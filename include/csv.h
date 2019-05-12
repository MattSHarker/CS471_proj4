
#ifndef CSV_H
#define CSV_H

#include "Population.h"
#include "RecordKeeper.h"

// CSVs for genetic algorithm
void particleCSVs(Population** pops, RecordKeeper** recordKeeper);

// void 
void particlePBestFit(RecordKeeper* rk, const int function);
void particleGBestFit(RecordKeeper** records);


#endif
