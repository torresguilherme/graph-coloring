#ifndef DSATUR_H_
#define DSATUR_H_

#include "graph.h"

/*
	Executes the Dsatur function and returns the chromatic number found
*/
int DsaturChroma(Graph *g);

/*
	This is the Dsatur function. This greedy heuristic chooses a color for
	each vertex in a order of priority, according to a criterium called
	"saturation" (number of different colors in the neighbourhood). 
*/
int *Dsatur(Graph *g);

/*
	Chooses a legal coloring for a vertex. 
*/
int ChooseColor(int &n, int *colors, vector<int> neighbours);

/*
	Finds the next vertex to be colored, between the ones that are most saturated
	ATM.
*/
int FindNextSaturation(vector<int> &sat, int *colors);

/*
	Increases the neighbours' saturation by 1 point if the color is new to
	their neighbourdhood.
*/
void Saturate(Graph *g, int *colors, int current_vertex, vector<int> &sat, vector<int> neighbours);

#endif
