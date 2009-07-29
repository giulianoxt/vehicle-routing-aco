/*
 * ACS-VRP-V1
 * VRP Ant System
 *
 * Giuliano Vilela, José C. Becceneri
 * Curso de Inverno 2009 - INPE
 */

#include "AntSystem.h"
#include <cassert>

double decisionFactor(uint i, uint j, Graph& g);


Ant::Ant() { }

Ant::Ant(const Graph& g) {
  tourLength = 0;
  
  path.reserve(g.numNodes + 2);
  visited = vec<bool>(g.numNodes, false);
}

bool Ant::operator<(const Ant& a) const {
  return tourLength < a.tourLength;
}

ostream& operator<<(ostream& out, const Ant& a) {
  out << "Ant {" << endl
      << " tourLength = " << a.tourLength << endl
      << " path       = " << a.path       << endl
      << " visited    = " << a.visited    << endl
      << "}";
  
  return out;
}


void initialize_as(Graph& g, vec<Ant>& ants) {
  initRandom();
  
  uint n = g.numNodes;
  
  for_(i, 0, numAnts)
    ants[i] = Ant(g);

  for_(i, 0, n) for_(j, 0, n)
    g.pheromone[i][j] = initialPheromone;
}

void ant_walk(Graph& g, Ant& ant) {  
  uint node = 0, n = g.numNodes, numVisited = 0;
  uint truckID = 0, truckCapacity = 0;
  
  uint facPos, next[n+1];
  double factors[n+1];
  
  for (;;) {
    ant.visited[node] = true;
    ant.path.push_back(node);
    
    if (node == 0) {
      if (++truckID > g.numTrucks) {
        if (numVisited + 1 != n) {
          ant.tourLength = INF;
        }
        break;
      }
      else {
        truckCapacity = g.truckCapacity;
      }
    }
    else {
      ++numVisited;
    }
    
    truckCapacity -= g.demand[node];
    
    facPos = 0;
    double allFactorsSum = 0.;

    for_(i, 0, n) {
      if (i == node) continue;
      
      double f = decisionFactor(node, i, g);
      
      allFactorsSum += f;
      
      if (i && ant.visited[i]) continue;
      if (g.demand[i] > truckCapacity) continue;
      
      next[facPos] = i;
      factors[facPos++] = f;
    }
    
    assert(facPos || node == 0);

    // Decisão pela regra pseudo-random
    
    uint nextNode = node;
    
    if (getRandom() < explotationFactor) {
      // Exploit
      
      double maxFactor = 0.0;
      uint maxFactorPos = INF;
      
      for_(i, 0, facPos) if (factors[i] >= maxFactor) {
        maxFactor = factors[i];
        maxFactorPos = i;
      }
      
      nextNode = next[maxFactorPos];
    }
    else {
      // Roleta
      
      double random = getRandom(), wheelSum = 0.0;
      
      double nextFactorsSum = 0.0;
      for_(i, 0, facPos) {
        factors[i] /= allFactorsSum;
        nextFactorsSum += factors[i];
      }
      
      for_(i, 0, facPos) {
        wheelSum += factors[i] / nextFactorsSum;
        
        if (random <= wheelSum || i == facPos - 1) {
          nextNode = next[i];
          break;
        }
      }
    }
    
    ant.tourLength += g.cost[node][nextNode];
    
    node = nextNode;
  }
}

void update_pheromone(Graph& g, const Ant& ant, const double factor) {
  if (ant.tourLength == INF) return;
  
  const double delta = factor / ant.tourLength;
  
  for_(i, 0, ant.path.size()-1) {
    uint a = ant.path[i];
    uint b = ant.path[i+1];
    
    g.pheromone[a][b] += delta;
  }
}

void evaporate_pheromone(Graph& g) {
  for_(i, 0, g.numNodes) for_(j, 0, g.numNodes)
    g.pheromone[i][j] *= (1 - evaporationRate);
}

double decisionFactor(uint i, uint j, Graph& g) {
  double pheromone = g.pheromone[i][j];
  double heuristic = 1 / double(g.cost[i][j]);
  
  return pow(pheromone, pheromoneWeight) + 
         pow(heuristic, heuristicWeight);
}
