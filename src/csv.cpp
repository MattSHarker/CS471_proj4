
/**
 * @file csvgenerator.cpp
 * @author Matthew Harker
 * @brief File dedicated to functions that create CSV files
 * 
 * @version 3.0
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
#include "RecordKeeper.h"

using namespace std;

/**
 * @brief Prints all genetic algorithm CSVs
 * 
 * @param pops  Population array
 * @param rks   RecordKeeper array
 */
void geneticCSVs( Population** pops, RecordKeeper** rks)
{
    // create a csv for each function
    for (int i = 0; i < rks[0]->getNumFuncs(); ++i)
        geneticHistoricCosts(rks[i], i);

    // create other CSV files
    geneticFinalBestFitness(rks, pops);
    geneticTime(rks);
    geneticFuncCalls(rks);

    // print out a confirmation
    cout << "csv files have been created for the genetic algorithm\n";
}


/**
 * @brief Generates CSVs for GA finalBestFitness
 * 
 * @param rks   RecordKeeper array
 * @param pops  Population array
 */
void geneticFinalBestFitness(RecordKeeper** rks, Population** pops)
{
    // create the filename (and path) for the csv
    string pathName = "results/geneticAlgorithm/finalBestFitness/gaFinalBestFit.csv";

    // create or open the csv
    ofstream csv(pathName);
    
    //for each function
    for (int i = 0; i < rks[0]->getNumFuncs(); ++i)
    {
        // write the costs from each population
        //
        // write the first cost to prevent extra commas
        csv << pops[i]->getCost(0);

        // write the rest of the experimentations
        for (int j = 1; j < rks[0]->getExperimentations(); ++j)
            csv << "," << pops[i]->getCost(j);
        
        // add a newline
        csv << '\n';
    }

    // close the csv file
    csv.close();
}

/**
 * @brief Creates CSVs for genetic algorithm's historic costs
 * 
 * @param rk    Record Keeper object
 * @param func  Function that was ran
 */
void geneticHistoricCosts(RecordKeeper* rk, const int func)
{
    // get the solution dimension for easier reading
    int solDim = rk->getSolutionSize();

    // create the filename (and path) for the csv
    string pathName = "results/geneticAlgorithm/historicBestFitness/gaHistFit-func";
    pathName += to_string(func+1);
    pathName += ".csv";

    // create or open the csv
    ofstream csv(pathName);

    // for each experiment
    for (int i = 0; i < rk->getExperimentations(); ++i)
    {
        // write the first element for no extra commas
        csv << rk->getHistoricCost(i, 0);

        // for generation
        for (int j = 1; j < rk->getGenerations(); ++j)
            csv << "," << rk->getHistoricCost(i, j);
        
        // create a newline
        csv << '\n';
    }

    // close the csv file
    csv.close();
}


/**
 * @brief Prints experimentation time of a RecordKeeper
 * 
 * @param rk RecordKeeper object
 */
void geneticTime(RecordKeeper** rk)
{
    // create the filename (and path) for the csv
    string pathName = "results/geneticAlgorithm/times/gaTime.csv";

    // create or open the csv
    ofstream csv(pathName);

    // for each function
    for (int i = 0; i < rk[0]->getNumFuncs(); ++i)
    {
        // get the first to prevent extra commas
        csv << rk[i]->getExpTime(0);

        // write the rest
        for (int j = 1; j < rk[0]->getExperimentations(); ++j)
            csv << "," << rk[i]->getExpTime(j);
        
        // create a newline
        csv << '\n';
    }

    // close the csv file
    csv.close();
}

/**
 * @brief prints function calls of the experimentations
 * 
 * @param rk RecordKeeper objects
 */
void geneticFuncCalls(RecordKeeper** rk)
{
    // create the filename (and path) for the csv
    string pathName = "results/geneticAlgorithm/functionCalls/gaCalls.csv";

    // create or open the csv
    ofstream csv(pathName);

    // for each function
    for (int i = 0; i < rk[0]->getNumFuncs(); ++i)
    {
        // get the first to prevent extra commas
        csv << rk[i]->getFinalFuncCalls(0);

        // write the rest
        for (int j = 1; j < rk[0]->getExperimentations(); ++j)
            csv << "," << rk[i]->getFinalFuncCalls(j);
        
        // create a newline
        csv << '\n';
    }

    // close the csv file
    csv.close();
}



/**
 * @brief Generates all Differential Evolution CSVs
 * 
 * @param pops  Population array
 * @param rks   RecordKeeper array
 */
void differentialCSVs(Population** pops, RecordKeeper** rks)
{
    // for each strategy
    for (int i = 0; i < rks[0]->getStrategies(); ++i)
    {
        // create a csv for each function
        for (int j = 0; j < rks[0]->getNumFuncs(); ++j)
            differentialHistoricCosts(rks[j], i, j);

        differentialFinalBestFitness(rks, pops, i);
    }

    // create other CSV files
    differentialTime(rks);
    differentialFuncCalls(rks);

    // print out a confirmation
    cout << "csv files have been created for the differential evolution\n";
}

/**
 * @brief Prints final best fitnesses for differential evolution
 * 
 * @param rks   RecordKeeper array
 * @param pops  Population array
 * @param strat Strategy
 */
void differentialFinalBestFitness(RecordKeeper** rks, Population** pops, const int strat)
{
    // create the filename (and path) for the csv
    string pathName = "results/differentialEvolution/finalBestFitness/deFinalBestFitStrat-";
    pathName += to_string(strat+1);
    pathName += ".csv";

    // create or open the csv
    ofstream csv(pathName);
    
    //for each function
    for (int i = 0; i < rks[0]->getNumFuncs(); ++i)
    {
        // write the first cost to prevent extra commas
        csv << pops[i]->getCost(0);

        // write the rest of the experimentations
        for (int j = 1; j < rks[0]->getExperimentations(); ++j)
            csv << "," << pops[i]->getCost(j);
        
        // add a newline
        csv << '\n';
    }

    // close the csv file
    csv.close();
}

/**
 * @brief Genetares CSV of historic costs for differential Evolution
 * 
 * @param rk    RecordKeeper object
 * @param strat Strategy
 * @param func  Function
 */
void differentialHistoricCosts(RecordKeeper* rk, const int strat, const int func)
{
   // get the solution dimension for easier reading
    int solDim = rk->getSolutionSize();

    // create the filename (and path) for the csv
    string pathName = "results/differentialEvolution/historicBestFitness/strat";
    pathName += to_string(strat+1);
    pathName += "/deHistFit-func";
    pathName += to_string(func+1);
    pathName += ".csv";

    // create or open the csv
    ofstream csv(pathName);

    // for each experiment
    for (int i = 0; i < rk->getExperimentations(); ++i)
    {
        // write the first element for no extra commas
        csv << rk->getHistoricCost(i, 0);

        // for the rest of the generation
        for (int j = 1; j < rk->getGenerations(); ++j)
            csv << "," << rk->getHistoricCostStrats(strat, i, j);
        
        // create a newline
        csv << '\n';
    }

    // close the csv file
    csv.close();
}


/**
 * @brief Creates CSV of experiment time take for differential evolution
 * 
 * @param rk RecordKeeper object
 */
void differentialTime(RecordKeeper** rk)
{
    // create the filename (and path) for the csv
    string pathName = "results/differentialEvolution/times/deTime.csv";

    // create or open the csv
    ofstream csv(pathName);

    // for each function
    for (int i = 0; i < rk[0]->getNumFuncs(); ++i)
    {
        // get the first to prevent extra commas
        csv << rk[i]->getExpTime(0);

        // write the rest
        for (int j = 1; j < rk[0]->getExperimentations(); ++j)
            csv << "," << rk[i]->getExpTime(j);
        
        // create a newline
        csv << '\n';
    }

    // close the csv file
    csv.close();
}

/**
 * @brief creates CSVs of function calls for differential evolution
 * 
 * @param rk RecordKeeper array
 */
void differentialFuncCalls(RecordKeeper** rk)
{
    // create the filename (and path) for the csv
    string pathName = "results/differentialEvolution/functionCalls/deCalls.csv";

    // create or open the csv
    ofstream csv(pathName);

    // for each function
    for (int i = 0; i < rk[0]->getNumFuncs(); ++i)
    {
        // get the first to prevent extra commas
        csv << rk[i]->getFinalFuncCalls(0);

        // write the rest
        for (int j = 1; j < rk[0]->getExperimentations(); ++j)
            csv << "," << rk[i]->getFinalFuncCalls(j);
        
        // create a newline
        csv << '\n';
    }

    // close the csv file
    csv.close();
}




