/*
 * ACS-VRP-V1
 * VRP Parameters
 *
 * Giuliano Vilela, José C. Becceneri
 * Curso de Inverno 2009 - INPE
 */

#include "Parameters.h"
#include <cstdlib>
#include <sstream>
using std::stringstream;


uint INF                 = -1;

uint numAnts             = 64;    // por iteração
uint maxIterations       = 500;
uint minSuccessAnts      = 10000;

bool useRank             = true;
uint rankListMaxSize     = 5;
uint rankListMaxDelta    = 50;

uint heuristicWeight     = 3;     // beta
uint pheromoneWeight     = 1;     // alpha

double evaporationRate   = 0.9;
double initialPheromone  = 1e-7;

double explotationFactor = 0.2;   // q0


template<typename T>
T cast(char const* str) {
  T x;
  stringstream ss(str);
  ss >> x;
  return x;
}

void handleArgs(int argc, char** argv) {
  static char const* long_opts_names[8] = {
    "numAnts", "minSuccessAnts",
    "ranking", "rankListMaxSize",
    "rankListMaxDelta", "heuristicWeight",
    "evaporationRate", "explotationFactor"
  };

  static option long_opts[8];
  
  for_(i, 0, 8) {
    long_opts[i].name = long_opts_names[i];
    long_opts[i].has_arg = required_argument;
    long_opts[i].val = i;
  }

  int c, p;
  
  optind = 2;
  
  while ((c = getopt_long(argc, argv, "", long_opts, &p)) != -1)   
    switch (c) {
      case 0:
        numAnts = cast<uint>(optarg); break;
      case 1:
        minSuccessAnts = cast<uint>(optarg); break;
      case 2:
        useRank = cast<uint>(optarg); break;
      case 3:
        rankListMaxSize = cast<uint>(optarg); break;
      case 4:
        rankListMaxDelta = cast<uint>(optarg); break;
      case 5:
        heuristicWeight = cast<uint>(optarg); break;
      case 6:
        evaporationRate = cast<double>(optarg); break;
      case 7:
        explotationFactor = cast<double>(optarg); break;
      default:
        abort();
    }
}
