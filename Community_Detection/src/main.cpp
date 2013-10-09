#include "Node.h"
#include "SLPA.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){	//usage example: community.exe amazon.graph 10

	SLPA* theSLPA;

    if(argc < 4)
    {
        cout<<"Usage: Community_Detection.exe <input graph> <iterations> <output file\n";
        exit(0);
    }

	string inFileName = argv[1];
	int numIter = atoi(argv[2]);
	string outFileName = argv[3];
	cout<<"argv[2] ="<<argv[2]<<" numIter ="<<numIter<<endl;


	cout<<"filename got into main and is "<<inFileName<<endl;
	cout<<"final file to be generated is "<<outFileName<<endl;

	theSLPA = new SLPA(inFileName, outFileName);
	theSLPA->propagateLabels(numIter);
	theSLPA->outputCommunities(0.1);
}
