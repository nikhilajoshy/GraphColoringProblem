#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>


using namespace std;

class Node {
public:
	Node() {}
	int ID;
	int color;
	unordered_map<int, Node*> Nbrs = {};
};


struct CompNodeDegree
{
	bool operator()(const Node* v1, const Node* v2) const
	{
		return v1->Nbrs.size() > v2->Nbrs.size();
	}
};

class Graph {

public:
	Graph() {}
	~Graph() = default;

	void read(const string & file);
	void print_nodes();
	void init();

	int get_number_of_nodes() const { return nodes.size(); }
	int get_number_of_edges() const {
		int num = 0;
		for (int i = 0; i < nodes.size(); i++) {
			num += nodes[i].Nbrs.size();
		}
		return num / 2;
	}

	int get_highest_degree() const {
		int h = 0;
		for (int i = 0; i < nodes.size(); i++) {
			int n_size = nodes[i].Nbrs.size();
			h = max(n_size, h);
		}
		return h;
	}

	int get_average_degree() const {
		return get_number_of_edges() * 2.0 / get_number_of_nodes();
	}

	


	vector<Node> nodes; // using hash map, search only need o(1) in best case
	vector<Node*> sorted_nodes; // sort node degree, make heap complexity O(3n)
	vector<int> colour;
};


void Graph::read(const string & file) {

	ifstream in(file.c_str());
	cout << "Load graph from " << file << endl;
	if (in.good()) {
		string buffer, p, td;
		int number_of_nodes, number_of_edges;
		stringstream firstRow;
		getline(in, buffer);
		firstRow << buffer;
		firstRow >> p >> td >> number_of_nodes >> number_of_edges;

		cout << "... with " << number_of_nodes << " nodes and " << number_of_edges << " edges." << endl;

		// edges = vector<Edge>(number_of_edges);
		nodes = vector<Node>(number_of_nodes);
		for (int i = 0; i < number_of_nodes; i++) {
			Node v1 = Node();
			v1.ID = i;
			v1.color = -1;
			nodes[i] = std::move(v1);
			sorted_nodes.push_back(&nodes[i]);
		}

		for (int i = 0; i < number_of_edges; i++) {
			getline(in, buffer);
			stringstream ss;
			ss << buffer;
			int v1_, v2_;
			ss >> v1_ >> v2_;
			// check self loop
			if (v1_ == v2_) {
				// cerr << "file contains self loop" << endl;
				continue;
			}
			// decrease node id in order to match the index
			v1_--;
			v2_--;
			// check duplicate edges
			unordered_map<int, Node*>::const_iterator it = nodes[v1_].Nbrs.find(v2_);

			if (it != nodes[v1_].Nbrs.end()) {
				// cerr << "file contains multiple edges" << endl;
				continue;
			}

			nodes[v1_].Nbrs[v2_] = &nodes[v2_];
			nodes[v2_].Nbrs[v1_] = &nodes[v1_];
		}
		sort(sorted_nodes.begin(), sorted_nodes.end(), CompNodeDegree()); // sort according to the degree
		cout << "Done." << endl;
		cout << "Graph actual contains " << get_number_of_edges() << " edges." << endl << endl;
	}
	else {
		cout << file << " file status proof failed... " << endl;
		return;
	}
}

void Graph::print_nodes() {
	for (int i = 0; i < sorted_nodes.size(); i++) {
		cout << "ID: " << sorted_nodes[i]->ID;
		cout << " d: " << sorted_nodes[i]->Nbrs.size();
		cout << endl;
	}
}

void Graph::init() {
	// clean the colors
	for (int i = 0; i < nodes.size(); i++) {
		nodes[i].color = -1;
	}
	colour.clear();
	cout << "Reseted Graph." << endl;
}


#endif

