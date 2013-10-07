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

	SLPA(string fileName);
	virtual ~SLPA();

};


#endif /* SLPA_H_ */