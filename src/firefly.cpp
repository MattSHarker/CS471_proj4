
#include <iostream>
#include <random>
#include <thread>

#include "firefly.h"

using namespace std;

void firefly(Population** pops)
{
    int funcs = pops[0]->getNumFuncs();
    thread* myThreads = new thread[funcs];
/*
    for (int i = 0; i < funcs; ++i)
        myThreads[i] = thread(runFirefly, pops[i]);
    
    for (int i = 0; i < funcs; ++i)
        myThreads[i].join();
*/
    for (int i = 0; i < funcs; ++i)
        runFirefly(pops[i]);

    delete [] myThreads;
}


void runFirefly(Population* pop)
{
    // initialize the fireflies

    // for each iteration
    for (int t = 0; t < pop->getExperimentations(); ++t)
    {
        // for each firefly
        for (int i = 0; i < pop->getPopSize(); ++i)
        {
            // for each firefly again
            for (int j = 0; j < pop->getPopSize(); ++j)
            {
                // move firefly j towards firefly i (equation 3)

                // attractiveness varies with distance r via (equation 2)

                // evaluate and update the worst firefly in the population (eqn 4)

            }
        }
    }
}


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

}


void moveFirefly(Population* pop, const int ff1, const int ff2)
{

}

// light intensity
// needs to be fixed (figure out what original intensity means)
double equationOne(Population* pop, const int r)
{
    double intensity = pop->getFitness(r);
    double gamma     = pop->getGamma();

    intensity *= exp(-gamma * pow(r, 2.0));

    return intensity;
}

// attractiveness
double equationTwo(Population* pop, const int r)
{
    double beta = pop->getBeta();
    double gamma = pop->getGamma();

    beta *= exp(-gamma * pow(r, 2.0));

    return beta;
}

// distance between two fireflies (ff1, ff2)
double equationThree(Population* pop, const int ff1, const int ff2)
{
    double distance = 0; 
    double temp;

    for (int i = 0; i < pop->getSolutionSize(); ++i)
    {
        temp  = pop->getPopulation(ff1, i);
        temp -= pop->getPopulation(ff2, i);

        pow(temp, 2.0);
    }

    return pow(distance, 0.5);
}

// movement
double equationFour(Population* pop, const int r, const int ff1, const int ff2, const int t, const int d)
{
    // set up random number generation
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> distr(0, 1);

    // retreive a random value and ensure it is not 0
    double rnd;
    do {rnd = distr(mt);} while (rnd == 0.0);
    
    // retreive and create other variables
    double beta  = pop->getBeta();
    double gamma = pop->getGamma();
    double temp;

    // calcualte the movement
    temp  = pop->getPopulation(ff1, d);
    temp += equationOne(pop, r);
    temp *= pop->getPopulation(ff2, d) - pop->getPopulation(ff1, d);

    // fix
    temp += rnd * 1;

    
}


