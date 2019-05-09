/**
 * @file RecordKeeper.cpp
 * @author Matthew
 * @brief Holds information about multiple optiization experimentations
 * @version 1.0
 * @date 2019-05-03
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <iostream>
#include "RecordKeeper.h"

using namespace std;

/**
 * @brief Construct a new Record Keeper:: Record Keeper object
 * 
 * @param param Parameters object to set variables
 */
RecordKeeper::RecordKeeper(Parameters param)
{
    experimentations = param.experimentations;
    generations      = param.generations;
    numFuncs         = param.numFuncs;
    populationSize   = param.popSize;
    solutionSize     = param.numDims;
    strategies       = param.strategies;

    // set up historicCostStrats
    historicCostStrats = new double**[strategies];
    for (int i = 0; i < strategies; ++i)
    {
        historicCostStrats[i] = new double*[experimentations];

        for (int j = 0; j < experimentations; ++j)
            historicCostStrats[i][j] = new double[generations];
    }

    // set up finalCostStrats
    finalCostStrats = new double**[strategies];
    for (int i = 0; i < strategies; ++i)
    {
        finalCostStrats[i] = new double*[experimentations];

        for (int j = 0; j < experimentations; ++j)
            finalCostStrats[i][j] = new double[populationSize];
    }


    // setup historicCost
    historicCost = new double*[experimentations];
    for (int i = 0; i < experimentations; ++i)
        historicCost[i] = new double[generations];

    // setup expTime
    expTime = new double[experimentations];

    // setup finalCosts
    finalCosts = new double*[experimentations];
    for (int i = 0; i < experimentations; ++i)
        finalCosts[i] = new double[populationSize];

    // setup finalFuncCalls
    finalFuncCalls = new int[experimentations];
}

/**
 * @brief Destroy the Record Keeper:: Record Keeper object
 * 
 */
RecordKeeper::~RecordKeeper()
{
    // destroy historicCostStrats
    if (historicCostStrats != nullptr)
    {
        for (int i = 0; i < strategies; ++i)
        {
            for (int j = 0; j < experimentations; ++j)
                delete [] historicCostStrats[i][j];
            delete [] historicCostStrats[i];
        }
        
        delete [] historicCostStrats;
    }


    // destroy finalCostStrats
    if (finalCostStrats != nullptr)
    {
        for (int i = 0; i < strategies; ++i)
        {
            for (int j = 0; j < experimentations; ++j)
                delete [] finalCostStrats[i][j];
            delete [] finalCostStrats[i];
        }
        delete [] finalCostStrats;
    }


    // destroy historicCosts
    if (historicCost != nullptr)
    {
        for (int i = 0; i < experimentations; ++i)
            delete [] historicCost[i];
        delete [] historicCost;
    }

    // destroy expTime
    if (expTime != nullptr)
        delete [] expTime;

    // destroy finalCost
    if (finalCosts != nullptr)
    {
        for (int i = 0; i < experimentations; ++i)
            delete [] finalCosts[i];

        delete [] finalCosts;
    }
    
    // destroy finalFuncCalls
    if (finalFuncCalls != nullptr)
        delete [] finalFuncCalls;
}

/**
 * @brief Returns the number of experimentations
 * 
 * @return int number of generations
 */
int RecordKeeper::getExperimentations()
{
    return experimentations;
}

/**
 * @brief Returns the number of generations
 * 
 * @return int number of generations
 */
int RecordKeeper::getGenerations()
{
    return generations;
}

/**
 * @brief Returns the total number of functions
 * 
 * @return int number of functions
 */
int RecordKeeper::getNumFuncs()
{
    return numFuncs;
}

/**
 * @brief returns the number of solution vectors in the population
 * 
 * @return int Number of solution vectors
 */
int RecordKeeper::getPopulationSize()
{
    return populationSize;
}

/**
 * @brief Returns the size of each solution
 * 
 * @return int Size of solutions
 */
int RecordKeeper::getSolutionSize()
{
    return solutionSize;
}

/**
 * @brief returns the number of strategies
 * 
 * @return int 
 */
int RecordKeeper::getStrategies()
{
    return strategies;
}

/**
 * @brief Sets the value of one element of historic cost
 * 
 * @param histCost  New value
 * @param expr      Experiment of value
 * @param gen       Generation of the experiment
 */
void RecordKeeper::setHistoricCost(double histCost, const int expr, const int gen)
{
    historicCost[expr][gen] = histCost;
}

/**
 * @brief Returns one value from historicCost
 * 
 * @param expr      Experiment of value
 * @param gen       Generation of experiment
 * @return double   Value of historic cost
 */
double RecordKeeper::getHistoricCost(const int expr, const int gen)
{
    return historicCost[expr][gen];
}

/**
 * @brief Sets one value of historic cost strats
 * 
 * @param newCost   New value
 * @param strat     The strategy
 * @param expr      The experimentation of the strategy
 * @param gen       The generation of the experimentation
 */
void RecordKeeper::setHistoricCostStrats(double newCost, const int strat, const int expr, const int gen)
{
    historicCostStrats[strat][expr][gen] = newCost;
}

/**
 * @brief Returns one value from historicCostStrats
 * 
 * @param strat     The strategy
 * @param expr      The experiment of the strategy
 * @param gen       The generation of the experiment
 * @return double   The value of histCostStrats
 */
double RecordKeeper::getHistoricCostStrats(const int strat, const int expr, const int gen)
{
    return historicCostStrats[strat][expr][gen];
}

/**
 * @brief Sets one value of finalCostStrats
 * 
 * @param newCost   The new value
 * @param strat     The strategy
 * @param expr      The experiment of the strategy
 * @param gen       The generation of the strategy
 */
void RecordKeeper::setFinalCostStrats(double newCost, const int strat, const int expr, const int gen)
{
    finalCostStrats[strat][expr][gen] = newCost;
}

/**
 * @brief Returns pne value from finalCostStrats
 * 
 * @param strat     The strategy
 * @param expr      The experiment of the strategy
 * @param gen       The generation of the strategy
 * @return double   The value being returned
 */
double RecordKeeper::getFinalCostStrats(const int strat, const int expr, const int gen)
{
    return finalCostStrats[strat][expr][gen];
}

/**
 * @brief Sets an array of finalCost
 * 
 * @param pop   The population
 * @param expr  The index of the cost array
 */
void RecordKeeper::setFinalCost(Population* pop, const int expr)
{
    // write each cost to the corresponding experimentation array
    for (int i = 0; i < populationSize; ++i)
    {
        finalCosts[expr][i] = pop->getCost(i);
    }
}

/**
 * @brief Returns a value from finalCost
 * 
 * @param expr      The experimentation
 * @param pop       The Population
 * @return double   The value from finalCosts
 */
double RecordKeeper::getFinalCost(const int expr, const int pop)
{
    return finalCosts[expr][pop];
}

/**
 * @brief Sets a value in finalFuncCalls
 * 
 * @param newCalls  The value to set
 * @param expr      The experiment
 * 
 */
void RecordKeeper::setFinalFuncCalls(int newCalls, const int expr)
{
    finalFuncCalls[expr] = newCalls;
}

/**
 * @brief Returns a value from finalFuncCalls
 * 
 * @param expr  The experiment
 * @return int  The Value from finalFuncCalls
 */
int RecordKeeper::getFinalFuncCalls(const int expr)
{
    return finalFuncCalls[expr];
}

/**
 * @brief Sets the value of expTime
 * 
 * @param newTime   The new value for expTime
 * @param expr      The experiment
 */
void RecordKeeper::setExpTime(double newTime, const int expr)
{
    expTime[expr] = newTime;
}

/**
 * @brief Returns a value from expTime
 * 
 * @param expr      The index of the value to return
 * @return double   The value veing returned
 */
double RecordKeeper::getExpTime(const int expr)
{
    return expTime[expr];
}





