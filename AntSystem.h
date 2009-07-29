/*
 * ACS-VRP-V1
 * VRP Ant System
 *
 * Giuliano Vilela, José C. Becceneri
 * Curso de Inverno 2009 - INPE
 */

#ifndef ANT_H
#define ANT_H

#include "Util.h"
#include "Graph.h"
#include "Parameters.h"
#include<cmath>
#include<vector>
#include<iostream>
using std::cout;
using std::endl;
using std::vector;
using std::ostream;

struct Ant {
  uint tourLength;
  
  vec<uint> path;
  vec<bool> visited;
  
  Ant();
  Ant(const Graph& g);
  bool operator<(const Ant& a) const;
};

ostream& operator<<(ostream& out, const Ant& ant);


void initialize_as(Graph& g, vec<Ant>& ants);

void ant_walk(Graph& g, Ant& ant);

void update_pheromone(Graph& g, const Ant& ant, const double factor = 1.0);

void evaporate_pheromone(Graph& g);

#endif
