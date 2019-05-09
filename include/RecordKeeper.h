
#ifndef __RECORD_KEEPER_H
#define __RECORD_KEEPER_H

#include "Parameters.h"
#include "Population.h"

class RecordKeeper
{
private:
    int experimentations;   // how many experiments there will be
    int generations;        // how many generations there are
    int numFuncs;           // how many functions the program uses
    int populationSize;     // how many solutions are in the population
    int solutionSize;       // the size of each solution
    int strategies;         // how many strategies are being used

    double** historicCost; // stores the history of solution costs
    double** finalCosts;    // the final costs of the solutions

    double*** historicCostStrats; // stores the history of best solutions (per strategy per generation per experiment)
    double*** finalCostStrats;      // stores all of the final costs for each strategy/exp/pop

    // misc stats
    int*    finalFuncCalls; // how many times functions were called
    double* expTime;        // 1 per experiment


public:
    RecordKeeper(Parameters parameters);
    ~RecordKeeper();

    // functions for the single variables
    int getExperimentations();
    int getGenerations();
    int getNumFuncs();
    int getPopulationSize();
    int getSolutionSize();
    int getStrategies();

    // functions that deal with historicBest
    void   setHistoricCostStrats(double newCost, const int strategy, const int experiment, const int generation);
    double getHistoricCostStrats(const int strategy, const int experiment, const int generation);

    // functions for finalCostStrats
    void   setFinalCostStrats(double newCost, const int strategy, const int experiment, const int generation);
    double getFinalCostStrats(const int strategy, const int experiment, const int generation);

    // functions that deal with historicCost
    void   setHistoricCost(double historicCost, const int experiment, const int generation);
    double getHistoricCost(const int experiment, const int generation);

    void   setFinalCost(Population* population, const int experiment);
    double getFinalCost(const int experiment, const int population);

    void   setFinalFuncCalls(int funcCalls, const int experiment);
    int    getFinalFuncCalls(const int experiment);

    void   setExpTime(double time, const int experiment);
    double getExpTime(const int experiment);

};



#endif
