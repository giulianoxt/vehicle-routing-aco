/*
 * ACS-VRP-V1
 * VRP Utils
 *
 * Giuliano Vilela, José C. Becceneri
 * Curso de Inverno 2009 - INPE
 */

#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <iostream>
#include <getopt.h>
using std::vector;
using std::ostream;

#define vec vector
#define for_(i, a, b) for (uint i=(a);i<(b);++i)
#define dump(x) cout << #x << " = " << x << endl

typedef unsigned int uint;


template<typename T>
ostream& operator<<(ostream& out, const vec<T>& v) {
  out << '[';
  
  for_(i, 0, v.size()) {
    if (i) out << ", ";
    out << v[i];
  }
  
  out << ']';
  return out;
}

template<typename N>
N sqr(N n) {
  return n * n;
}

void initRandom();

double getRandom();

#endif
