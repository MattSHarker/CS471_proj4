
#ifndef FIREFLY_H
#define FIREFLY_H

#include "Population.h"

void firefly(Population** populations);
void runFirefly(Population* population);

void initializeFFO(Population* pop);

// equation 1
double intensity(Population* population, const int ff, double r);
double intensity(double** tempPopulation, const int ff, double r);

// equation 2
double equationTwo(Population* population, double r);

// equation 3, returns the distance between two fireflies
double ffDistance(Population* population, const int ff1, const int ff2);    //
double ffDistance(double** tempPopulation, const int ff1, const int ff2);    //

// equation 4
void equationFour(Population* population, double* newPos, const int r, const int ff1, const int ff2);

void addNewFirefly(Population* popualtion, double* newPos);


#endif
