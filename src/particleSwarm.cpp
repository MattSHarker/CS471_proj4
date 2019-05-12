
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
    cout << "Starting Particle Swarm optimization...\n";

    // create threads
    thread* myThreads = new thread[pops[0]->getNumFuncs()];

    // start threads
    for (int i = 0; i < pops[0]->getNumFuncs(); ++i)
        myThreads[i] = thread(runParticleSwarm, pops[i], rks[i]);
    
    // join threads
    for (int i = 0; i < pops[0]->getNumFuncs(); ++i)
        myThreads[i].join();
/*

    for (int i = 0; i < pops[0]->getNumFuncs(); ++i)
        runParticleSwarm(pops[i], rks[i]);
*/


    // destroy the threads
    delete [] myThreads;

    cout << "Particle Swarm optimization completed\n";
}

/**
 * @brief Runs each thread of PSO
 * 
 * @param pop The population to optimize
 */
void runParticleSwarm(Population* pop, RecordKeeper* rk)
{
    // initialize the population
    initializePSO(pop);

    // create a timer
    clock_t timer;

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

        // update record
        updateRecords(pop, rk, timer, i);
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
    double k   = pop->getDampener();
    double c1  = pop->getVelConst1();
    double c2  = pop->getVelConst2();

    // variables for the algorithm
    double vel;
    double pos;
    double rand1;
    double rand2;
    
    for (int i = 0; i < pop->getPopSize(); ++i)
    {
        for (int j = 0; j < pop->getSolutionSize(); ++j)
        {
            // get the velocity
            pos = pop->getVelocity(i, j);

            // create random variables ensure they are not 0
            do { rand1 = distr(mt); } while (rand1 == 0.0);
            do { rand2 = distr(mt); } while (rand2 == 0.0);

            // create and adjust the new velocity
            vel  = c1 * rand1 * (pop->getPBestVec(i, j)   - pop->getPopulation(i, j));
            vel += c2 * rand2 * (pop->getGlobalBestVec(j) - pop->getPopulation(i, j));
            vel *= k;

            // adjust the position
            pos += vel;

            // set the new velocity value
            pop->setVelocity(i, j, pos);
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

void updateRecords(Population* pop, RecordKeeper* rk, const clock_t timer, const int iter)
{
    // save the time taken
    rk->setTimeTaken(double(timer*1000)/CLOCKS_PER_SEC, iter);

    // record function calls
    rk->setFinalFuncCalls(pop->getFuncCalls(), iter);

    // add current fit and pBest to records
    for (int x = 0; x < pop->getPopSize(); ++x)
    {
        rk->setHistoricFit(pop->getFitness(x), x, iter);
        rk->setHistoricPBest(pop->getPBestFit(x), x, iter);
    }
    
    // add current gBest to records
    rk->setHistoricGBest(pop->getGlobalBestFit(), iter);
}

