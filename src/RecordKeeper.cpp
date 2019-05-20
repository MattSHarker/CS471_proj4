/**
 * @file RecordKeeper.cpp
 * @author Matthew
 * @brief Holds information about multiple optiization experimentations
 * @version 4.0
 * @date 2019-05-20
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
    // setup variables
    experimentations = param.experimentations;
    numFuncs         = param.numFuncs;
    populationSize   = param.popSize;
    solutionSize     = param.numDims;

    // setup historicGBest
    historicGBest = new double[experimentations];

    // setup historicPBest
    historicPBest = new double*[populationSize];
    for (int i = 0; i < populationSize; ++i)
        historicPBest[i] = new double[experimentations];

    // setup historicBestFit and historicWorstFit
    historicBestFit  = new double[experimentations];
    historicWorstFit = new double[experimentations];

    // setup historicFit
    historicFit = new double*[populationSize];
    for (int i = 0; i < populationSize; ++i)
        historicFit[i] = new double[experimentations];

    // setup finalFit
    finalFit = new double*[populationSize];
    for (int i = 0; i < populationSize; ++i)
        finalFit[i] = new double[experimentations];

    // setup timeTaken
    timeTaken = new double[experimentations];

    // setup finalFuncCalls
    finalFuncCalls = new int[experimentations];
}

/**
 * @brief Destroy the Record Keeper:: Record Keeper object
 * 
 */
RecordKeeper::~RecordKeeper()
{
    // destroy historicGBest
    if (historicGBest != nullptr)
        delete[] historicGBest;
    
    // destroy historicPBest
    if (historicPBest != nullptr)
    {
        for (int i = 0; i < populationSize; ++i)
            delete[] historicPBest[i];
        delete[] historicPBest;
    }

    // destroy historicBestFit
    if (historicBestFit != nullptr)
        delete[] historicBestFit;
    
    // destroy historicWorstFit
    if (historicWorstFit != nullptr)
        delete[] historicWorstFit;

    // destroy historicFits
    if (historicFit != nullptr)
    {
        for (int i = 0; i < populationSize; ++i)
            delete[] historicFit[i];
        delete[] historicFit;
    } 

    // destroy timeTaken
    if (timeTaken != nullptr)
        delete[] timeTaken;

    // destroy finalFit
    if (finalFit != nullptr)
    {
        for (int i = 0; i < populationSize; ++i)
            delete[] finalFit[i];
        delete[] finalFit;
    }
    
    // destroy finalFuncCalls
    if (finalFuncCalls != nullptr)
        delete[] finalFuncCalls;
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
 * @brief Sets an element of the historicPBest matrix
 * 
 * @param newBest   The value to set the element to
 * @param vec       The vector the element being set is in
 * @param elem      The element of the vector to set
 */
void RecordKeeper::setHistoricPBest(double newBest, const int vec, const int elem)
{
    historicPBest[vec][elem] = newBest;
}

/**
 * @brief Returns the value of an element in the historicPBest matrix
 * 
 * @param vec       The vector the element is in
 * @param elem      The element of the vector to return
 * @return double   The value of the specified element
 */
double RecordKeeper::getHistoricPBest(const int vec, const int elem)
{
    return historicPBest[vec][elem];
}

/**
 * @brief Sets an element of the historicGBest matrix
 * 
 * @param newBest   The value to set the element to
 * @param vec       The vector the element being set is in
 * @param elem      The element of the vector to set
 */
void RecordKeeper::setHistoricGBest(double newBest, const int vec)
{
    historicGBest[vec] = newBest;
}

/**
 * @brief Returns the value of an element in the historicGBest matrix
 * 
 * @param vec       The vector the element is in
 * @param elem      The element of the vector to return
 * @return double   The value of the specified element
 */
double RecordKeeper::getHistoricGBest(const int vec)
{
    return historicGBest[vec];
}

/**
 * @brief Sets the value of one element of historic cost
 * 
 * @param histFit  New value
 * @param expr      Experiment of value
 * @param gen       Generation of the experiment
 */
void RecordKeeper::setHistoricFit(double histFit, const int vec, const int elem)
{
    historicFit[vec][elem] = histFit;
}

/**
 * @brief Sets the value of a vector in the historicFit matrix
 * 
 * @param histFit   The array of value to set
 * @param vec       The array to be written to
 */
void RecordKeeper::setHistoricFit(double* histFit, const int vec)
{
    for (int i = 0; i < populationSize; ++i)
        historicFit[i][vec] = histFit[i];
}

/**
 * @brief Returns one value from historicFit
 * 
 * @param expr      Experiment of value
 * @param gen       Generation of experiment
 * @return double   Value of historic cost
 */
double RecordKeeper::getHistoricFit(const int vec, const int elem)
{
    return historicFit[vec][elem];
}

/**
 * @brief Sets the value of an element in the historic best fit array
 * 
 * @param newBest   The new value to set the element to
 * @param elem      The element whose value is being changed
 */
void RecordKeeper::setHistoricBestFit(double newBest, const int elem)
{
    historicBestFit[elem] = newBest;
}

/**
 * @brief Sets the value of an element in the historiWorstFit array
 * 
 * @param newBest   The new value to set the element to
 * @param elem      The element whose value is being changed
 */
void RecordKeeper::setHistoricWorstFit(double newBest, const int elem)
{
    historicWorstFit[elem] = newBest;
}


/**
 * @brief Returns a value from an element in the historicBestFit array
 * 
 * @param elem      The element whose value is being returned
 * @return double   The value of the specified element
 */
double RecordKeeper::getHistoricBestFit(const int elem)
{
    return historicBestFit[elem];
}

/**
 * @brief Returns a value from an element in the historicWorstFit array
 * 
 * @param elem      The element whose value is being returned
 * @return double   The value of the specified element
 */
double RecordKeeper::getHistoricWorstFit(const int elem)
{
    return historicWorstFit[elem];
}

/**
 * @brief Sets an element of the finalFit matrix
 * 
 * @param newFit    The value to set the specified element to
 * @param vec       The vector containing the element to be set
 * @param elem      The element whose value is being set
 */
void RecordKeeper::setFinalFit(double newFit, const int vec, const int elem)
{
    finalFit[vec][elem] = newFit;
}


/**
 * @brief Returns a value from finalFit
 * 
 * @param expr      The experimentation
 * @param pop       The Population
 * @return double   The value from finalFit
 */
double RecordKeeper::getFinalFit(const int expr, const int pop)
{
    return finalFit[expr][pop];
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
 * @brief Sets the value of timeTaken
 * 
 * @param newTime   The new value for timeTaken
 * @param expr      The experiment
 */
void RecordKeeper::setTimeTaken(double newTime, const int expr)
{
    timeTaken[expr] = newTime;
}

/**
 * @brief Returns a value from timeTaken
 * 
 * @param expr      The index of the value to return
 * @return double   The value veing returned
 */
double RecordKeeper::getTimeTaken(const int expr)
{
    return timeTaken[expr];
}





