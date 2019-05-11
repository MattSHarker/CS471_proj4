
#ifndef POPULATION_H
#define POPULATION_H

#include "Parameters.h"

class Population {

private:
    int popSize;            // the number of solution vectors in the population (and size of fitness)
    int solutionSize;       // the size of the solution vectors
    int experimentations;   // how many experimentations there will be
    int funcCalls;          // how many times a fitness function has been called
    int function;           // which function the population is running
    int numFuncs;           // how total functions there are
    int generations;        // how many generations the population will go through
                                // primarily used for storing the history of solutions

    double lowerBound;      // the lowest acceptable value of an element in a solution
    double upperBound;      // the highest acceptable value of an element in a solution

    double velConst1;       // two constants to modify velocity for PSO
    double velConst2;

    double alpha;           // three constants for FFO
    double beta;            
    double gamma;           

    double*  fitness;       // the normalized cost of a function
    double** population;    // the genes of the population (an array of gene pointers)

    double   globBestFit;   // The global best fitness of the population
    double*  globBestVec;   // The global best vector
    double*  pBestFit;      // The array of each personal best fitness
    double** pBestVec;      // the personal best fitness solution of each solution
    double** velocity;      // The matrix of velocities

    double* intensity;      // the intensity of each vector (FFO)

public:

    // constructors and destructors
    Population(Parameters params, const int func);
    ~Population();

    // functions for single variables
    int    getExperimentations();
    int    getGenerations();
    int    getNumFuncs();
    int    getPopSize();
    int    getSolutionSize();
    double getLowerBound();
    double getUpperBound();
    double getVelConst1();
    double getVelConst2();
    double getAlpha();
    double getBeta();
    double getGamma();

    // functions for funcCalls
    int  getFuncCalls();
    void addToFuncCalls(const int otherFuncCalls);
    void incrimentFuncCalls();

    // functions for function
    int  getFunction();
    void setFunction(const int newFunc);

    // functions for pBestVec and pBestFit
    void   setPBestVec(const int vec, const int elem, double newVal);
    void   setPBestFit(const int vec, double newFit);
    double getPBestVec(const int vec, const int elem);
    double getPBestFit(const int vec);

    // functions for globBestVec and globBestFit
    void   setGlobalBestVec(const int elem, double newBest);
    void   setGlobalBestFit(double newBest);
    double getGlobalBestVec(const int elem);
    double getGlobalBestFit();

    // functions for fitness
    int     getIndexOfBest();
    void    generateAllFitness();
    void    generateOneFitness(const int solutionIndex);
    double  getFitness(const int index);
    double* getFitness();

    // functions for population
    void    setPopulation(const int vec, double* newSolution);
    void    setPopulation(const int vec, const int elem, double newValue);
    double  getPopulation(const int vec, const int element);
    double* getPopulation(const int vec);

    // functions for velocity
    void   setVelocity(const int vec, const int elem, double newValue);
    double getVelocity(const int vec, const int elem);

};

#endif