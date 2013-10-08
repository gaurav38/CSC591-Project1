/*
 * Graph.h - Graph class will maintain the information about a graph (or network in other terms)
 * by loading from a file which lists: number of nodes, number of edges, which followed by edge list as a pair
 * (start_vertex_ID end_vertex_ID).
 *
 *
 *
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cstdlib>
#include "Node.h"

using namespace std;

class Graph{

public:
	int NN; //total number of nodes in the graph
	int NE; //total number of edges in the graph
	vector<Node *> NodeArray;
	map<int,Node *> IDtoNodeMap;

	string inputFileName;


	Graph(string inputFileName);
	virtual ~Graph();

	void readGraph();
private:
	void storeEdge(int from, int to);


};



#endif /* GRAPH_H_ */
