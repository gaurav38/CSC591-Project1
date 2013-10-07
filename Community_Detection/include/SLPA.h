/*
 * SLPA.h
 *
 *  Created on: Oct 7, 2013
 *      Author: tolik
 */

#ifndef SLPA_H_
#define SLPA_H_

#include "Graph.h"

class SLPA{

public:
	Graph* theGraph;
	string inputFileName;
	int N_ITER;

	SLPA(string fileName, int numIterations);
	virtual ~SLPA();
	void propagateLabels();
	void outputCommunities();

};


#endif /* SLPA_H_ */
