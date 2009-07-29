/*
 * ACS-VRP-V1
 * VRP Parameters
 *
 * Giuliano Vilela, José C. Becceneri
 * Curso de Inverno 2009 - INPE
 */

#ifndef PARAMS_H
#define PARAMS_H

#include "Util.h"
#include <getopt.h>

extern uint INF;

extern uint numAnts;
extern uint maxIterations;
extern uint minSuccessAnts;

extern bool useRank;
extern uint rankListMaxSize;
extern uint rankListMaxDelta;

extern uint heuristicWeight;
extern uint pheromoneWeight;

extern double evaporationRate;
extern double initialPheromone;

extern double explotationFactor;


void handleArgs(int argc, char** argv);

#endif
