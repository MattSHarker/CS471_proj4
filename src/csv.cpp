
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


void particleCSVs(RecordKeeper** rks)
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


void fireflyCSVs(RecordKeeper** rks)
{
    cout << "creating Firefly CSV files\n";

    // create the CSVs
    fireflyHistBestFit(rks);
    fireflyHistWorstFit(rks);
    fireflyFuncCalls(rks);

    // print out a confirmation
    cout << "csv files have been created for Firefly Algorithm\n";

}

void fireflyHistBestFit(RecordKeeper** rks)
{
     // set the filename (and path) for the csv
    string pathName = "results/FFA/histBestFit/ffaBestFit.csv";

    // create or open the csv
    ofstream csv(pathName);
    
    //for each function, write the gBest
    for (int i = 0; i < rks[0]->getNumFuncs(); ++i)
    {
        // write the first cost to prevent extra commas
        csv << rks[i]->getHistoricBestFit(0);

        // write the rest of the experimentations
        for (int j = 1; j < rks[0]->getExperimentations(); ++j)
            csv << "," << rks[i]->getHistoricBestFit(j);
        
        // add a newline
        csv << '\n';
    }

    // close the csv file
    csv.close();
}

void fireflyHistWorstFit(RecordKeeper** rks)
{
    // set the filename (and path) for the csv
    string pathName = "results/FFA/histWorstFit/ffaWorstFit.csv";

    // create or open the csv
    ofstream csv(pathName);
    
    //for each function, write the gBest
    for (int i = 0; i < rks[0]->getNumFuncs(); ++i)
    {
        // write the first cost to prevent extra commas
        csv << rks[i]->getHistoricWorstFit(0);

        // write the rest of the experimentations
        for (int j = 1; j < rks[0]->getExperimentations(); ++j)
            csv << "," << rks[i]->getHistoricWorstFit(j);
        
        // add a newline
        csv << '\n';
    }

    // close the csv file
    csv.close();
}


void fireflyFuncCalls(RecordKeeper** rks)
{
     // set the filename (and path) for the csv
    string pathName = "results/FFA/funcCalls/ffaFuncCalls.csv";

    // create or open the csv
    ofstream csv(pathName);
    
    //for each function, write the gBest
    for (int i = 0; i < rks[0]->getNumFuncs(); ++i)
    {
        // write the first cost to prevent extra commas
        csv << rks[i]->getFinalFuncCalls(0);

        // write the rest of the experimentations
        for (int j = 1; j < rks[0]->getExperimentations(); ++j)
            csv << "," << rks[i]->getFinalFuncCalls(j);
        
        // add a newline
        csv << '\n';
    }

    // close the csv file
    csv.close();
}


void harmonyCSVs(RecordKeeper** rks)
{
    cout << "creating Harmony CSV files\n";

    // create the CSVs
    harmonyHistBestFit(rks);
    harmonyHistWorstFit(rks);
    harmonyFuncCalls(rks);
    harmonyTimeTaken(rks);

    cout << "csv files have been created for Harmony Search Algorithm\n";
}


void harmonyHistBestFit(RecordKeeper** rks)
{
     // set the filename (and path) for the csv
    string pathName = "results/HSA/histBestFit/hsaBestFit.csv";

    // create or open the csv
    ofstream csv(pathName);
    
    //for each function, write the gBest
    for (int i = 0; i < rks[0]->getNumFuncs(); ++i)
    {
        // write the first cost to prevent extra commas
        csv << rks[i]->getHistoricBestFit(0);

        // write the rest of the experimentations
        for (int j = 1; j < rks[0]->getExperimentations(); ++j)
            csv << "," << rks[i]->getHistoricBestFit(j);
        
        // add a newline
        csv << '\n';
    }

    // close the csv file
    csv.close();
}


void harmonyHistWorstFit(RecordKeeper** rks)
{
     // set the filename (and path) for the csv
    string pathName = "results/HSA/histWorstFit/hsaWorstFit.csv";

    // create or open the csv
    ofstream csv(pathName);
    
    //for each function, write the gBest
    for (int i = 0; i < rks[0]->getNumFuncs(); ++i)
    {
        // write the first cost to prevent extra commas
        csv << rks[i]->getHistoricWorstFit(0);

        // write the rest of the experimentations
        for (int j = 1; j < rks[0]->getExperimentations(); ++j)
            csv << "," << rks[i]->getHistoricWorstFit(j);
        
        // add a newline
        csv << '\n';
    }

    // close the csv file
    csv.close();
}

void harmonyFuncCalls(RecordKeeper** rks)
{
     // set the filename (and path) for the csv
    string pathName = "results/HSA/funcCalls/hsaFuncCalls.csv";

    // create or open the csv
    ofstream csv(pathName);
    
    //for each function, write the gBest
    for (int i = 0; i < rks[0]->getNumFuncs(); ++i)
    {
        // write the first cost to prevent extra commas
        csv << rks[i]->getFinalFuncCalls(0);

        // write the rest of the experimentations
        for (int j = 1; j < rks[0]->getExperimentations(); ++j)
            csv << "," << rks[i]->getFinalFuncCalls(j);
        
        // add a newline
        csv << '\n';
    }

    // close the csv file
    csv.close();
}

void harmonyTimeTaken(RecordKeeper** rks)
{
    // set the filename (and path) for the csv
    string pathName = "results/HSA/timeTaken/hsaTimeTaken.csv";

    // create or open the csv
    ofstream csv(pathName);
    
    //for each function, write the gBest
    for (int i = 0; i < rks[0]->getNumFuncs(); ++i)
    {
        // write the first cost to prevent extra commas
        csv << rks[i]->getTimeTaken(0);

        // write the rest of the experimentations
        for (int j = 1; j < rks[0]->getExperimentations(); ++j)
            csv << "," << rks[i]->getTimeTaken(j);
        
        // add a newline
        csv << '\n';
    }

    // close the csv file
    csv.close();
}




