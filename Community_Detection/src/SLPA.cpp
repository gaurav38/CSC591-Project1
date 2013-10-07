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




