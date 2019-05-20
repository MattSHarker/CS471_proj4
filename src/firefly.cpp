
/**
 * @file firefly.cpp
 * @author Matthew Harker
 * @brief Optimizes a population using the Firefly algorithm
 * @version 1.0
 * @date 2019-05-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <ctime>
#include <iostream>
#include <random>
#include <thread>

#include "firefly.h"
#include "runFuncs.h"

using namespace std;

/**
 * @brief Threads a series of Population and RecordKeeper object
 *          to be optimized by the firefly optimization algorithm
 * 
 * @param pops  The array of Population objects to be optimized
 * @param rks   The array of RecordKeeper objects to record the optimization process
 */
void firefly(Population** pops, RecordKeeper** rks)
{
    cout << "Starting firefly optimization\n";

    // create the threads
    int funcs = pops[0]->getNumFuncs();
    thread* myThreads = new thread[funcs];

    // start the threads
    for (int i = 0; i < funcs; ++i)
        myThreads[i] = thread(runFirefly, pops[i], rks[i]);
    
    // join the threads
    for (int i = 0; i < funcs; ++i)
        myThreads[i].join();

    delete [] myThreads;

    cout << "Firefly optimization has completed\n";
}

/**
 * @brief Optimizes a population using the firefly optimization algorithm
 * 
 * @param pop   The population to optimize
 * @param rk    Records data about the optimization process
 */
void runFirefly(Population* pop, RecordKeeper* rk)
{
    // initialize the fireflies
    initializeFFO(pop);
    
    // variables for the algorithm
    double  r;
    double* newPos = new double[pop->getSolutionSize()];
    clock_t timer;

    // for each iteration
    for (int t = 0; t < pop->getExperimentations(); ++t)
    {
        // start the timer
        timer = clock();

        // for each firefly
        for (int i = 0; i < pop->getPopSize(); ++i)
        {
            // compare with each other firefly
            for (int j = 0; j < pop->getPopSize(); ++j)
            {
                // get the distance (eq 3, 2)
                r = ffDistance(pop, i, j);

                // only move the firefly if it is worse
                if (intensity(pop, j, r) < intensity(pop, i, r))
                {                  
                    // (get a new position for a firefly)
                    newPosition(pop, newPos, r, i, j);
                    // evaluate and update the worst firefly in the population (eqn 4)
                    addNewFirefly(pop, newPos);

                    // calculate the new fitness
                }
            }
        }
        // stop the timer
        timer = clock() - timer;

        // record the results
        recordInfo(pop, rk, timer, t);
    }

    // record the final fitnesses
    for (int i = 0; i < pop->getPopSize(); ++i)
        rk->setFinalFit(pop->getFitness(i), i, 0);
    
    // destroy the newPosition array
    delete[] newPos;
}

/**
 * @brief Initializes a population to be optimized
 * 
 * @param pop The population to be initialized
 */
void initializeFFO(Population* pop)
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
    pop->resetFuncCalls();

    // sort the population (and fitness array)
    pop->sortPopulation();
}


// light intensity
/**
 * @brief Generates a value for the light intensity of one firefly based
 *          on the distance of another.
 * 
 * @param pop       The population to get information from
 * @param ff        The index of the firefly
 * @param r         The distance from the firefly the other firefly is
 * @return double   The intensity of the firefly's light
 */
double intensity(Population* pop, const int ff, double r)
{
    double intensity = pop->getFitness(ff);
    double gamma     = pop->getGamma();

    intensity *= exp(-gamma * pow(r, 2.0));

    return intensity;
}


/**
 * @brief Returns a value for beta based on the distance between
 *          two fireflies
 * 
 * @param pop       The population to get information from
 * @param r         The distance between two fireflies
 * @return double   The beta value of the two fireflies
 */
double newBeta(Population* pop, double r)
{
    double beta  = pop->getBeta();
    double gamma = pop->getGamma();

    // modified from exp (-gamma * r^2)
    beta *= exp(-gamma * r);

    return beta;
}


/**
 * @brief Calculates the distance between two fireflies
 * 
 * @param pop       The population to retreive positions from
 * @param ff1       The index of the firest firefly
 * @param ff2       The index of the second firefly
 * @return double   The distance between the two fireflies
 */
double ffDistance(Population* pop, const int ff1, const int ff2)
{
    double temp;
    double sum = 0;

    // create the summation of the square of the difference between two elements
    for (int i = 0; i < pop->getSolutionSize(); ++i)
    {
        temp = pop->getPopulation(ff1, i) - pop->getPopulation(ff2, i);
        temp = pow(temp, 2.0);
        sum += temp;
    }

    // take the square root of the summation
    return pow(sum, 0.5);
}


/**
 * @brief Creates a new firefly based on the positions of two pre-existing fireflies
 * 
 * @param pop       The population to retreive fireflies from
 * @param newPos    The new firefly to generate
 * @param r         The distance between the two fireflies
 * @param ff1       The index of the first firefly
 * @param ff2       The index of the second firefly
 */
void newPosition(Population* pop, double* newPos, const int r, const int ff1, const int ff2)
{
    // set up random number generation
    random_device rd;
    mt19937 mt(rd());
    normal_distribution<double>  distN(0,1);
    double rnd;

    // retreive and create other variables
    double alpha = pop->getAlpha();
    double pos;

    // adjust the position of each dimension
    for (int i = 0; i < pop->getSolutionSize(); ++i)
    {
        // retreive a random value and ensure it is not 0, then modify it
        do {rnd = distN(mt);} while (rnd == 0.0);
        rnd -= 0.5;
        rnd *= pop->getUpperBound() - pop->getLowerBound();

        // calcualte the movement
        pos  = pop->getPopulation(ff1, i);
        pos += newBeta(pop, r) * (pop->getPopulation(ff2, i) - pop->getPopulation(ff1, i));
        pos += alpha * rnd;

        // check the bounds
        if (pos > pop->getUpperBound()) pos = pop->getUpperBound();
        if (pos < pop->getLowerBound()) pos = pop->getLowerBound();

        // change the dimension's value
        newPos[i] = pos;
    }
}

/**
 * @brief Inserts a new firefly into a population.
 *          Adds a firefly into a sorted population. The firefly will
 *          be placed in its sorted position, and all worse fireflies 
 *          are shifted back one position. The worst firefly is removed
 *          during this process.
 * 
 * @param pop       The population to insert the firefly into
 * @param newPos    The new firefly to add to the population
 */
void addNewFirefly(Population* pop, double* newPos)
{
    // get the new position's fitness
    double newFit = runSolution(newPos, pop->getSolutionSize(), pop->getFunction());
    pop->incrimentFuncCalls();

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
    pop->setPopulation(index, newPos);

    // replace the fitnes
    pop->setFitness(index, newFit);
}


/**
 * @brief Records the results of an experimentation to a RecordKeeper object
 * 
 * @param pop       The population to get info from
 * @param rk        The RecordKeeper object to record to
 * @param timer     How long each experiment took (in ms)
 * @param expr      Which experiment just finished
 */
void recordInfo(Population* pop, RecordKeeper* rk, clock_t timer, const int expr)
{
    // record the results
    rk->setHistoricBestFit(pop->getFitness(0), expr);
    rk->setHistoricWorstFit(pop->getFitness(pop->getPopSize()-1), expr);
    rk->setTimeTaken(double(timer*1000)/CLOCKS_PER_SEC, expr);
    rk->setFinalFuncCalls(pop->getFuncCalls(), expr);
    pop->resetFuncCalls();
}


