
#ifndef HARMONY_H
#define HARMONY_H

#include "Population.h"
#include "RecordKeeper.h"

void harmony(Population** pops, RecordKeeper** records);
void runHarmony(Population* pop, RecordKeeper* record);

void initializeHS(Population* pop);

void pitchAdjust(Population* pop, double* newHarm, const int elem);
double adjustPitch(double pitch, double bandwidth);

void addNewHarmony(Population* pop, double* newHarmony, double newFitness);

#endif


