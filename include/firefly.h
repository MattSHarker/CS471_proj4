
#ifndef FIREFLY_H
#define FIREFLY_H

#include "Population.h"

void firefly(Population** populations);
void runFirefly(Population* population);

void initializeFFO(Population* pop);
void moveFirefly(Population* population, const int ff1, const int ff2);

double equationOne(Population* population, const int r);
double equationTwo(Population* population, const int r);
double equationThree(Population* population, const int ff1, const int ff2);
double equationFour(Population* population,  const int r, const int ff1, const int ff2, const int t, const int d);



#endif
