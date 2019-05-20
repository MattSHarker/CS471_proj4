
/**
 * @file csvgenerator.cpp
 * @author Matthew Harker
 * @brief File dedicated to functions that create CSV files
 * 
 * @version 4.0
 * @date 2019-05-20
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

/**
 * @brief Creates every CSV file for PSO
 * 
 * @param rks The objects containing the information about the optimization process
 */
void particleCSVs(RecordKeeper** rks)
{
    cout << "creating Particle Swarm CSV files\n";

    // create a csv for each function
    particleGBestFit(rks);
    particleWorstFit(rks);
    particleFinalFits(rks);
    particleFuncCalls(rks);
    particleTimeTaken(rks);

    // print out a confirmation
    cout << "csv files have been created for Particle Swarm Optimization\n";
}

/**
 * @brief Creates a CSV file for PSO containing info on gBestFit
 * 
 * @param rks The objects containing the information about the optimization process
 */
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

/**
 * @brief Creates a CSV file for PSO containing info on worstFit
 * 
 * @param rks The objects containing the information about the optimization process
 */
void particleWorstFit(RecordKeeper** rks)
{
    // set the filename (and path) for the csv
    string pathName = "results/PSO/histWorstFit/psoWorstFit.csv";

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

/**
 * @brief Creates a CSV file for PSO containing info on finalFits
 * 
 * @param rks The objects containing the information about the optimization process
 */
void particleFinalFits(RecordKeeper** rks)
{
    // set the filename (and path) for the csv
    string pathName = "results/PSO/finalFits/psoFinalFits.csv";

    // create or open the csv
    ofstream csv(pathName);
    
    //for each function, write the gBest
    for (int i = 0; i < rks[0]->getNumFuncs(); ++i)
    {
        // write the first cost to prevent extra commas
        csv << rks[i]->getFinalFit(0, 0);

        // write the rest of the experimentations
        for (int j = 1; j < rks[0]->getPopulationSize(); ++j)
            csv << "," << rks[i]->getFinalFit(j, 0);
        
        // add a newline
        csv << '\n';
    }

    // close the csv file
    csv.close();
}

/**
 * @brief Creates a CSV file for PSO containing info on funcCalls
 * 
 * @param rks The objects containing the information about the optimization process
 */
void particleFuncCalls(RecordKeeper** rks)
{
     // set the filename (and path) for the csv
    string pathName = "results/PSO/funcCalls/psoFuncCalls.csv";

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

/**
 * @brief Creates a CSV file for PSO containing info on timeTaken
 * 
 * @param rks The objects containing the information about the optimization process
 */
void particleTimeTaken(RecordKeeper** rks)
{
    // set the filename (and path) for the csv
    string pathName = "results/PSO/timeTaken/psoTimeTaken.csv";

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

/**
 * @brief Creates every CSV file for FFA 
 * 
 * @param rks The objects containing the information about the optimization process
 */
void fireflyCSVs(RecordKeeper** rks)
{
    cout << "creating Firefly CSV files\n";

    // create the CSVs
    fireflyHistBestFit(rks);
    fireflyHistWorstFit(rks);
    fireflyFinalFits(rks);
    fireflyFuncCalls(rks);
    fireflyTimeTaken(rks);

    // print out a confirmation
    cout << "csv files have been created for Firefly Algorithm\n";

}

/**
 * @brief Creates a CSV file for FFA containing info on bestFit
 * 
 * @param rks The objects containing the information about the optimization process
 */
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

/**
 * @brief Creates a CSV file for FFA containing info on worstFit
 * 
 * @param rks The objects containing the information about the optimization process
 */
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

/**
 * @brief Creates a CSV file for FFA containing info on finalFits
 * 
 * @param rks The objects containing the information about the optimization process
 */
void fireflyFinalFits(RecordKeeper** rks)
{
    // set the filename (and path) for the csv
    string pathName = "results/FFA/finalFits/ffaFinalFits.csv";

    // create or open the csv
    ofstream csv(pathName);
    
    //for each function, write the gBest
    for (int i = 0; i < rks[0]->getNumFuncs(); ++i)
    {
        // write the first cost to prevent extra commas
        csv << rks[i]->getFinalFit(0, 0);

        // write the rest of the experimentations
        for (int j = 1; j < rks[0]->getPopulationSize(); ++j)
            csv << "," << rks[i]->getFinalFit(j, 0);
        
        // add a newline
        csv << '\n';
    }

    // close the csv file
    csv.close();
}

/**
 * @brief Creates a CSV file for FFA containing info on funcCalls
 * 
 * @param rks The objects containing the information about the optimization process
 */
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

/**
 * @brief Creates a CSV file for FFA containing info on timeTaken
 * 
 * @param rks The objects containing the information about the optimization process
 */
void fireflyTimeTaken(RecordKeeper** rks)
{
    // set the filename (and path) for the csv
    string pathName = "results/FFA/timeTaken/ffaTimeTaken.csv";

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

/**
 * @brief Creates every CSV file for HSA
 * 
 * @param rks The objects containing the information about the optimization process
 */
void harmonyCSVs(RecordKeeper** rks)
{
    cout << "creating Harmony CSV files\n";

    // create the CSVs
    harmonyHistBestFit(rks);
    harmonyHistWorstFit(rks);
    harmonyFinalFits(rks);
    harmonyFuncCalls(rks);
    harmonyTimeTaken(rks);

    cout << "csv files have been created for Harmony Search Algorithm\n";
}

/**
 * @brief Creates a CSV file for HSA containing info on bestFit
 * 
 * @param rks The objects containing the information about the optimization process
 */
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

/**
 * @brief Creates a CSV file for HSA containing info on worstFit
 * 
 * @param rks The objects containing the information about the optimization process
 */
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

/**
 * @brief Creates a CSV file for HSA containing info on finalFit
 * 
 * @param rks The objects containing the information about the optimization process
 */
void harmonyFinalFits(RecordKeeper** rks)
{
     // set the filename (and path) for the csv
    string pathName = "results/HSA/finalFits/hsaFinalFits.csv";

    // create or open the csv
    ofstream csv(pathName);
    
    //for each function, write the gBest
    for (int i = 0; i < rks[0]->getNumFuncs(); ++i)
    {
        // write the first cost to prevent extra commas
        csv << rks[i]->getFinalFit(0, 0);

        // write the rest of the experimentations
        for (int j = 1; j < rks[0]->getPopulationSize(); ++j)
            csv << "," << rks[i]->getFinalFit(j, 0);
        
        // add a newline
        csv << '\n';
    }

    // close the csv file
    csv.close();
}

/**
 * @brief Creates a CSV file for HSA containing info on funcCalls
 * 
 * @param rks The objects containing the information about the optimization process
 */
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

/**
 * @brief Creates a CSV file for HSA containing info on timeTaken
 * 
 * @param rks The objects containing the information about the optimization process
 */
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
