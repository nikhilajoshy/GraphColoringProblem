#include <iostream>
#include <vector>
#include "Graph.h"
#include "GreedyColor.h"
#include "PlGreedyColor.h"
#include "ExactColor.h"
#include <bits/stdc++.h>
#include <string>
#include<filesystem>
#include <limits>


using namespace std;
using namespace std::chrono;
//using namespace boost::filesystem;
namespace fs = std::filesystem;


const string output = "C:/Users/Acer/OneDrive/Desktop/WS21/AlgoEngg/Exam/results6.txt";
int main()
{
	
	string file = "C:/Users/Acer/OneDrive/Desktop/WS21/AlgoEngg/Ass03/pace2019_track1_vc_exact_all/vc-exact_200.gr";
	string file_no = file.substr(file.length() - 6,3);
	ifstream in(file);
	cerr << "Load graph from " << file << endl;
	if (in.good()) {
		string buffer, p, td;
		int number_of_nodes, number_of_edges;
		stringstream firstRow, ss;
		getline(in, buffer);
		firstRow << buffer;
		firstRow >> p >> td >> number_of_nodes >> number_of_edges;
		cerr << "... with " << number_of_nodes << " nodes and " << number_of_edges << " edges." << endl;


	//string path="c:/Users/Acer/OneDrive/Desktop/WS21/AlgoEngg/Ass03/pace2019_track1_vc_exact_all";
	//ofstream of(output);
	//if (!of) {
	//	cout << "Cannot open file!" << endl;
	//}
	//for (const auto & entry : fs::directory_iterator(path)) {
	//	//files.push_back(dir_itr->path().filename());
	//	//cout<< dir_itr->path().filename() << "\n";
	//	string file = entry.path().string();
	//	string file_no = file.substr(file.length() - 6, 3);

		Graph g;
		g.read(file);

		GreedyColor gc;
		//approx 
		///*auto t0 = high_resolution_clock::now();
		//gc.graphColoring(g, g.get_highest_degree());
		//auto t1 = high_resolution_clock::now();
		//int time = duration_cast<milliseconds>(t1 - t0).count();

		//of << file_no << " " << g.get_highest_degree() << " " << g.colour.size() << " " << time / 1000.0<<" ";
		//g.init();*/

		//approx with sorted nodes
		//auto t0 = high_resolution_clock::now();
		//gc.graphColoring_s(g, g.get_highest_degree());
		//auto t1 = high_resolution_clock::now();
		//int time = duration_cast<milliseconds>(t1 - t0).count();
		//cout << "Time: " << time / 1000.0 << "\n";
		//write to file
		
		//of << g.colour.size()<<" "<<time/ 1000.0 << " ";


		//divide&conquer
		//PlGreedyColor pgc;
		//auto t0 = high_resolution_clock::now();
		//int m=pgc.start_merge_sort(g, 4);
		//auto t1 = high_resolution_clock::now();
		//int time = duration_cast<milliseconds>(t1 - t0).count();
		//cout << "Time: " << time / 1000.0 << "\n";
		//of << file_no << " " << m <<"  "<<time/1000.0<<"\n";

		//Greedy
		auto t0 = high_resolution_clock::now();
		gc.graphColoring_greedy(g);
		auto t1 = high_resolution_clock::now();
		int time = duration_cast<milliseconds>(t1 - t0).count();
		cout << "Time: " << time / 1000.0 << "\n";
		//of << file_no << " " << g.colour.size() << "  " << time / 1000.0 << "\n";
		/*ExactColor ec;
		int k = 48;
		auto t0 = high_resolution_clock::now();
		int res=ec.do_exactColoring(g, g.get_number_of_nodes(), k);
		auto t1 = high_resolution_clock::now();
		int time = duration_cast<milliseconds>(t1 - t0).count();
		if (res == 0)
			cout << "Graph " << file_no << " does not have a solution with " << k << " colors"<<endl;
		else
			cout << "Graph " << file_no << " has a solution with " << k << " colors" << endl;
		cout<<"Time: "<< time / 1000.0 << "\n";*/
		////write to file
		//	//
		//of << res<<" "<<time/ 1000.0 << "\n";

		cout << endl;
		//return 0;
	}
	//of.close();
}