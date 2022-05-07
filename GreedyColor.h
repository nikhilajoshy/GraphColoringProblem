#ifndef GREEDYCOLOR_H
#define GREEDYCOLOR_H
#include <iostream>
#include <vector>
#include "Graph.h"
#include <bits/stdc++.h>
#include <omp.h>



using namespace std;

class GreedyColor {
public:
	GreedyColor() {}
	void graphColoring(Graph &g_, int V);
	void graphColoring_s(Graph &g_, int V);
	void graphColoring_greedy(Graph &g_);
};
void GreedyColor::graphColoring(Graph &g_, int V)
{

	//start
	for (int i = 0; i < g_.nodes.size(); i++)
	{
		int v1 = g_.nodes[i].ID;
		if (g_.nodes[i].color == -1) {
			int c = 1;
			int col = 1;
			for (int c = 1; c < V; c++) {
				
				for (auto n : g_.nodes[v1].Nbrs) {
					if (n.second->color == c)
						col = c + 1;
				}
				if (col == c) {
					g_.nodes[i].color = col;
					bool cf = false;
					list<int>::iterator i;
					for (int i = 0; i < g_.colour.size(); i++) {
						if (g_.colour[i] == col)
							cf = true;
					}
					if (cf != true) {
						g_.colour.push_back(col);
					}
					break;
				}
			}
		}

	}
	//Print vertex with its color
	/*for (int i = 0; i < g_.sorted_nodes.size(); i++)
	{
		cout << "Vertex" << g_.sorted_nodes[i]->ID << " ---> Color " << g_.sorted_nodes[i]->color << endl;
	}*/

	cout << "Number of colors required: " << g_.colour.size() << endl;
	
	//Verification
	/*for (int i = 0; i < g_.sorted_nodes.size(); i++)
	{
		int v = g_.sorted_nodes[i]->ID;
		cout << v << " - " << g_.sorted_nodes[i]->color << ": ";
		for (auto n : g_.nodes[v].Nbrs) {
			cout << n.second->ID << "-" << n.second->color << ", ";

		}
		cout << "\n";
	}*/

};
void GreedyColor::graphColoring_s(Graph &g_, int V)
{

	//start

	for (int i = 0; i < g_.nodes.size(); i++)
	{
		int v1 = g_.sorted_nodes[i]->ID;
		if (g_.sorted_nodes[i]->color == -1) {
			int c = 1;
			int col = 1;
			for (int c = 1; c < V; c++) {

				for (auto n : g_.nodes[v1].Nbrs) {
					if (n.second->color == c)
						col = c + 1;
				}
				if (col == c) {
					g_.sorted_nodes[i]->color = col;
					bool cf = false;
					list<int>::iterator i;
					for (int i = 0; i < g_.colour.size(); i++) {
						if (g_.colour[i] == col)
							cf = true;
					}
					if (cf != true) {
						g_.colour.push_back(col);
					}
					break;
				}
			}
		}

	}
	//Print vertex with its color
	/*for (int i = 0; i < g_.sorted_nodes.size(); i++)
	{
		cout << "Vertex" << g_.sorted_nodes[i]->ID << " ---> Color " << g_.sorted_nodes[i]->color << endl;
	}*/

	cout << "Number of colors required with sorted graph: " << g_.colour.size() << endl;
	cout << "Max degree in the graph: " << g_.get_highest_degree() << endl;

	//Verification
	/*for (int i = 0; i < g_.sorted_nodes.size(); i++)
	{
		int v = g_.sorted_nodes[i]->ID;
		cout << v << " - " << g_.sorted_nodes[i]->color << ": ";
		for (auto n : g_.nodes[v].Nbrs) {
			cout << n.second->ID << "-" << n.second->color << ", ";

		}
		cout << "\n";
	}*/

};
void GreedyColor::graphColoring_greedy(Graph &g_)
{
	int c = 1;
	#pragma omp parallel for
	for (int i = 0; i < g_.nodes.size(); i++)
	{
		//cout << "i value: " << i << endl;
		int v1 = g_.nodes[i].ID;
		
		if (g_.nodes[i].color == -1) {
			bool colFound = false;
			
			while (!colFound) {
				bool f = false;
				//cout << "checking with color value " << c << endl;
				for (auto n : g_.nodes[v1].Nbrs) 
					if (n.second->color == c)
						f = true;
				
				if (f)
					c++;
				else 
					colFound = true;
				}
				
					g_.nodes[i].color = c;
					bool cf = false;
					list<int>::iterator j;
					for (int j = 0; j < g_.colour.size(); j++) {
						if (g_.colour[j] == c)
							cf = true;
					}
					if (cf != true) {
						//cout << "New col........."<<c<<endl;
						g_.colour.push_back(c);
					}
		}
		/*for (int k = 0; k < g_.nodes.size(); k++) {
			cout << g_.nodes[k].color << " ";
		}*/
		

	}
	//Print vertex with its color
	/*for (int i = 0; i < g_.sorted_nodes.size(); i++)
	{
		cout << "Vertex" << g_.sorted_nodes[i]->ID << " ---> Color " << g_.sorted_nodes[i]->color << endl;
	}*/

	cout << "Number of colors required: " << g_.colour.size() << endl;

	//Verification
	/*for (int i = 0; i < g_.sorted_nodes.size(); i++)
	{
		int v = g_.sorted_nodes[i]->ID;
		cout << v << " - " << g_.sorted_nodes[i]->color << ": ";
		for (auto n : g_.nodes[v].Nbrs) {
			cout << n.second->ID << "-" << n.second->color << ", ";

		}
		cout << "\n";
	}*/

};
#endif
