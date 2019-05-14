
#ifndef HARMONY_H
#define HARMONY_H

#include "Population.h"

void harmony(Population** pops);
void runHarmony(Population* pop);

void initializeHS(Population* pop);

void pitchAdjust(Population* pop, double* newHarm, const int originalHarmIndex);

#endif
