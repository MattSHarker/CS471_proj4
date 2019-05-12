/**
 * @file Population.cpp
 * @author Matthew Harker
 * @brief Holds optimization information
 * @version 3.0
 * @date 2019-05-03
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <cfloat>
#include <chrono>
#include <climits>
#include <iostream>
#include <random>

#include "Population.h"
#include "runFuncs.h"

using namespace std;

/**
 * @brief Construct a new Population:: Population object
 * 
 * @param params    A parameters object to set values
 * @param func      Which function the population deals with
 */
Population::Population(Parameters params, const int func)
{
    // initialize variables
    popSize          = params.popSize;
    solutionSize     = params.numDims;
    experimentations = params.experimentations;
    numFuncs         = params.numFuncs;
    dampener         = params.dampener;
    velConst1        = params.velConst1;
    velConst2        = params.velConst2;
    function         = func;
    funcCalls        = 0;

    globBestFit = DBL_MAX;

    lowerBound = params.lowRanges[func];
    upperBound = params.highRanges[func];

    // initialize fitness array
    fitness = new double[popSize];

    // initialize the globalBest solution array and set the values to DBL_MAX
    globBestVec = new double[solutionSize];

    // initialize the pBest fitness array
    pBestFit = new double[popSize];

    // initialize the intensity array
    intensity = new double[popSize];

    // initialize the pBest solution matrix
    pBestVec = new double*[popSize];
    for (int i = 0; i < popSize; ++i)
        pBestVec[i] = new double[solutionSize];

    // initialize population matrix
    population = new double*[popSize];
    for (int i = 0; i < popSize; ++i)
        population[i] = new double[solutionSize];

    // initialize velocity matrix
    velocity = new double*[popSize];
    for (int i = 0; i < popSize; ++i)
        velocity[i] = new double[solutionSize];
}


/**
 * @brief Destroy the Population:: Population object
 * 
 */
Population::~Population()
{
    // destroy the population matrix
    if (population != nullptr)
    {
        for (int i = 0; i < popSize; ++i)
            delete[] population[i];

        delete[] population;
    }

    // destroy the fitness array
    if (fitness != nullptr)
        delete [] fitness;

    // destroy the global best vector array
    if (globBestVec != nullptr)
        delete [] globBestVec;
    
    // destroy the personal best fitness array
    if (pBestFit != nullptr)
        delete [] pBestFit;

    // destroy the intensity array
    if (intensity != nullptr)
        delete [] intensity;
    
    // destroy the personal best solution matrix
    if (pBestVec != nullptr)
    {
        for (int i = 0; i < popSize; ++i)
            delete [] pBestVec[i];
        
        delete [] pBestVec;
    }

    // destroy the velocity matrix
    if (velocity != nullptr)
    {
        for (int i = 0; i < popSize; ++i)
            delete [] velocity[i];
        
        delete [] velocity;
    }
}

/**
 * @brief Returns the population size
 * 
 * @return int population size
 */
int Population::getPopSize()
{
    return popSize;
}

/**
 * @brief Returns the solution size
 * 
 * @return int solution size 
 */
int Population::getSolutionSize()
{
    return solutionSize;
}

/**
 * @brief Returns the number of experimentations
 * 
 * @return int number of experimentations
 */
int Population::getExperimentations()
{
    return experimentations;
}

/**
 * @brief increase the number of function calls by 1
 * 
 */
void Population::incrimentFuncCalls()
{
    ++funcCalls;
}

void Population::resetFuncCalls()
{
    funcCalls = 0;
}

/**
 * @brief Return the number of function calls
 * 
 * @return int function calls
 */
int Population::getFuncCalls()
{
    return funcCalls;
}

/**
 * @brief return the number of the function the population uses
 * 
 * @return int 
 */
int Population::getFunction()
{
    return function;
}

/**
 * @brief Return the total number of functions
 * 
 * @return int total functions
 */
int Population::getNumFuncs()
{
    return numFuncs;
}

/**
 * @brief Returns the value of the dampener variable.
 *          Dampener affects the overall velocity of a particle's movement.
 * 
 */
double Population::getDampener()
{
    return dampener;
}

/**
 * @brief Returns the value in velConst1
 * 
 * @return double The first constant for modifying the velocity 
 */
double Population::getVelConst1()
{
    return velConst1;
}

/**
 * @brief Returns the value of velConst2
 * 
 * @return double The second constant for modifying the velocity
 */
double Population::getVelConst2()
{
    return velConst2;
}

/**
 * @brief Returns the value of alpha
 * 
 * @return double A constant to determine movement
 */
double Population::getAlpha()
{
    return alpha;
}

/**
 * @brief Returns the value of beta
 * 
 * @return double A variable to determine movement and attractiveness
 */
double Population::getBeta()
{
    return beta;
}

/**
 * @brief Returns the value of gamma
 * 
 * @return double A variable to determine attractiveness,
 *                  movement, and light intensity
 */
double Population::getGamma()
{
    return gamma;
}

/**
 * @brief returns the value of the lowest allowable value
 * 
 * @return double lowest allowable value
 */
double Population::getLowerBound()
{
    return lowerBound;
}

/**
 * @brief Returns the value of the highest allowable value
 * 
 * @return double highest allowable value
 */
double Population::getUpperBound()
{
    return upperBound;
}

/**
 * @brief Set the values of a solution in the population
 * 
 * @param vec       The solution vector being set
 * @param newSol    The new solution vector
 */
void Population::setPopulation(const int vec, double* newSol)
{
    for (int i = 0; i < solutionSize; ++i)
        population[vec][i] = newSol[i];
}

/**
 * @brief Set the value of an element in the population matrix
 * 
 * @param vec       The vector of the matrix to set
 * @param elem      The element of the vector to set
 * @param newVal    The value to set the element to
 */
void Population::setPopulation(const int vec, const int elem, double newVal)
{
    population[vec][elem] = newVal;
}

/**
 * @brief Return a value from a solution vector
 * 
 * @param vec       The solution vector
 * @param elem      The element from the vector
 * @return double   The value being returned
 */
double Population::getPopulation(const int vec, const int elem)
{
    return population[vec][elem];
}

/**
 * @brief Returns a solution vector
 * 
 * @param vec       The index of the solution vector
 * @return double*  The solution vector
 */
double* Population::getPopulation(const int vec)
{
    return population[vec];
}

/**
 * @brief Sets one value of the pBestVec matrix
 * 
 * @param vec       The vector to set
 * @param elem      The element of the vector to set
 * @param newVal    The value to set
 */
void Population::setPBestVec(const int vec, const int elem, double newVal)
{ 
    pBestVec[vec][elem] = newVal;
}

/**
 * @brief Returns a value from the pBestVec matrix
 * 
 * @param vec       The vector of the value
 * @param elem      The element of the vector
 * @return double   The value being returned
 */
double Population::getPBestVec(const int vec, const int elem)
{
    return pBestVec[vec][elem];
}

/**
 * @brief Sets a value in the pBestFit array
 * 
 * @param vec       The element of the array to set
 * @param newFit    The value to set the element to
 */
void Population::setPBestFit(const int vec, double newFit)
{
    pBestFit[vec] = newFit;
}

/**
 * @brief Returns a value from the pBestFit array
 * 
 * @param vec       The element to return
 * @return double   The value of the element
 */
double Population::getPBestFit(const int vec)
{
    return pBestFit[vec];
}




/**
 * @brief Sets a value in the globBestVec array
 * 
 * @param elem      The element of the array to set
 * @param newBest   The value to set the element to
 */
void Population::setGlobalBestVec(const int elem, double newBest)
{
    globBestVec[elem] = newBest;
}

/**
 * @brief Returns a value from the globBestVec array
 * 
 * @param elem      The element of the array to return
 * @return double   The value of the element
 */
double Population::getGlobalBestVec(const int elem)
{
    return globBestVec[elem];
}

/**
 * @brief Sets the value of globBestFit
 * 
 * @param newFit The new value for globBestFit
 */
void Population::setGlobalBestFit(double newFit)
{
    globBestFit = newFit;
}

/**
 * @brief Returns the value of globBestFit
 * 
 * @return double The value of globBestFit
 */
double Population::getGlobalBestFit()
{
    return globBestFit;
}


/**
 * @brief Returns the index of the solution vector with the lowest fitness
 * 
 * @return int Index of best solution vector
 */
int Population::getIndexOfBest()
{
    // to store the value of the best solution
    double best = DBL_MAX;
    int index = 0;

    // find the best solution
    for (int i = 0; i < popSize; ++i)
    {
        if (best > fitness[i])
        {
            best = fitness[i];
            index = i;
        }
    }

    // return the population at the best index
    return index;
}

/**
 * @brief Generates the fitness of every solution vector
 * 
 */
void Population::generateAllFitness()
{
    // calculate the fitness for every solution
    for (int i = 0; i < popSize; ++i)
        generateOneFitness(i);
}

/**
 * @brief generates the fitness of one solution vector
 * 
 * @param index Index of solution
 */
void Population::generateOneFitness(const int index)
{
    // calcualate and set the fitness of the specified solution
    fitness[index] = runSolution(population[index], solutionSize, function);

    // incriment the functionCall variable
    incrimentFuncCalls();
}

/**
 * @brief Returns the fitness of a solution
 * 
 * @param index     Index of solution
 * @return double   Fitness of solution
 */
double Population::getFitness(const int index)
{
    return fitness[index];
}

/**
 * @brief Returns full normalized fitness array
 * 
 * @return double* Fitness array
 */
double* Population::getFitness()
{
    return fitness;
}

/**
 * @brief Sets the value of an element in the velocity matrix
 * 
 * @param vec       The vector of the matrix to set
 * @param elem      The element of the matrix to set
 * @param newVel    The value to set the element to
 */
void Population::setVelocity(const int vec, const int elem, double newVel)
{
    velocity[vec][elem] = newVel;
}

/**
 * @brief Returns the value of an element from the velocity matrix
 * 
 * @param vec       The vector of the element to return
 * @param elem      The element of the vector to return
 * @return double   The value of the element
 */
double Population::getVelocity(const int vec, const int elem)
{
    return velocity[vec][elem];
}

