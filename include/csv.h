
#ifndef __CSV_GENERATOR_H
#define __CSV_GENERATOR_H

#include "RecordKeeper.h"
#include "Population.h"

// CSVs for genetic algorithm
void geneticCSVs(Population** pops, RecordKeeper** recordKeeper);

void geneticFinalBestFitness(RecordKeeper** recordKeeper, Population** pop);
void geneticFuncCalls(RecordKeeper** recordKeepers);
void geneticHistoricCosts(RecordKeeper* recordKeeper, const int func);
void geneticTime(RecordKeeper** recordKeepers);

// CSVs for differential evolution
void differentialCSVs(Population** pops, RecordKeeper** recordKeepers);

void differentialFinalBestFitness(RecordKeeper** recordKeeper, Population** pop, const int strat);
void differentialFuncCalls(RecordKeeper** recordKeepers);
void differentialHistoricCosts(RecordKeeper* recordKeeper, const int strat, const int func);
void differentialTime(RecordKeeper** recordKeepers);

#endif
