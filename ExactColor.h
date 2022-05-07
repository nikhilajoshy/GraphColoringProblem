#ifndef EXACTCOLOR_H
#define EXACTCOLOR_H
#include <iostream>
#include "Graph.h"
#include <omp.h>
using namespace std;

class ExactColor {
public:
	ExactColor() {}
	int do_exactColoring(Graph &g_, int n, int k);
};


int ExactColor::do_exactColoring(Graph &g_, int n, int k)
{
	for (int i = 0; i < g_.nodes.size(); i++) {
		g_.nodes[i].color = 1;
	}
	vector<int> visited(n, 0);
	int maxC = 1;
	#pragma omp parallel for
	for (int v = 0; v < n; v++)
	{

		if (visited[v])
			continue;
		visited[v] = 1;
		queue<int> q;
		q.push(v);
		while (!q.empty())
		{

			int v1 = q.front();
			q.pop();
			//cout <<"checking vertex "<< v1<<endl;
			//#pragma omp parallel for
			for (auto n : g_.nodes[v1].Nbrs) {
				if (n.second->color == g_.nodes[v1].color)
					n.second->color += 1;
				
				maxC = max(maxC, max(g_.nodes[v1].color,n.second->color));
				if (maxC > k)
					return 0;
				if (!visited[n.second->ID]) {
					visited[n.second->ID] = 1;
					q.push(n.second->ID);
				}
			}
		}
	}

	return 1;
};

#endif