/**
 * @file Population.cpp
 * @author Matthew Harker
 * @brief Holds optimization information
 * @version 1.0
 * @date 2019-05-03
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <cfloat>
#include <chrono>
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
    generations      = params.generations;
    function         = func;
    funcCalls        = 0;

    mutProbability  = params.mutProbability;
    mutRange        = params.mutRange;
    mutPrecision    = params.mutPrecision;
    elitismRate     = params.elitismRate;
    crossoverRate   = params.crProbability;
    selection       = params.selection;
    scale           = params.scale;
    lambda          = params.lambda;

    lowerBound = params.lowRanges[func];
    upperBound = params.highRanges[func];

    // initialize fitness array
    fitness = new double[popSize];

    // initialize cost array
    cost = new double[popSize];

    // initialize population matrix
    population = new double*[popSize];
    for (int i = 0; i < popSize; ++i)
        population[i] = new double[solutionSize];
}



/**
 * @brief Construct a new Population:: Population object
 * 
 * @param other another population object to get values from
 */
Population::Population(Population* other)
{
    // copy information from the other population 
    popSize          = other->getPopSize();
    solutionSize     = other->getSolutionSize();
    experimentations = other->getExperimentations();
    function         = other->getFunction();
    numFuncs         = other->getNumFuncs();
    generations      = other->getGenerations();

    mutProbability = other->getMutProbability();
    mutRange       = other->getMutRange();
    mutPrecision   = other->getMutPrecision();
    elitismRate    = other->getElitismRate();
    crossoverRate  = other->getCrossoverRate();

    lowerBound = other->getLowerBound();
    upperBound = other->getUpperBound();

    // set funcCalls to 0
    funcCalls = 0;

    // initialize fitness array
    fitness = new double[popSize];

    // initialize cost array
    cost = new double[popSize];

    // initialize population matrix
    population = new double*[popSize];
    for (int i = 0; i < popSize; ++i)
        population[i] = new double[solutionSize];
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

    // destroy cost array
    if (cost != nullptr)
        delete [] cost;
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
 * @brief set the function of the population
 * 
 * @param newFunc the new function to run
 */
void Population::setFunction(const int newFunc)
{
    function = newFunc;
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
 * @brief return the number of generations being ran
 * 
 * @return int Number of generations
 */
int Population::getGenerations()
{
    return generations;
}

/**
 * @brief Sets the value of the lowest allowable value
 * 
 * @param newLower lowest allowable value
 */
void Population::setLowerBound(const int newLower)
{
    lowerBound = newLower;
}

/**
 * @brief sets the value of the highest allowable value
 * 
 * @param newUpper highest allowable value
 */
void Population::setUpperBound(const int newUpper)
{
    upperBound = newUpper;
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
 * @brief Sets the indices of the two parent variables
 * 
 * @param newPar1   Index of parent 1
 * @param newPar2   Index of parent 2
 */
void Population::setParents(const int newPar1, const int newPar2)
{
    parent1 = newPar1;
    parent2 = newPar2;
}

/**
 * @brief Return the index of parent 1
 * 
 * @return int Index of parent 1
 */
int Population::getParent1()
{
    return parent1;
}

/**
 * @brief Return the index of parent 2
 * 
 * @return int index of parent 2
 */
int Population::getParent2()
{
    return parent2;
}

/**
 * @brief return the value of selection
 * 
 * @return int selection
 */
int Population::getSelection()
{
    return selection;
}

/**
 * @brief Return the mutation range
 * 
 * @return double mutation range
 */
double Population::getMutRange()
{
    return mutRange;
}

/**
 * @brief Return the mutation probability
 * 
 * @return double 
 */
double Population::getMutProbability()
{
    return mutProbability;
}

/**
 * @brief return the mutation precision
 * 
 * @return int mutation precision
 */
int Population::getMutPrecision()
{
    return mutPrecision;
}

/**
 * @brief return the elitism rate
 * 
 * @return double elitism rate
 */
double Population::getElitismRate()
{
    return elitismRate;
}

/**
 * @brief return the crossover rate
 * 
 * @return double crossover rate
 */
double Population::getCrossoverRate()
{
    return crossoverRate;
}

/**
 * @brief return the scaling factor
 * 
 * @return double scaling factor
 */
double Population::getScale()
{
    return scale;
}

/**
 * @brief Return another scaling factor
 * 
 * @return double another scaling factor
 */
double Population::getLambda()
{
    return lambda;
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
        if (best < cost[i])
        {
            best = cost[i];
            index = i;
        }
    }

    // return the population at the best index
    return index;
}

/**
 * @brief Generates the costs of every solution vector
 * 
 */
void Population::generateAllCosts()
{
    // calculate the fitness for every solution
    for (int i = 0; i < popSize; ++i)
        generateOneCost(i);
}

/**
 * @brief generates the cost of one solution vector
 * 
 * @param index Index of solution
 */
void Population::generateOneCost(const int index)
{
    // calcualate and set the fitness of the specified solution
    cost[index] = runSolution(population[index], solutionSize, function);

    // incriment the functionCall variable
    incrimentFuncCalls();
}

/**
 * @brief Returns the cost of a solution vector
 * 
 * @param index     Index of solution vector
 * @return double   Fitness of solution vector
 */
double Population::getCost(const int index)
{
    return cost[index];
}

/**
 * @brief Returns the full cost vector
 * 
 * @return double* Cost array
 */
double* Population::getCost()
{
    return cost;
}

/**
 * @brief Generates the total cost of the population
 * 
 */
void Population::generateTotalCost()
{
    // reset the value
    totalFitness = 0;

    // sum up all of the fitnesses
    for (int i = 0; i < popSize; ++i)
        totalFitness += fitness[i];
}

/**
 * @brief Returns the total cost of the population
 * 
 * @return double Total cost
 */
double Population::getTotalCost()
{
    return totalCost;
}

/**
 * @brief Returns the total fitness of the population
 * 
 * @return double total fitness
 */
double Population::getTotalFitness()
{
    return totalFitness;
}

/**
 * @brief Generates all of the normalized fitnesses
 * 
 */
void Population::generateAllFitness()
{
    // generate all of the solutions' costs
    generateAllCosts();

    // for every element in the cost and fitness arrays
    for (int i = 0; i < solutionSize; ++i)
    {
        if(cost[i] >= 0)
            fitness[i] = 1 / (1 + cost[i]);
        else
            fitness[i] = 1 / (1 + std::abs(cost[i]));
        
    }
}

/**
 * @brief Generates total normalized fitnesses
 * 
 */
void Population::generateTotalFitness()
{
    // reset the value of totalFitness
    totalFitness = 0;

    // add all of the fitnesses together
    for (int i = 0; i < solutionSize; ++i)
        totalFitness += fitness[i];
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
 * @brief A method of insertion sort which will sort the
 *          population matrix and the fitness matrix.
 *        The population matrix will be sorted according to
 *          each solution vector's corresponding fitness. The
 *          fitness array will also be sorted as well.
 * 
 */
void Population::sortPopulation()
{
    // create a temporary array to hold a solution vector
    double* curSol = new double[solutionSize];

    // create a variabe to hold a fitness
    double curFit;

    // for every solution in the matrix
    for (int i = 0; i < popSize; ++i)
    {
        // get the fitness to sort
        curFit = fitness[i];

        // get the initial index to compare
        int j = i - 1;

        // for the remainder of the unsorted array
        while (j >= 0 && fitness[j] < curFit)   /* double check the right comparator */
        {
            // move the compared fitness forward one
            fitness[j+1] = fitness[j];

            // move the corresponding solution vector forward one position
            for (int x = 0; x < solutionSize; ++x)
                curSol[x] = population[j][x];
            
            // move the index backwards
            --j;
        }

        // move the initial fitness into its sorted position
        fitness[j+1] = curFit;

        // move the corresponding solution vector into its sorted position
        for (int x = 0; x < solutionSize; ++x)
            population[j+1][x] = curSol[x];
    }

    // destroy the array
    delete [] curSol;
}

/**
 * @brief Initializes a population
 * 
 */
void Population::initialize()
{
    // set up random number generation
    double seed = seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 mt(seed);

    // set up random distribution for (lowerBound, upperBound) and get a value
    uniform_real_distribution<> distr(lowerBound, upperBound);

    // randomize the population matrix
    for (int i = 0; i < popSize; ++i)
        for (int j = 0; j < solutionSize; ++j)
            population[i][j] = distr(mt);
            
    // calculate the cost
    generateAllCosts();
    generateAllFitness();
}

