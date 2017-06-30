#ifndef ILS_H_
#define ILS_H_
#include "graph.h"
#include "dsatur.h"
#include "tabucol.h"

int ILSChroma(Graph *g);
int *IteratedLocalSearch();

#endif
