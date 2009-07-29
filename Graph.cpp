/*
 * ACS-VRP-V1
 * VRP Data structures
 *
 * Giuliano Vilela, José C. Becceneri
 * Curso de Inverno 2009 - INPE
 */

#include "Graph.h"

ostream& operator<<(ostream& out, const Graph& g) {
  out << "Graph {" << endl
      << " capacity  = " << g.truckCapacity << endl
      << " n_trucks  = " << g.numTrucks     << endl
      << " n_nodes   = " << g.numNodes      << endl
      << " cost      = " << g.cost          << endl
      << " pheromone = " << g.pheromone     << endl
      << " demands   = " << g.demand        << endl
      << "}";
  
  return out;
}
