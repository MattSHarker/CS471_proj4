
/**
 * @file main.cpp
 * @author  Matthew Harker
 * @brief   Project 4 for CS470. This program run a population of
 *          solution vectors through Particle Swarm algorithm,
 *          Firefly algorthim, and Harmony Search algorithm then
 *          print all the results to csv files.
 * 
 * @version 4.0
 * @date 2019-05-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <iostream>
#include "unistd.h"

#include "csv.h"
#include "firefly.h"
#include "harmony.h"
#include "Parameters.h"
#include "particleSwarm.h"
#include "Population.h"
#include "RecordKeeper.h"

using namespace std;

/**
 * @brief   The Main function. This will run the Patricle Swarm,
 *              
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

    // run PSO
    particleSwarm(pops, rks);
    particleCSVs(rks);

    // run FFA
    firefly(pops, rks);
    fireflyCSVs(rks);

    // run HS
    harmony(pops, rks);
    harmonyCSVs(rks);

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
