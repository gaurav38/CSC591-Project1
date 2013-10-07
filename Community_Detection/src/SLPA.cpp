/*
 * SLPA.cpp is the business part of Speaker-listener Label Propagation Algorithm (SLPA).
 *
 *  Created on: Oct 7, 2013
 *      Author: tolik
 *
 */

#include "SLPA.h"

SLPA::SLPA(string inFileName){
	inputFileName = inFileName;
	theGraph = new Graph(inputFileName);
}

SLPA::~SLPA(){

}

/*
 * The SLPA algorithm
 * -----------------------------------------
 * N_ITER - number of iterations
 * THRESH - postprocessing threshold
 * 1) At t=0, the memory of each node is initialized with its node id
 * 2) For t=1:T
 * 		All nodes are marked unvisited
 * 		While (there is any unvisited node)
 * 		a. One unvisited node is randomly selected as a listener.
 * 		b. Each neighbor (speaker) of the selected node randomly selects label
 * 			with probability proportional to the occurance frequency in the memory
 * 			and sens the selected label to the listener
 * 		c. The listener adds the most popular label received to its memory.
 * 		d. Mark the listener visited
 * 3) The post-processing based on the labels in the memories and the threshold THRESH
 * 		is applied to output the communities
 */
void SLPA::propagateLabels(int numIter){


	for (int i=0;i<numIter;i++){

		// for all nodes
		//	mark them unvisited
		//node X <- pickRandomeNode()
		//X listenToNeighbors()
		//etc.
		cout<<"Propagating labels iteration number = " <<i<<endl;
	}


}

void SLPA::outputCommunities(){
	//write communities to a file
}


