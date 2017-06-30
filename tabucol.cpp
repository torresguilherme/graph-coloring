#include "tabucol.h"
#include <unistd.h>

int TabucolChroma(Graph *g)
{
	int max_iterations = g->VertexNum()*20000;
	int taboo_duration = g->VertexNum();
	int *colors = Tabucol(g, g->VertexNum(), max_iterations, taboo_duration);
	int ret = max(colors, g->VertexNum());

	delete[] colors;
	return ret;
}

int *Tabucol(Graph *g, int num_vertex, int max_iterations, int taboo_duration)
{
	srand(time(NULL));
	int *colors = Dsatur(g);
	int *colors_trial = new int[num_vertex];
	int current_c_number = max(colors, num_vertex);
	int **gamma = new int*[num_vertex];
	int **taboo_list = new int*[num_vertex];

	for(int i=0; i < num_vertex; i++)
	{
		gamma[i] = new int[current_c_number];
		taboo_list[i] = new int[current_c_number];
		for(int j=0; j < current_c_number; j++)
		{
			gamma[i][j] = 0;
			taboo_list[i][j] = 0;
		}
	}

	int end = 0;

	while(!end)
	{
		current_c_number--;
		int isLegal = 0;
		int iterations = 0;
		int i;
//		cout<<"cores: ";
		for(i=0; i < num_vertex; i++)
		{
			colors_trial[i] = colors[i];
			if(colors_trial[i] == current_c_number+1)
			{
				colors_trial[i] = (rand() % current_c_number)+1;
			}
//			cout<<colors_trial[i]<<' ';
//			cout<<endl;
		}

		for(i=0; i < num_vertex; i++)
		{
			CalculateGammasForAVertex(g, colors_trial, gamma, i);
			for(int j=1; j <= current_c_number; j++)
			{
//				cout<<gamma[i][j]<<' ';
			}
//			cout<<endl;
		}
//		cout<<endl;

		while(!end && !isLegal)
		{
/*			for(i=0; i < num_vertex; i++)
			{
				for(int j=1; j <= current_c_number; j++)
				{
					cout<<gamma[i][j]<<' ';
				}
				cout<<endl;
			}
*/
			if(IsLegal(colors_trial, g))
			{
				isLegal = 1;
				for(i=0; i < num_vertex; i++)
				{
					colors[i] = colors_trial[i];
					for(int j=0; j < current_c_number; j++)
					{
						taboo_list[i][j] = 0;
					}
				}
			}

			else if(iterations > max_iterations)
			{
				end = 1;
			}

			else
			{
				pair<int, int> nextMove = LookForBestMove(gamma, colors, taboo_list, num_vertex, current_c_number);
//				if(DeltaFunction(gamma, nextMove.first, colors[nextMove.first], nextMove.second) >= 0)
//				{
//					isLegal = 1;
//				}

//				else
//				{
					AddToTabooList(taboo_list, nextMove, taboo_duration);
					cout<<"delta: "<<DeltaFunction(gamma, nextMove.first, colors[nextMove.first], nextMove.second)<<endl;
//					sleep(1);
					UpdateTabooList(taboo_list, num_vertex, current_c_number);
					UpdateGammas(g, gamma, colors_trial, nextMove);

					colors_trial[nextMove.first] = nextMove.second;

					iterations++;
//				}
			}
		}

		cout<<iterations<<" iteracoes para achar alguma solucao com "<<current_c_number<<" cores"<<endl;
	}

	delete[] taboo_list;
	delete[] gamma;
	delete[] colors_trial;
	return colors;
}

int DeltaFunction(int **gamma, int vertex, int current_color, int next_color)
{
	return gamma[vertex][next_color] - gamma[vertex][current_color];
}

void CalculateGammasForAVertex(Graph *g, int *colors, int **gamma, int v)
{
	vector<int> nb = g->GetNeighbours(v);

	for(vector<int>::iterator it = nb.begin(); it != nb.end(); it++)
	{
		gamma[v][colors[*it]]++;
	}
}

pair<int, int> LookForBestMove(int **gamma, int *colors, int **taboo_list, int num_vertex, int num_colors)
{
	pair<int, int> ret = make_pair(0, 0);
	int minDelta = 0;
	for(int i=0; i < num_vertex; i++)
	{
		if(gamma[i][colors[i]] > 0)
		{
			for(int j=1; j <= num_colors; j++)
			{
				if(!IsTaboo(taboo_list, make_pair(i, j)) && 
				DeltaFunction(gamma, i, colors[i], j) < minDelta)
				{
					minDelta = DeltaFunction(gamma, i, colors[i], j);
					ret = make_pair(i, j);
				}
			}
		}
	}

	return ret;
}

void UpdateGammas(Graph *g, int **gamma, int *colors, pair<int, int> nextMove)
{
	vector<int> nb = g->GetNeighbours(nextMove.first);
	vector<int>::iterator it;
	int current_color = colors[nextMove.first];
	int next_color = nextMove.second;

	for(it = nb.begin(); it != nb.end(); it++)
	{
		gamma[*it][next_color]++;
		gamma[*it][current_color]--;
	}
}

void AddToTabooList(int **list, pair<int, int> move, int duration)
{
	list[move.first][move.second] = duration;
}

int IsTaboo(int **list, pair<int, int> move)
{
	if(list[move.first][move.second])
	{
		return 1;
	}

	return 0;
}

void UpdateTabooList(int **list, int num_vertex, int color_number)
{
	for(int i=0; i < num_vertex; i++)
	{
		for(int j=0; j < color_number; j++)
		{
			if(list[i][j])
			{
				list[i][j]--;
			}
		}
	}
}
