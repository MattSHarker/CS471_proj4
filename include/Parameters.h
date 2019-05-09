#ifndef __FILES_H
#define __FILES_H

struct Parameters
{
    // for matrix
    int numVecs;
    int numDims;
    int numFuncs;

    // for population
    int    experimentations;
    int    generations;
    int    mutPrecision;
    int    popSize;
    int    selection;
    int    strategies;
    double crProbability;
    double elitismRate;
    double mutProbability;
    double mutRange;

    // scaling factors
    double scale;
    double lambda;

    // for all
    float* lowRanges;
    float* highRanges;

    // auxillary functions
    void setupRanges(const int funcs);
};

Parameters getParameters();

bool comparedoubles(const double, const double);

int moveToRange(const int);

void checkVectors(const int);
void checkNumberOfFunctions(const int numFuncs);
void checkDimensions(const int dims);

void checkPopSize(const int popSolutions);
void checkGenerations(const int generations);
void checkExperimentations(const int experimentations);
void checkElitismRate(const int elitismRate);

void printParameters(const int, const int, const int, const double);


#endif