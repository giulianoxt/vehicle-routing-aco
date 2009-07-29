/*
 * ACS-VRP-V1
 * Ant Colony System for the Vehicle Routing Problem
 *
 * Giuliano Vilela, José C. Becceneri
 * Curso de Inverno 2009 - INPE
 */

#include "Util.h"
#include "Graph.h"
#include "Reader.h"
#include "AntSystem.h"
#include "Parameters.h"
#include <iostream>
#include <algorithm>
using namespace std;


int main(int argc, char** argv) {
  if (argc < 2) {
    cout << "ACS-VRP-V1: Wrong usage." << endl;
    return 1;
  }
  
  handleArgs(argc, argv);
  
  Graph g;
  vec<Ant> ants(numAnts);
  
  // Leitura da instância  
  read_tsplib_instance(argv[1], g);
  
  uint it = 0;
  uint antCount = 0, goodAnts = 0;
  Ant globalBestAnt;
  
  
  // Loop de iterações
  while (goodAnts < minSuccessAnts && ++it <= maxIterations) {
    // Inicializa as formigas
    initialize_as(g, ants);
    
    for_(i, 0, numAnts) {
      // Tour de uma formiga
      Ant& ant = ants[i];
      ant_walk(g, ant);
      
      ++antCount;
      if (ant.tourLength != INF) ++goodAnts;
    }
       
    Ant* bestAnt;
    
    if (useRank) {
      // Ranking de tours
      sort(ants.begin(), ants.end());
      
      for_(i, 0, rankListMaxSize) {
        uint diff = ants[i].tourLength - ants[0].tourLength;
        
        if (diff > rankListMaxDelta) break;
        
        double factor = 1 / double(1 + i);
        update_pheromone(g, ants[i], factor);
      }
      
      bestAnt = &ants[0];
    }
    else {
      bestAnt = &ants[0];
      
      for_(i, 1, ants.size())
        if (ants[i].tourLength < bestAnt->tourLength)
          bestAnt = &ants[i];
      
      update_pheromone(g, *bestAnt);
    }
    
    // Atualiza melhor caminho global
    if (bestAnt->tourLength < globalBestAnt.tourLength ||
        globalBestAnt.tourLength == INF) {
      globalBestAnt = *bestAnt;
//       cout << bestAnt->tourLength << " [it " << it << "]" << endl;
    }
    
    // Evaporação de feromônio
    evaporate_pheromone(g);
  }
  
  if (globalBestAnt.tourLength != INF)
    cout << globalBestAnt.tourLength << endl;
  else
    cout << -1 << endl;

//   cout << "\nResult: ";
//   if (globalBestAnt.tourLength != INF)
//     cout << globalBestAnt.tourLength << endl;
//   else
//     cout << "Route not found." << endl;
  
//   cout << "Valid Ants: " << goodAnts << '/' << antCount << endl;
//   cout << "Iterations: " << it << endl;
  
  return 0;
}
