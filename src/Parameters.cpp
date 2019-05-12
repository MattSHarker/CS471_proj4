
/**
 * @file files.cpp
 * @author  Matthew Harker
 * @brief   C++ file that provides utilities.
 *          This file contains all of the various utilities
 *          that provide extra functions, such as reading in
 *          parameters, and setting values in vectors.
 * 
 * @version 3.0
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
    ifstream file1 ("parameters/functionParams.txt");

    if (file1.is_open())
    {  
        // variables to retreive parameters
        string line;
        string range;

        // read the info in from the file
        file1 >> params.numVecs;
        file1 >> params.numDims;
        file1 >> params.numFuncs;

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
        cout << "Function parameter file not found\n";
        exit(EXIT_FAILURE);
    }
    
    // when all parameters are read in, close the file
    file1.close();

    // open the population parameters file
    ifstream file2 ("parameters/optimizationParams.txt");

    // if the file was succesfully opened
    if (file2.is_open())
    {
        // retreive the variables
        file2 >> params.experimentations;
        file2 >> params.popSize;
        file2 >> params.dampener;
        file2 >> params.velConst1;
        file2 >> params.velConst2;
        file2 >> params.alpha;
        file2 >> params.beta;
        file2 >> params.gamma;

        // check variables to ensure they are within bounds
    }
    else
    {
        // if the file could not be found
        cout << "Optimization parameter file not found\n";
        exit(EXIT_FAILURE);
    }
    
    // close the file
    file2.close();

    // return the params object
    return params;
}


