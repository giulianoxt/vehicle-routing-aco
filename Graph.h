/*
 * ACS-VRP-V1
 * VRP Data structures
 *
 * Giuliano Vilela, José C. Becceneri
 * Curso de Inverno 2009 - INPE
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "Util.h"
#include<iostream>
using std::ostream;
using std::endl;

struct Graph {
  uint truckCapacity;
  uint numTrucks;
  uint numNodes;
  
  vec<uint> demand;
  vec<vec<uint> > cost;
  vec<vec<double> > pheromone;
};


ostream& operator<<(ostream& out, const Graph& g);

#endif
