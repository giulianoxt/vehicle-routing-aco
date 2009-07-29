/*
 * ACS-VRP-V1
 * VRP Instance Reader
 *
 * Giuliano Vilela, José C. Becceneri
 * Curso de Inverno 2009 - INPE
 */

#include "Util.h"
#include "Graph.h"
#include "Reader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <iostream>
using namespace std;


void read_tsplib_instance(char* filename, Graph& g) {
  string line;
  ifstream file(filename);
  
  while (file) {
    getline(file, line);
    
    if (line.empty()) continue;
    
    string kw, x;
    istringstream ss(line);
    
    ss >> kw;
    
    if (kw == "DIMENSION") {
      uint n;
      ss >> x >> n;
      
      g.numNodes = n;
      g.cost = vec<vec<uint> >(n, vec<uint>(n));
      g.pheromone = vec<vec<double> >(n, vec<double>(n, 0.));
      g.demand = vec<uint>(n);
    }
    else if (kw == "CAPACITY") {
      uint c;
      ss >> x >> c;
      g.truckCapacity = c;
    }
    else if (kw == "TRUCKS") {
      uint t;
      ss >> x >> t;
      g.numTrucks = t;
    }
    else if (kw == "NODE_COORD_SECTION") {
      uint n = g.numNodes;
      
      vec<int> x(n), y(n);
      
      for (;;) {
        getline(file, line);
        
        if (line[0] == 'D')
          break;
        
        istringstream ss(line);
        
        int a, b, c;
        ss >> a >> b >> c;
        
        x[a-1] = b;
        y[a-1] = c;
      }
      
      for_(i, 0, n) for_ (j, i + 1, n) {
        double dist2 = sqr(x[i]-x[j]) + sqr(y[i]-y[j]);
        g.cost[i][j] = g.cost[j][i] = floor(sqrt(dist2) + .5);
      }
      
      // DEMAND_SECTION
      
      for (;;) {
        getline(file, line);
        
        if (line[0] == 'D')
          break;
        
        istringstream ss(line);
        uint v, d;
        ss >> v >> d;
        g.demand[v-1] = d;
      }
      
      return;
    }
  }
}
