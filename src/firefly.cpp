
#include <iostream>
#include <random>
#include <thread>

#include "firefly.h"
#include "runFuncs.h"

using namespace std;

void firefly(Population** pops)
{
    cout << "Starting firefly optimization\n";

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

    cout << "Firefly optimization has completed\n";
}


void runFirefly(Population* pop)
{
    // initialize the fireflies
    initializeFFO(pop);
    
    // variables for the algorithm
    double r;

    // create an array to hold a temporary position
    double* newPos = new double[pop->getSolutionSize()];
    
    // for each iteration
    for (int t = 0; t < pop->getExperimentations(); ++t)
    {
        // for each firefly&
        for (int i = 0; i < pop->getPopSize(); ++i)
        {
            // for each firefly again
            for (int j = 0; j < pop->getPopSize(); ++j)
            {
                // get the distance (eq 3, 2)
                r = ffDistance(pop, i, j);

                // only move the firefly if it is worse
                if (intensity(pop, j, r) < intensity(pop, i, r))
                {                  
                    // move firefly i towards firefly j (equation 4)
                    // (get a new position for a firefly)
                    equationFour(pop, newPos, r, i, j);
                    // evaluate and update the worst firefly in the population (eqn 4)
                    addNewFirefly(pop, newPos);
                }
            }
        }

        cout << "Best fit[" << pop->getFunction() << "]: "
                            << pop->getFitness(0) << "\t "
                            << pop->getFitness(pop->getPopSize() / 2) << "\t  "
                            << pop->getFitness(pop->getPopSize() - 1)
                            << endl;
    }

    delete[] newPos;
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

    // sort the population (and fitness array)
    pop->sortPopulation();
}


// light intensity
double intensity(Population* pop, const int ff, double r)
{
    double intensity = pop->getFitness(ff);
    double gamma     = pop->getGamma();

    intensity *= exp(-gamma * pow(r, 2.0));

    return intensity;
}


// attractiveness
double equationTwo(Population* pop, double r)
{
    double beta  = pop->getBeta();
    double gamma = pop->getGamma();

    beta *= exp(-gamma * pow(r, 2.0));

    return beta;
}

// distance between two fireflies (ff1, ff2)
// produces the value r
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


// Create a new position
void equationFour(Population* pop, double* newPos, const int r, const int ff1, const int ff2)
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
        pos += equationTwo(pop, r) * (pop->getPopulation(ff2, i) - pop->getPopulation(ff1, i));
        pos += alpha * rnd;

        // check the bounds
        if (pos > pop->getUpperBound()) pos = pop->getUpperBound();
        if (pos < pop->getLowerBound()) pos = pop->getLowerBound();

        // change the dimension's value
        newPos[i] = pos;
    }
}

void addNewFirefly(Population* pop, double* newPos)
{
    // get the new position's fitness
    double newFit = runSolution(newPos, pop->getSolutionSize(), pop->getFunction());

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


