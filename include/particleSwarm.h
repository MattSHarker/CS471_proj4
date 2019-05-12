
#ifndef PARTICLE_SWARM_H
#define PATRICLE_SWARM_H

#include <ctime>

#include "Population.h"
#include "RecordKeeper.h"

void particleSwarm(Population** populations, RecordKeeper** records);
void runParticleSwarm(Population* pop, RecordKeeper* record);

void initializePSO(Population* pop);
void updateRecords(Population* population, RecordKeeper* records, const std::clock_t, const int experiment);

void updateVelocity(Population* population);
void updateParticles(Population* population);
void updateFitness(Population* population);
void updatePersonalBest(Population* population);
void updateGlobalBest(Population* population);


#endif
