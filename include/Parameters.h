
#ifndef PARAMETERS_H
#define PARAMETERS_H

struct Parameters
{
    // general variables
    int popSize;
    int experimentations;
    int numDims;
    int numFuncs;

    float* lowRanges;
    float* highRanges;

    // PSO variables
    double dampener;
    double velConst1;
    double velConst2;

    // HS variables
    double bandwidth;
    double hmcr;
    double par;

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