
#ifndef CSV_H
#define CSV_H

#include "Population.h"
#include "RecordKeeper.h"

// CSVs for Particle Swarm
void particleCSVs(RecordKeeper** records);
void particlePBestFit(RecordKeeper* rk, const int function);
void particleGBestFit(RecordKeeper** records);
void particleFuncCalls(RecordKeeper** records);

// CSVs for Firefly Algorithm
void fireflyCSVs(RecordKeeper** records);
void fireflyHistBestFit(RecordKeeper** records);
void fireflyHistWorstFit(RecordKeeper** records);
void fireflyFuncCalls(RecordKeeper** records);

// CSVs for Harmony Search
void harmonyCSVs(RecordKeeper** records);
void harmonyHistBestFit(RecordKeeper** records);
void harmonyHistWorstFit(RecordKeeper** records);
void harmonyFuncCalls(RecordKeeper** records);
void harmonyTimeTaken(RecordKeeper** records);

#endif
