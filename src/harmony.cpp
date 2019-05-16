
#include <iostream>
#include <random>
#include <thread>

#include "harmony.h"
#include "runFuncs.h"

using namespace std;

void harmony(Population** pops, RecordKeeper** rks)
{
    int funcs = pops[0]->getNumFuncs();
    thread* myThreads = new thread[funcs];

    for (int i = 0; i < funcs; ++i)
        myThreads[i] = thread(runHarmony, pops[i], rks[i]);
    
    for (int i = 0; i < funcs; ++i)
        myThreads[i].join();

/*
    for (int i = 0; i < funcs; ++i)
        runHarmony(pops[i], rks[i]);
*/

    delete [] myThreads;
}

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
       
        // record data
        rk->setHistoricBestFit(pop->getFitness(0), i);
        rk->setHistoricWorstFit(pop->getFitness(pop->getPopSize()-1), i);
        rk->setTimeTaken(double(timer*1000)/CLOCKS_PER_SEC, i);
        rk->setFinalFuncCalls(pop->getFuncCalls(), i);
        pop->resetFuncCalls();
    }

    delete[] newHarm;
}


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

    if (pop->getFunction() == 0)
        for (int i = 0; i < pop->getPopSize(); ++i)
            cout << pop->getFitness(i) << endl;

    // reset the function calls
    pop->resetFuncCalls();
}


void pitchAdjust(Population* pop, double* newHarm, const int elem)
{
    // setup random number generation
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> distr(-1, 1);

    // assign a new value for each dimension in the harmony
    for (int i = 0; i < pop->getSolutionSize(); ++i)
    {
        // create the new value
        double temp = newHarm[elem];
        temp += pop->getBandwidth() * distr(mt);

        // assign the new value
        newHarm[i] = temp;
    }
}

double adjustPitch(double pitch, double bandwidth)
{
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> distr(-1, 1);

    return pitch + bandwidth * distr(mt);
}

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

