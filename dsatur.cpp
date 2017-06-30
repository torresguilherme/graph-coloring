#include "dsatur.h"

using namespace std;

int DsaturChroma(Graph *g)
{
	int *colors = Dsatur(g);
	int ret = max(colors, g->VertexNum());
	delete[] colors;
	return ret;
}

int *Dsatur(Graph *g)
{
	int i, vertex = g->VertexNum();
	vector<int> saturation;
	int *colors = new int[vertex];

	for(i=0; i < vertex; i++)
	{
		saturation.push_back(0);
		colors[i] = 0;
	}

	int it = g->order_by_degree[0];
	int end = 0;
	int num_colors = 0;
	vector<int> current_neighbours;

	while(!end)
	{
		current_neighbours = g->GetNeighbours(it);
		colors[it] = ChooseColor(num_colors, colors, current_neighbours);

		Saturate(g, colors, it, saturation, current_neighbours);
		it = FindNextSaturation(saturation, colors);

		if(it == -1)
		{
			end = 1;
		}
	}

	return colors;
}

int ChooseColor(int &n, int *colors, vector<int> neighbours)
{
	if(n == 0)
	{
		n++;
	}

	else
	{
		vector<int>::iterator it;
		for(int i=1; i < n; i++)
		{
			int illegal = 0;
			for(it = neighbours.begin(); it != neighbours.end(); it++)
			{
				if(colors[(*it)] == i)
				{
					illegal = 1;
				}
			}

			if(!illegal)
			{
				return i;
			}
		}

		n++;
	}

	return n;
}

int FindNextSaturation(vector<int> &sat, int *colors)	
{
	int ret = -1;
	int size = sat.size();
	for(int i=0; i < size; i++)
	{
		if(!colors[i])
		{
			if(ret == -1 || sat[i] > sat[ret])
			{
				ret = i;
			}
		}
	}

	return ret;
}

void Saturate(Graph *g, int *colors, int current_vertex, vector<int> &sat, vector<int> neighbours)
{
	int flag = 0;
	for(vector<int>::iterator it = neighbours.begin(); it != neighbours.end(); it++)
	{
		vector<int> other_n = g->GetNeighbours(*it);
		for(vector<int>::iterator i2 = other_n.begin(); i2 != other_n.end(); i2++)
		{
			if(colors[*i2] == colors[current_vertex] && *i2 != current_vertex)
			{
				flag = 1;
			}
		}

		if(!flag)
		{
			sat[*it]++;
		}
	}
}
