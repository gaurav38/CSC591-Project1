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

}

Graph::~Graph(){

}

void Graph::readGraph(string inFileName){
	fstream fsin;
	fsin.open(inFileName.c_str(),fstream::in);
	if(fsin.is_open()){
		//read it
		fsin.close();
	}else{
		cout<<"File is not open for reading"<<endl;
	}
}

