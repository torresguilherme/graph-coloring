#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "graph.h"

using namespace std;

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		cout<<"Usage: ./exec <file_name>"<<endl;
		return -1;
	}

	Graph *g = ReadInput(argv[1]);

	if(g == NULL)
	{
		cout<<"Error: input read failed. Aborting."<<endl;
		return -2;
	}

	Menu(g);
	FreeGraph(g);
	return 0;
}
