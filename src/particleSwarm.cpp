
#include <ctime>
#include <iostream>
#include <random>
#include <thread>

#include "particleSwarm.h"

using namespace std;

/**
 * @brief Optimizes population objects using Particle Swarm optimization
 * 
 * @param pops 
 */
void particleSwarm(Population** pops, RecordKeeper** rks)
{
    int funcs = pops[0]->getNumFuncs();
    thread* myThreads = new thread[funcs];
/*
    for (int i = 0; i < funcs; ++i)
        myThreads[i] = thread(runParticleSwarm, pops[i], rks[i]);
    
    for (int i = 0; i < funcs; ++i)
        myThreads[i].join();
*/
    for (int i = 0; i < funcs; ++i)
        runParticleSwarm(pops[i], rks[i]);

    delete [] myThreads;

}

/**
 * @brief Runs each thread of PSO
 * 
 * @param pop The population to optimize
 */
void runParticleSwarm(Population* pop, RecordKeeper* rk)
{
cout << "Starting PSO " << pop->getFunction() + 1 << endl;
    // initialize the population
    initializePSO(pop);
    clock_t timer;

// cout << "Global Best Fit: " << pop->getGlobalBestFit() << endl;
cout << "Persnl Best Fit [0]: " << pop->getPBestFit(0) << endl;

    // run it X times
    for (int i = 0; i < pop->getExperimentations(); ++i)
    {
        // set funcCalls to 0
        pop->resetFuncCalls();

        // start timer
        timer = clock();

        // update the full population
        for (int j = 0; j < pop->getPopSize(); ++j)
        {
            // calculate new velocity of the particle
            updateVelocity(pop);

            // update the particle
            updateParticles(pop);

            // calculate the fitness
            updateFitness(pop);

            // update pBest and gBest (if necessary)
            updatePersonalBest(pop);
            updateGlobalBest(pop);
        }

        // end timer and record it
        timer = clock() - timer;
        rk->setTimeTaken(double(timer*1000)/CLOCKS_PER_SEC, i);

        // record function calls
        rk->setFinalFuncCalls(pop->getFuncCalls(), i);

        // add current fit and pBest to records
        for (int x = 0; x < pop->getPopSize(); ++x)
        {
            rk->setHistoricFit(pop->getFitness(x), i, x);
            rk->setHistoricPBest(pop->getPBestFit(x), i, x);
        }
        
        // add current gBest to records
        rk->setHistoricGBest(pop->getGlobalBestFit(), i);

// cout << "Global Best Fit: " << pop->getGlobalBestFit() << endl;
cout << "Global Best Fit: " << pop->getGlobalBestFit() << endl;

    }
}

/**
 * @brief Updates all velocities based on the particle's
 *          pBest and the population's gBest
 * 
 * @param pop The population to update
 */
void updateVelocity(Population* pop)
{
    // set up random number generation using mersenne twister 19937
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> distr(0, 1);

    // get the velocity constants
    double c1  = pop->getVelConst1();
    double c2  = pop->getVelConst2();

    for (int i = 0; i < pop->getPopSize(); ++i)
    {
        for (int j = 0; j < pop->getSolutionSize(); ++j)
        {
            // get the velocity
            double vel = pop->getVelocity(i, j);

            // calculate the velocity
            double rand1 = distr(mt);
            double rand2 = distr(mt);

            // ensure that 0 is not a possible value
            if (rand1 == 0.0) rand1 = 0.00000000001;
            if (rand2 == 0.0) rand2 = 0.00000000001;

            // create the new velocity valuePersnlPersnl
            vel += c1 * rand1 * (pop->getPBestVec(i, j)   - pop->getPopulation(i, j));
            vel += c2 * rand2 * (pop->getGlobalBestVec(j) - pop->getPopulation(i, j));

            // set the new velocity value
            pop->setVelocity(i, j, vel);
        }
    }
}

/**
 * @brief Updates the position of every particle.
 *          The position of the particle is updated by taking
 *          the current position and adding the velocity to it.
 *          If the velocity takes the particle out of bounds the
 *          new value is set to the relevant bound's value.
 * 
 * @param pop The population to update
 */
void updateParticles(Population* pop)
{
    // create a variable to hold info about the position
    double newPos;

    for (int i = 0; i < pop->getPopSize(); ++i)
    {
        for (int j = 0; j < pop->getSolutionSize(); ++j)
        {
            // get a new value for the particle's element
            newPos = pop->getPopulation(i, j) + pop->getVelocity(i, j);
            
            // check the bounds
            if (newPos > pop->getUpperBound()) newPos = pop->getUpperBound();
            if (newPos < pop->getLowerBound()) newPos = pop->getLowerBound();
            
            // assign the new value to the particle
            pop->setPopulation(i, j, newPos);
        }
    }
}

/**
 * @brief Updates the fitnesses of the particles in the population
 * 
 * @param pop The population to update
 */
void updateFitness(Population* pop)
{
    pop->generateAllFitness();
}

/**
 * @brief Updates each particle's personal best.
 *          If the particle's new fitness is more optimal
 *          the the personal best, update the personal best.
 * 
 * @param pop The population to update
 */
void updatePersonalBest(Population* pop)
{
    // for each particle in the population
    for (int i = 0; i < pop->getPopSize(); ++i)
    {
        double curFit = pop->getFitness(i);
        double pBest  = pop->getPBestFit(i);

        // check if pBest needs to be updated
        if (curFit < pBest)
        {
            // update pBestFit
            pop->setPBestFit(i, curFit);

            // update pBestVec
            for (int j = 0; j < pop->getSolutionSize(); ++j)
                pop->setPBestVec(i, j, pop->getPopulation(i, j));
        }
    }
}

/**
 * @brief Updates the global best particle and fitness.
 *          If the population contains a particle that is
 *          more optimal that the global best, updat the
 *          global best particle and its fitness
 * 
 * @param pop The population to update
 */
void updateGlobalBest(Population* pop)
{
    for (int i = 0; i < pop->getPopSize(); ++i)
    {
        double curFit = pop->getFitness(i);
        double glBest = pop->getGlobalBestFit();

        // check if globBest needs to be updated
        if (curFit < glBest)
        {
            // update globBestFit
            pop->setGlobalBestFit(curFit);

            // update globBestVec
            for (int j = 0; j < pop->getSolutionSize(); ++j)
            {
                pop->setGlobalBestVec(j, pop->getPopulation(i, j));
            }
        }
    }
}


/**
 * @brief Initializes a population.
 *          The particles and velocities in the population
 *          are set to random values. The personal best arrays
 *          and values are set and the global best array and
 *          value is set.
 *          
 * 
 * @param pop The population to initialize
 */
void initializePSO(Population* pop)
{
    // set up random number generation using mersenne twister 19937
    random_device rd;
    mt19937 mt(rd());

    // set up random distributions
    uniform_real_distribution<double> distrVal(pop->getLowerBound(), pop->getUpperBound());
    uniform_real_distribution<double> distrVlct(0, 0.5*(pop->getUpperBound() - pop->getLowerBound()));

    // initialize each value to a random value
    for (int i = 0; i < pop->getPopSize(); ++i)
        for (int j = 0; j < pop->getSolutionSize(); ++j)
            pop->setPopulation(i, j, distrVal(mt));

    // generate the velocity matrix
    for (int i = 0; i < pop->getPopSize(); ++i)
        for (int j = 0; j < pop->getSolutionSize(); ++j)
            pop->setVelocity(i, j, distrVlct(mt));
    
    // generate the fitness array
    pop->generateAllFitness();


    // generate the personal best matrix and array
    // copy the current population into the personal best matrix
    for (int i = 0; i < pop->getPopSize(); ++i)
        for (int j = 0; j < pop->getSolutionSize(); ++j)

    // copy the fitness array into personal best array
    for (int i = 0; i < pop->getPopSize(); ++i)
        pop->setPBestFit(i, pop->getFitness(i));


    // generate the global best array and variable
    // get the best index and its fitness
    int bestInd = pop->getIndexOfBest();
    double curBest = pop->getFitness(bestInd);

    // set the global best fitness
    pop->setGlobalBestFit(curBest);

    // set the global best solution
    for (int i = 0; i < pop->getSolutionSize(); ++i)
        pop->setGlobalBestVec(i, pop->getPopulation(bestInd, i));

}

