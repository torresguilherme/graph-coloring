#include "graph.h"
#include "dsatur.h"
#include "tabucol.h"

using namespace std;

int Graph::VertexNum()
{
	return vertex;
}

int Graph::EdgesNum()
{
	return edges;
}

int Graph::GetDegree(int v)
{
	return adj[v].size();
}

vector<int> Graph::GetNeighbours(int v)
{
	return adj[v];
}

void Graph::OrderVertexByDegree()
{
	order_by_degree = new int[vertex];
	Aux *array = new Aux[vertex];

	for(int i = 0; i < vertex; i++)
	{
		array[i].number = i;
		array[i].degree = GetDegree(i);
	}

	qsort(array, vertex, sizeof(Aux), compare);

	for(int i=0; i < vertex; i++)
	{
		order_by_degree[i] = array[i].number;
	}

	delete[](array);
}

void Graph::InitAdj()
{
	adj = new vector<int> [vertex];
}

void Graph::AddEdge(int v1, int v2)
{
	adj[v1].push_back(v2);
	adj[v2].push_back(v1);
}

int Graph::AreNeighbours(int v1, int v2)
{
	if(BinarySearch(adj[v1], v2, 0, adj[v1].size()))
	{
		return 1;
	}

	return 0;
}

int IsLegal(int *colors, Graph *g)
{
	int v = g->VertexNum();
	for(int i=0; i < v; i++)
	{
		vector<int> nb = g->GetNeighbours(i);
		for(vector<int>::iterator j = nb.begin(); j != nb.end(); j++)
		{
			if(colors[i] == colors[*j])
			{
				return 0;
			}
		}
	}

	return 1;
}

// acha o numero maximo em 1 vetor
int max(int *vet, int size)
{
	int max = 0;
	for(int i = 0; i < size; i++)
	{
		if(vet[i] > max)
		{
			max = vet[i];
		}
	}

	return max;
}

// procura um vizinho no vector da vizinhança
int BinarySearch(vector<int> vet, int num, int start, int end)
{
	int half = (start+end) / 2;

	if(half == start && half == end)
	{
		return 0;
	}

	else
	{
		if(vet[half] == num)
		{
			return 1;
		}

		else if(vet[half] > num)
		{
			return BinarySearch(vet, num, start, half);
		}

		else
		{
			return BinarySearch(vet, num, half, end);
		}
	}
}

// comparaçao para ordenar ao contrario no qsort
int compare(const void *a, const void *b)
{
	const Aux *na = (const Aux *)a;
	const Aux *nb = (const Aux *)b;
	return  (nb->degree) - (na->degree);
}

Graph *ReadInput(char* file_name)
{
	Graph *novo = new Graph;
	FILE *file;
	if(!(file = fopen(file_name, "r")))
	{
		cout<<"Error: could not open input file with name: "<<file_name<<endl;
		return NULL;
	}

	char type;
	char *comment = NULL;
	size_t len = 1024;
	int v1, v2;

	while(fscanf(file, "%c", &type) != EOF)
	{
		if(type == 'c')
		{
			if(!getline(&comment, &len, file))
			{
				cout<<"Error: bad input file!"<<endl;
				fclose(file);
				return NULL;
			}
		}

		else if(type == 'p')
		{
			if(!(fscanf(file, "%s", comment)) || !(fscanf(file, "%i %i", &novo->vertex, &novo->edges)))
			{
				cout<<"Error: bad input file!"<<endl;
				fclose(file);
				return NULL;
			}

			novo->InitAdj();
		}

		else if(type == 'e')
		{
			if(!fscanf(file, "%i %i", &v1, &v2))
			{
				cout<<"Error: bad input file!"<<endl;
				fclose(file);
				return NULL;
			}

			novo->AddEdge(v1-1, v2-1);
		}
	}

	free(comment);
	fclose(file);
	novo->OrderVertexByDegree();

	return novo;
}

void Menu(Graph *g)
{
	int choice;
	cin>>choice;

	while(0 <= choice && choice <= 2)
	{
		int ans;
		if(choice == 0)
		{
			ans = DsaturChroma(g);
			cout<<ans<<endl;
		}

		else if(choice == 1)
		{
			ans = TabucolChroma(g);
			cout<<ans<<endl;
		}

		else if(choice == 2)
		{
		}

		cin>>choice;
	}
}
	

void FreeGraph(Graph *g)
{
	delete[](g->adj);
	delete[](g->order_by_degree);
	delete(g);
}
