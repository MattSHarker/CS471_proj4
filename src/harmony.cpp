
/**
 * @file harmony.cpp
 * @author Matthew Harker
 * @brief 
 * @version 1.0
 * @date 2019-05-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <iostream>
#include <random>
#include <thread>

#include "harmony.h"
#include "runFuncs.h"

using namespace std;

/**
 * @brief Threads the algorithm so each thread runs the population
 *          through a specific function
 * 
 * @param pops  The array of Population objects
 * @param rks   The array of RecordKeeper objects
 */
void harmony(Population** pops, RecordKeeper** rks)
{
    cout << "Starting Harmony Search algorithm...\n";

    int funcs = pops[0]->getNumFuncs();
    thread* myThreads = new thread[funcs];

    for (int i = 0; i < funcs; ++i)
        myThreads[i] = thread(runHarmony, pops[i], rks[i]);
    
    for (int i = 0; i < funcs; ++i)
        myThreads[i].join();

    delete [] myThreads;
    
    cout << "Harmony Search has completed...\n";
}

/**
 * @brief Runs a population through the Harmony Search algorithm
 * 
 * @param pop   The population being optimized
 * @param rk    Records the information as the optimization executes
 */
void runHarmony(Population* pop, RecordKeeper* rk)
{
    // initialize random number generation
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> distr(0, 1);
    double rnd;

    // variables for the algorithm
    double* newHarm = new double[pop->getSolutionSize()];
    double  newFit;
    clock_t timer;

    // initialize population
    initializeHS(pop);

    // run it $experimentation times
    for (int i = 0; i < pop->getExperimentations(); ++i)
    {
        // start the timer
        timer = clock();

        // for each pitch in the harmony
        for (int j = 0; j < pop->getSolutionSize(); ++j)
        {
            if (distr(mt) <= pop->getHMCR())
            {
                // choose an existing harmony randomly and set it to newHarm
                rnd = distr(mt) * pop->getPopSize();
                newHarm[j] = pop->getPopulation(rnd, j);

                // adjust the pitch randomly within limits
                if (distr(mt) <= pop->getPAR())
                    newHarm[j] = adjustPitch(newHarm[j], pop->getBandwidth());
            }

            // otherwise generate new harmonics via randomization
            else
                newHarm[j] = pop->getLowerBound() + distr(mt) * (pop->getUpperBound() - pop->getLowerBound());

        }
        // accept the new solutions if better
        newFit = runSolution(newHarm, pop->getSolutionSize(), pop->getFunction());
        pop->incrimentFuncCalls();

        if (newFit < pop->getFitness(pop->getPopSize()-1));
            addNewHarmony(pop, newHarm, newFit);

        // end the timer
        timer = clock() - timer;
       
        // update records
        updateRecordsFF(pop, rk, timer, i);
    }

    // record all of the final fitnesses
    for (int i = 0; i < pop->getPopSize(); ++i)
        rk->setFinalFit(pop->getFitness(i), i, 0);

    // destrouy
    delete[] newHarm;
}

/**
 * @brief Initializes a population to be optimized
 * 
 * @param pop The population to initialize
 */
void initializeHS(Population* pop)
{
    // set up random number generation using mersenne twister 19937
    random_device rd;
    mt19937 mt(rd());

    // set up random distributions
    uniform_real_distribution<double> distr(pop->getLowerBound(), pop->getUpperBound());

    // initialize each value to a random value
    for (int i = 0; i < pop->getPopSize(); ++i)
        for (int j = 0; j < pop->getSolutionSize(); ++j)
            pop->setPopulation(i, j, distr(mt));
    
    // generate the fitness array
    pop->generateAllFitness();

    // sort the population (and fitness array)
    pop->sortPopulation();

    // reset the function calls
    pop->resetFuncCalls();
}

/**
 * @brief Adjusts the pitches of a harmony
 * 
 * @param pitch     The pitch to be adjusted
 * @param bandwidth A constant that adjusts the pitch
 * @return double   The resulting adjustment
 */
double adjustPitch(double pitch, double bandwidth)
{
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> distr(-1, 1);

    return pitch + bandwidth * distr(mt);
}

/**
 * @brief Inserts a new harmony into a population.
 *          The new harmony will be insterted into a sorted
 *          position, so the population must already be sorted
 *          for this to work. This process will also remove the
 *          worst harmony in the population.
 * 
 * @param pop       The population being optimized
 * @param newHarm   The harmony being added into the population
 * @param newFit    The fitness of the new harmony being added
 */
void addNewHarmony(Population* pop, double* newHarm, double newFit)
{
    // variables for the new position
    int    index = 0;
    double curFit;

    // find the index to move it to, go from best to worst
    while (index < pop->getPopSize()-1)
    {
        // get the fitness to compare to
        curFit = pop->getFitness(index);

        // if the current fitness is worse than the new one
        if (newFit < curFit)
            break;
        else
            ++index;
    }

    // going backwards, shift the worse fireflys down
    for (int i = pop->getPopSize()-1; i > index; --i)
    {
        // replace each dimension with the one ahead of it
        pop->setPopulation(i, pop->getPopulation(i-1));

        // replace the fitnesses with the one before it
        pop->setFitness(i, pop->getFitness(i-1));
    }

    // replace the values at the index
    pop->setPopulation(index, newHarm);

    // replace the fitnes
    pop->setFitness(index, newFit);
}

/**
 * @brief Updates the RecordKeeper object with information of the
 *          optimization algorithm's progress.
 * 
 * @param pop       The populaion being optimized
 * @param rk        The RecordKeeper object storing the information
 * @param timer     Records the time an iteration took to complete
 * @param iter      Which iteration the population has just finished
 */
void updateRecordsFF(Population* pop, RecordKeeper* rk, clock_t timer, const int iter)
{
    // record data
    rk->setHistoricBestFit(pop->getFitness(0), iter);
    rk->setHistoricWorstFit(pop->getFitness(pop->getPopSize()-1), iter);
    rk->setTimeTaken(double(timer*1000)/CLOCKS_PER_SEC, iter);
    rk->setFinalFuncCalls(pop->getFuncCalls(), iter);
    pop->resetFuncCalls();
}

