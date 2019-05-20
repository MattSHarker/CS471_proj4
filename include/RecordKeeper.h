
#ifndef RECORD_KEEPER_H
#define RECORD_KEEPER_H

#include "Parameters.h"
#include "Population.h"

class RecordKeeper
{
private:
    int experimentations;   // how many experiments there will be
    int numFuncs;           // how many functions the program uses
    int populationSize;     // how many solutions are in the population
    int solutionSize;       // the size of each solution
    int strategies;         // how many strategies are being used

    double*  historicGBest; // stores the history of gBest
    double** historicPBest; // stores the history of each patricle's pBest

    double* historicBestFit;
    double* historicWorstFit;

    double** historicFit;   // stores the history of solution costs
    double** finalFit;      // the final costs of the solutions

    // misc stats
    int*    finalFuncCalls; // how many times functions were called
    double* timeTaken;      // Time taken per


public:
    RecordKeeper(Parameters parameters);
    ~RecordKeeper();

    // functions for the single variables
    int getExperimentations();
    int getNumFuncs();
    int getPopulationSize();
    int getSolutionSize();
    int getStrategies();

    // functions for historicGBest
    void   setHistoricGBest(double newGBest, const int experiment);
    double getHistoricGBest(const int experiment);

    // functions for historicPBest
    void   setHistoricPBest(double newPBest, const int popSize, const int experiment);
    double getHistoricPBest(const int particle, const int experiment);

    // functions for historicBestFit and historicWorstFit
    void   setHistoricBestFit(double newBest, const int element);
    void   setHistoricWorstFit(double newWorst, const int element);
    double getHistoricBestFit(const int element);
    double getHistoricWorstFit(const int element);

    // functions for historicFit
    void   setHistoricFit(double historicCost, const int population, const int experiment);
    void   setHistoricFit(double* historicCost, const int population);
    double getHistoricFit(const int population, const int experiment);

    // functions for finalFit
    void   setFinalFit(double fit, const int population, const int experiment);
    double getFinalFit(const int population, const int experiment);

    // functions for funcCalls
    void   setFinalFuncCalls(int funcCalls, const int experimentation);
    int    getFinalFuncCalls(const int experimentation);

    // functions for experimentTime
    void   setTimeTaken(double time, const int experiment);
    double getTimeTaken(const int experiment);

};

#endif
