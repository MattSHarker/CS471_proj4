
#ifndef __POPULATION_H
#define __POPULATION_H

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

    int parent1;            // the index of the solution acting as parent 1
    int parent2;            // the index of the solution acting as parent 2
    int selection;          // which selection method to use

    int    mutPrecision;    // the mutation precision
    double mutProbability;  // the mutation probability
    double mutRange;        // the mutation range
    double elitismRate;     // the elitism rate
    double crossoverRate;   // the crossover rate

    double scale;           // the main scaling factor for Diff Evo
    double lambda;          // a secondary scaling factor for Diff Evo

    double lowerBound;       // the lowest acceptable value of an element in a solution
    double upperBound;       // the highest acceptable value of an element in a solution

    double   totalCost;     // the summation of all the elements in cost
    double   totalFitness;  // the summation of the elements in fitness
    double*  cost;          // the results of passing a solution through a function
    double*  fitness;       // the normalized cost of a function
    double** population;    // the genes of the population (an array of gene pointers)

public:
    // constructors and destructors
    Population(Parameters params, const int func);
    Population(Population* otherPopulation);    // turn this one into a copy constr?
    ~Population();

    // functions for popSize
    int getPopSize();

    // functions for popDim
    int getSolutionSize();

    // functions for experimentations
    int getExperimentations();

    // functions for funcCalls
    void incrimentFuncCalls();
    void addToFuncCalls(const int otherFuncCalls);
    int  getFuncCalls();

    // functions for function
    void setFunction(const int newFunc);
    int  getFunction();

    // functions for numFunc
    int getNumFuncs();

    // functions for generations
    int getGenerations();

    // functions for bounds
    void   setLowerBound(const int newLower);
    void   setUpperBound(const int newUpper);
    double getLowerBound();
    double getUpperBound();

    // functions for parent1, parent 2
    void setParents(const int newPar1, const int newPar2);
    int  getParent1();
    int  getParent2();

    // functions for selection
    int getSelection();

    // functions for mutation variables
    double getMutRange();
    double getMutProbability();
    int    getMutPrecision();

    // functions for elitismRate
    double getElitismRate();

    // functions for crossoverRate
    double getCrossoverRate();

    // functions for scale
    double getScale();
    double getLambda();

    // functions for cost
    void    generateAllCosts();
    void    generateOneCost(const int solutionIndex);
    double  getCost(const int index);
    double* getCost();
    double  getBestCost();

    // functions for fitness
    void    generateAllFitness();
    double  getFitness(const int index);
    double* getFitness();

    // functions for population
    void    setPopulation(const int vec, double* newSolution);
    double  getPopulation(const int vec, const int element);
    double* getPopulation(const int vec);
    int getIndexOfBest();

    // functions for totalCost
    void   generateTotalCost();
    double getTotalCost();

    // functions for totalFitness
    void   generateTotalFitness();
    double getTotalFitness();

    // functions that affect multiple things
    void sortPopulation();
    void initialize();


    // functions the print
    void printVars();
    void printPopMatrix();

};

#endif