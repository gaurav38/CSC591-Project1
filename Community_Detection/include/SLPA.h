/*
 * SLPA.h
 *
 *  Created on: Oct 7, 2013
 *      Author: tolik
 */

#ifndef SLPA_H_
#define SLPA_H_

#include "Graph.h"
#include <tr1/unordered_map>
#include <tr1/random>
#include <algorithm>

class SLPA{

public:
	Graph* theGraph;
	string inputFileName;



	SLPA(string fileName);
	virtual ~SLPA();
	void propagateLabels(int numIterations);
	void outputCommunities();
private:

	unsigned int selectRandomNode();

};


#endif /* SLPA_H_ */
