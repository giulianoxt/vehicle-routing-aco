/*
 * ACS-VRP-V1
 * VRP Utils
 *
 * Giuliano Vilela, José C. Becceneri
 * Curso de Inverno 2009 - INPE
 */

#include "Util.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>


void initRandom() {
  srand(time(0));
}

double getRandom() {
  return rand() / (double(RAND_MAX) + 1);
}
