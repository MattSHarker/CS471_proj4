
#include <iostream>
#include <random>
#include <thread>

#include "harmony.h"

using namespace std;

void harmony(Population** pops)
{
    int funcs = pops[0]->getNumFuncs();
    thread* myThreads = new thread[funcs];
/*
    for (int i = 0; i < funcs; ++i)
        myThreads[i] = thread(runHarmony, pops[i]);
    
    for (int i = 0; i < funcs; ++i)
        myThreads[i].join();
*/
    for (int i = 0; i < funcs; ++i)
        runHarmony(pops[i]);

    delete [] myThreads;
}

void runHarmony(Population* pop)
{
    // initialize random number generation
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> distr(0, 1);

    // variables for the algorithm
    double* newHarm = new double[pop->getSolutionSize()];

    // initialize population
    initializeHS(pop);

    // run it $experimentation times
    for (int i = 0; i < pop->getExperimentations(); ++i)
    {
        // generate new harmonics by accepting new harmonics

        // adjust pitch to get new harmonics


        if (distr(mt) < pop->getHMCR())
        {
            // choose an existing harmony randomly
        }
        else if (distr(mt) < pop->getPAR())
        {
            // adjust the pitch randomly within limits
        }
        else
        {
            // generate new harmonics via randomization
        }
        
        // accept the new solutions if better

        // record best and worst solutions

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
}


void pitchAdjust(Population* pop, double* newHarm, const int origIndex)
{
    // setup random number generation
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> distr(-1, 1);

    // assign a new value for each dimension in the harmony
    for (int i = 0; i < pop->getSolutionSize(); ++i)
    {
        // create the new value
        double temp = pop->getPopulation(origIndex, i);
        temp += pop->getBandwidth() * distr(mt);

        // assign the new value
        newHarm[i] = temp;
    }
}



