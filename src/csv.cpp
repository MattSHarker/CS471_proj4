
/**
 * @file csvgenerator.cpp
 * @author Matthew Harker
 * @brief File dedicated to functions that create CSV files
 * 
 * @version 4.0
 * @date 2019-04-22
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "csv.h"

using namespace std;


void particleCSVs(Population** pops, RecordKeeper** rks)
{
    cout << "creating Particle Swarm CSV files\n";

    // create a csv for each function
    for (int i = 0; i < rks[0]->getNumFuncs(); ++i)
    {
        particlePBestFit(rks[i], i);
    }

    particleGBestFit(rks);

    // print out a confirmation
    cout << "csv files have been created for Particle Swarm Optimization\n";
}



void particlePBestFit(RecordKeeper* rk, const int func)
{
    // set the filename (and path) for the csv
    string pathName = "results/PSO/personalBest/psoPBestFit-Func";
    pathName += to_string(func);
    pathName += ".csv";

    // create or open the csv
    ofstream csv(pathName);
    
    //for each particle, write the pBest
    for (int i = 0; i < rk->getPopulationSize(); ++i)
    {
        // write the first cost to prevent extra commas
        csv << rk->getHistoricPBest(i, 0);

        // write the rest of the experimentations
        for (int j = 1; j < rk->getExperimentations(); ++j)
            csv << "," << rk->getHistoricPBest(i, j);
        
        // add a newline
        csv << '\n';
    }

    // close the csv file
    csv.close();
}

void particleGBestFit(RecordKeeper** rks)
{
     // set the filename (and path) for the csv
    string pathName = "results/PSO/globalBest/psoGBestFit.csv";

    // create or open the csv
    ofstream csv(pathName);
    
    //for each function, write the gBest
    for (int i = 0; i < rks[0]->getNumFuncs(); ++i)
    {
        // write the first cost to prevent extra commas
        csv << rks[i]->getHistoricGBest(0);

        // write the rest of the experimentations
        for (int j = 1; j < rks[0]->getExperimentations(); ++j)
            csv << "," << rks[i]->getHistoricGBest(j);
        
        // add a newline
        csv << '\n';
    }

    // close the csv file
    csv.close();
}




