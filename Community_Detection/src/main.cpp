#include "Node.h"
#include "SLPA.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){	//usage example: community.exe amazon.graph 10

	SLPA* theSLPA;

	string inFileName=argv[1];
	int numIter = atoi(argv[2]);
	cout<<"argv[2] ="<<argv[2]<<" numIter ="<<numIter<<endl;


	cout<<"filename got into main and is "<<inFileName<<endl;

	theSLPA = new SLPA(inFileName);
	theSLPA->propagateLabels(numIter);
	theSLPA->outputCommunities(0.1);
}
