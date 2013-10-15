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
#include <tr1/unordered_map>
#include <cstdlib>
#include "Node.h"
#include "error.h"

using namespace std;
typedef std::tr1::unordered_map<NodeID,Node *> NodeMap;

class Graph
{
public:
	unsigned int NN; //total number of nodes in the graph
	unsigned int NE; //total number of edges in the graph
	static NodeMap IDtoNodeMap;
    static Node* getNode(NodeID);
	string inputFileName;
	Graph(string inputFileName);
	virtual ~Graph();
	void readGraph();

private:
	void storeEdge(NodeID from, NodeID to);


};



#endif /* GRAPH_H_ */
