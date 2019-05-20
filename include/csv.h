
#ifndef CSV_H
#define CSV_H

#include "Population.h"
#include "RecordKeeper.h"

// CSVs for Particle Swarm
void particleCSVs(RecordKeeper** records);
void particleGBestFit(RecordKeeper** records);
void particleWorstFit(RecordKeeper** records);
void particleFinalFits(RecordKeeper** records);
void particleFuncCalls(RecordKeeper** records);
void particleTimeTaken(RecordKeeper** records);

// CSVs for Firefly Algorithm
void fireflyCSVs(RecordKeeper** records);
void fireflyHistBestFit(RecordKeeper** records);
void fireflyHistWorstFit(RecordKeeper** records);
void fireflyFinalFits(RecordKeeper** records);
void fireflyFuncCalls(RecordKeeper** records);
void fireflyTimeTaken(RecordKeeper** records);

// CSVs for Harmony Search
void harmonyCSVs(RecordKeeper** records);
void harmonyHistBestFit(RecordKeeper** records);
void harmonyHistWorstFit(RecordKeeper** records);
void harmonyFinalFits(RecordKeeper** records);
void harmonyFuncCalls(RecordKeeper** records);
void harmonyTimeTaken(RecordKeeper** records);

#endif
