#ifndef PLGREEDYCOLOR_H
#define PLGREEDYCOLOR_H
#include <iostream>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <stdio.h>
#include <math.h>
#include "Graph.h"

using namespace std;
using namespace std::chrono;

class PlGreedyColor {

public:
	PlGreedyColor() {}
	void merge(Graph &g_, int left, int right, int mid);
	void merge_sort(Graph &g_, int left, int right);
	void firstmerge(Graph &g_);
	void setM_thread(int m);
	int getM_thread();
	int start_merge_sort(Graph &g_, int max_threads);

private:
	int m_thread;

};

void PlGreedyColor::setM_thread(int m) {
	this->m_thread = m;
};
int PlGreedyColor::getM_thread() {
	return this->m_thread;
};
void PlGreedyColor::merge(Graph &g_, int left, int right, int mid)
{
	
	int mm=-1;
	for (int n = left; n <= right; n++) {
		if (mm < g_.nodes[n].color)
			mm = g_.nodes[n].color;
	}
	/*for (int n = left; n <= right; n++) {
		cout << "id:" << g_.nodes[n].ID<<" color: "<<g_.nodes[n].color << endl;
	}*/
	int max;
	//cout << left << " " << right << endl;
	for (int i = left; i <= mid; i++) {
		//cout << i << " " <<endl;
		for (int j = mid + 1; j <= right; j++) {
			for (auto n : g_.nodes[i].Nbrs) {
				if (n.second->color == g_.nodes[i].color && n.second->ID == j) {
					//max = *max_element(g_.colour.begin(), g_.colour.end());
					g_.colour.push_back(mm + 1);
					n.second->color = mm + 1;
					mm += 1;
						//cout << "colour vector: " << mm+1 << endl;
				}
			}
		}
	}
	/*cout << "after while" << endl;
	for (int n = left; n <= right; n++) {
		cout << "id:" << g_.nodes[n].ID << " color: " << g_.nodes[n].color << endl;
	}*/
	
};

void PlGreedyColor::merge_sort(Graph &g_, int left, int right)
{
	int mid, i = 0;

	if (right-left>=100) {
		//cout << left << " " << right << endl;
		//recursively divide the array till there are single elements in the array
		mid = (left + right) / 2;
		merge_sort(g_, left, mid);
		merge_sort(g_, mid + 1, right);
		merge(g_, left, right, mid);
		
	}

};
void PlGreedyColor::firstmerge(Graph &g_) {
	for (int i = 0; i < g_.nodes.size(); i++) {
		g_.nodes[i].color = 1;
	}
	g_.colour.push_back(1);
	int max_t = getM_thread();
#pragma omp parallel for num_threads(max_t)

	for (int i = 0; i < g_.nodes.size(); i = i + (g_.nodes.size() / max_t) + 1) {
		int high;
		//cout << "Thread no: " << omp_get_thread_num() << "\n";
		// calculating low and high
		int low = i;
		if ((i + (g_.nodes.size() / max_t)) < g_.nodes.size()) {
			high = i + (g_.nodes.size() / max_t);
		}
		else {
			high = g_.nodes.size() - 1;
		}
		//cout << low << " " << high << endl;
		// evaluating mid point
		int mid = low + (high - low) / 2;
		if (low < high) {
			merge_sort(g_, low, mid);
			merge_sort(g_, mid + 1, high);
			merge(g_, low, high, mid);
		}
	}

};



int PlGreedyColor::start_merge_sort(Graph &g_, int max_threads) {

	int num = g_.get_number_of_nodes();
	int counter, step;
	setM_thread(max_threads);
	step = counter = max_threads;
	firstmerge(g_);
	int t = 2;
	int length = (num / max_threads) + 1;
	while (counter > 1) {
		step = (step + 1) / 2;
		#pragma omp parallel for
		for (int n = 0; n < step; n++) {
			int l = length * t*n;
			int r = min(l + length * t - 1, (int)g_.get_number_of_nodes() - 1);
			merge(g_, l, r, l + length * (t / 2) - 1);
		}
		t = t * 2;
		counter = (counter + 1) / 2;
	}
	int mx = *max_element(g_.colour.begin(), g_.colour.end());
	cout << "Maximum colors required: " << mx<<endl;
	/*for (int n = 0; n < g_.get_number_of_nodes(); n++) {
		cout << "id:" << g_.nodes[n].ID << " color: " << g_.nodes[n].color << endl;
	}*/
	return mx;
};

#endif
