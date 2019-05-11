
#ifndef PARAMETERS_H
#define PARAMETERS_H

struct Parameters
{
    // general variables
    int numVecs;
    int numDims;
    int numFuncs;
    int experimentations;
    int popSize;

    float* lowRanges;
    float* highRanges;

    // PSO variables
    double velConst1;
    double velConst2;

    // FFO variables
    double alpha;
    double beta;
    double gamma;

    // auxillary functions
    void setupRanges(const int funcs);
};

Parameters getParameters();

bool comparedoubles(const double, const double);

void printParameters(const int, const int, const int, const double);


#endif