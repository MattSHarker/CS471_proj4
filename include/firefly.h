
#ifndef FIREFLY_H
#define FIREFLY_H

#include "Population.h"
#include "RecordKeeper.h"

void firefly(Population** populations, RecordKeeper** records);
void runFirefly(Population* population, RecordKeeper* record);

void initializeFFO(Population* pop);

// equations 1-4 (in order)
double intensity(Population* population, const int ff, double r);
double newBeta(Population* population, double r);
double ffDistance(Population* population, const int ff1, const int ff2);
void newPosition(Population* population, double* newPos, const int r, const int ff1, const int ff2);
void addNewFirefly(Population* popualtion, double* newPos);

void recordInfo(Population* pop, RecordKeeper* record, clock_t timer, const int iteration);

#endif
