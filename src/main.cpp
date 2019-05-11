
/**
 * @file main.cpp
 * @author  Matthew Harker
 * @brief   Project 3 for CS470. This program run a population of
 *          solution vectors through a genetic algorithm and a
 *          differential evolution algorthim, then print all the 
 *          results to csv files.
 * 
 * @version 3.0
 * @date 2019-05-03
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <iostream>

#include "csv.h"
#include "differentialEvolution.h"
#include "geneticAlg.h"
#include "Parameters.h"
#include "Population.h"
#include "RecordKeeper.h"

using namespace std;

/**
 * @brief   The Main function. This will run the genetic algorithm
 *          and the Differential Evolution Algorithm and create
 * 
 * @return  int Indicates status of how the program ended.
 */
int main()
{
    // Create a Parameters object
    Parameters params = getParameters();

    // create an array of Population objects
    Population** pops = new Population*[params.numFuncs];
    for (int i = 0; i < params.numFuncs; ++i)
        pops[i] = new Population(params, i);

    // create an array RecordKeeper objects
    RecordKeeper** rks = new RecordKeeper*[params.numFuncs];
    for (int i = 0; i < params.numFuncs; ++i)
        rks[i] = new RecordKeeper(params);

    // run the genetic algorithm
    cout << "Starting Genetic Algorithm...\n";
    geneticAlgorithm(pops, rks);
    cout << "Genetic Algorithm Completed\n";

    // print the results to csv files
    geneticCSVs(pops, rks);

    // run the differentail evolution
    cout << "Starting Differential Evolution...\n";
    differentialEvolution(pops, rks);
    cout << "Differential Evolution Completed\n";

    // print the results to csv files
    differentialCSVs(pops, rks);

    // destroy the Population \m/ 
    for (int i = 0; i < params.numFuncs; ++i)
        delete pops[i];
    delete [] pops;

    // destroy the RecordKeeper 
    for (int i = 0; i < params.numFuncs; ++i)
        delete rks[i];
    delete [] rks;

    return 0;
}
