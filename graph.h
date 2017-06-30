#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include <iterator>

using namespace std;

/*
*/
typedef struct
{
	int number;
	int degree;
} Aux;

/*
*/
class Graph
{
	public:
	//number of vertexes and edges in the graph
	int vertex;
	int edges;

	// this is a vector of vectors, its purpose is to know what are each vertex's neighbours
	vector<int> *adj;
	// this array contains the number of vertexes sorted by degree (highest to lowest)
	int *order_by_degree;

	// returns the size of "adj" (number of vertexes)
	int VertexNum();
	// returns the number of edges
	int EdgesNum();
	// returns the size of a particular vector in adj, that is the degree of the vertex v
	int GetDegree(int v);
	// returns the whole neighbourhood of a vertex
	vector<int> GetNeighbours(int v);

	// sorts the vertexes by highest degree
	void OrderVertexByDegree();
	// adds an edge (used when reading the file)
	void AddEdge(int v1, int v2);
	// this function only allocates the memory for adj
	void InitAdj();
	// finds out if there is an edge between v1 and v2
	int AreNeighbours(int v1, int v2);
};
/*
	Checks if a coloring is legal
*/
int IsLegal(int *colors, Graph *g);

/*
	This returns the maximum value in an array. It's useful to find the chromatic number, given an array with a certain coloring
*/
int max(int *vet, int size);

/*
	Regular binary search, it searches for a particular neighbour in a vertex' neighbourhood
*/
int BinarySearch(vector<int> vet, int num, int start, int end);

/*
	Compares two Aux struct values. Used for a qsort call
*/
int compare(const void *a, const void *b);

/*
	Reads the user input and generates the graph in memory
*/
Graph *ReadInput(char* file_name);

/*
	Menu is called after the input is read and the user chooses an option.
	If he chooses 0, the heuristic used to find a solution will be a simple Dsatur implementation
	In case he chooses 1, Tabucol iterations will be used
	If 2 is the chosen option, the Iterated Local Search as described by Stuetzle and Chiarandini will be used.
	Any other number choice will make the program shut down
*/
void Menu(Graph *g);

/*
	Frees the memory used for the graph.
*/
void FreeGraph(Graph *g);

#endif
