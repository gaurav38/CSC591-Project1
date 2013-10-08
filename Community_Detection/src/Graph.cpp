/*
 * Graph.cpp
 *
 *  Created on: Oct 7, 2013
 *      Author: tolik
 */

#include "Graph.h"

Graph::Graph(string inFileName){
	NE=0;
	NN=0;
	inputFileName = inFileName;
	cout<<"The file name got to Graph and is "<<inputFileName<<endl;
	readGraph();

}

Graph::~Graph(){

}

void Graph::readGraph(){
	ifstream inFile(inputFileName.c_str());
	string inLine;
	int fromID, toID;

	if(inFile.is_open()){
		getline(inFile,inLine);
		istringstream iss(inLine);
		iss>>NN>>NE;
		cout<<"The number of nodes in the graph is NN = "<<NN <<" and the number of edges is NE = "<<NE<<endl<<endl;
		while(getline(inFile,inLine)){
			istringstream iss(inLine);
			if(!(iss>>fromID>>toID)){cout<<"Error reading a line from the file. Breaking out!"; break;}
			storeEdge(fromID,toID);
		}



		inFile.close();
	}else{
		cout<<"File is not open for reading"<<endl;
	}
}//end of readGraph()

void Graph::storeEdge(int from, int to){

}

