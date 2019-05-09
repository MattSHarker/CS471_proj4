
/**
 * @file files.cpp
 * @author  Matthew Harker
 * @brief   C++ file that provides utilities.
 *          This file contains all of the various utilities
 *          that provide extra functions, such as reading in
 *          parameters, and setting values in vectors.
 * 
 * @version 1.1
 * @date 2019-04-22
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "functions.h"
#include "Parameters.h"

using namespace std;

/**
 * @brief   Helper function for Parameters:: getParameters().
 *          Sets up the two float arrays to the proper size.
 * 
 * @param numFuncs  The size of the two range arrays.
 *                  The size is directly related to the number of
 *                  functions being used in the program.
 */
void Parameters::setupRanges(const int numFuncs)
{
    lowRanges  = new float[numFuncs];
    highRanges = new float[numFuncs];
}

/**
 * @brief   Checks if a double is sufficiently close to M_PI.
 * 
 * @param   n       The value being checked.
 * @return  true    The value is PI.
 * @return  false   The value is not PI
 */
bool compareDoubles(const double x, const double y)
{
    return abs(x - y) <= 0.0000001 * abs(x);
}


/**
 * @brief   Ensures the correct amount of vectors.
 *          This program requires at least 30 vectors to be
 *          used to ensure proper results.
 * 
 * @param numVecs   The number of vectors being used.
 */
void checkVectors(const int numVecs)
{
    // the number of vectors must be at least 30
    if (numVecs < 30)
    {
        cout << "The number of vectors must be at least 30" << endl;
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief   Ensures a usable amount of functions.
 *          THe number of functions must be at least 1.
 * 
 * @param numFuncs  The number of functions being used
 */
void checkNumberOfFunctions(const int numFuncs)
{
    // must be at least 1 function
    if (numFuncs < 1)
    {
        cout << "There must be at lest 1 function being ran in this program\n";
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief   Ensures the correct amount of dimensions.
 *          This program requires that either 10, 20, or 30
 *          are to be used to ensure proper results.
 * 
 * @param dims  The number of dimensions the vectors contain.
 */
void checkDimensions(const int dims)
{
    // dimensions must be either 10, 20, or 30
    if (dims != 10 && dims != 20 && dims != 30)
    {
        cout << "The number of dimensions must be either 10, 20, or 30" << endl;
        exit(EXIT_FAILURE);
    }
}


/**
 * @brief   Ensures the step size is usable.
 *          The step size must be positive.
 * 
 * @param stepSize  How far the local searches will check for another solution
 */
void checkStepSize(const int stepSize)
{
    // step size must be positive
    if (stepSize < 0)
    {
        cout << "The step size must be positive\n";
        exit(EXIT_FAILURE);
    }
}

void checkPopSize(const int popSize)
{
    if (popSize < 200)
    {
        cout << "There must be at least 200 solutions for each population\n";
        exit(EXIT_FAILURE);
    }
}

void checkGenerations(const int gens)
{
    if (gens < 100)
    {
        cout << "There must be at least 100 generations\n";
        exit(EXIT_FAILURE);
    }
}

void checkExperimentations(const int exp)
{
    if (exp < 50)
    {
        cout << "There must be at least 50 experimentations\n";
        exit(EXIT_FAILURE);
    }
}

void checkElitismRate(const double rate)
{
    if (rate > 1.0 || rate < 0.0)
    {
        cout << "The elitism rate must be between 0 and 1\n";
    }
}

/**
 * @brief   Reads in parameters from a file and returns
 *          an object filled with the values.
 * 
 * @return Parameters   The object filled with the read in parameters
 */
Parameters getParameters()
{
    // create a Parameters object to be returned
    Parameters params;

    // open first file for matrix info
    ifstream file1 ("parameters/matrixParams.txt");

    if (file1.is_open())
    {  
        // variables to retreive parameters
        string line;
        string range;

        // read the info in from the file
        file1 >> params.numVecs;
        file1 >> params.numDims;
        file1 >> params.numFuncs;

        // check the variables
        checkVectors(params.numVecs);
        checkDimensions(params.numDims);
        checkNumberOfFunctions(params.numFuncs);

        // read in the info for the ranges
        params.setupRanges(params.numFuncs);

        // for each function
        for (int i = 0; i < params.numFuncs; ++i)
        {
            // retreive the full line
            file1 >> line;

            // tokenize the line by ',' into the string stream
            stringstream ss(line);
            getline(ss, range, ',');

            // set the low range
            params.lowRanges[i] = stof(range);

            // get the value of the high range in the sstream
            getline(ss, range, ',');

            // if the input is the string "PI" manually set the value
            if (!range.compare("PI"))    // in case the value is pi
                params.highRanges[i] = M_PI;
            else
                params.highRanges[i] = stof(range);
        }            
    }
    else
    {
        // if the file could not be opened
        cout << "Matrix parameter file not found\n";
        exit(EXIT_FAILURE);
    }
    
    // when all parameters are read in, close the file
    file1.close();

    // open the population parameters file
    ifstream file2 ("parameters/populationParams.txt");

    // if the file was succesfully opened
    if (file2.is_open())
    {
        // retreive the variables
        file2 >> params.experimentations;
        file2 >> params.popSize;
        file2 >> params.generations;
        file2 >> params.crProbability;
        file2 >> params.mutProbability;
        file2 >> params.mutRange;
        file2 >> params.mutPrecision;
        file2 >> params.elitismRate;
        file2 >> params.scale;
        file2 >> params.lambda;
        file2 >> params.strategies;
        file2 >> params.selection;

        // check variables to ensure they are within bounds
        checkPopSize(params.popSize);
        checkGenerations(params.generations);
        checkExperimentations(params.experimentations);
        checkElitismRate(params.elitismRate);
    }
    else
    {
        // if the file could not be found
        cout << "Population parameter file not found\n";
        exit(EXIT_FAILURE);
    }
    
    // close the file
    file2.close();


    // return the params object
    return params;
}


