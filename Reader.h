/*
 * ACS-VRP-V1
 * VRP Instance Reader
 *
 * Giuliano Vilela, José C. Becceneri
 * Curso de Inverno 2009 - INPE
 */

#ifndef READER_H
#define READER_H

#include "Graph.h"

void read_tsplib_instance(char* filename, Graph& g);

#endif
