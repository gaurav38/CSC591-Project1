#include "Node.h"
#include "SLPA.h"
#include <iostream>
#include "error.h"

using namespace std;

int main(int argc, char* argv[])
{
    SLPA* theSLPA;

    if(argc < 5)
    {
        cout<<"Usage: \n"<<argv[0]<<" <input graph> <iterations> <output file> <threshold>\n";
        cout<<"Example:\n"<<argv[0]<<" amazon.graph 100 amazon.output 0.4\n";
        handle_error("Invalid usage!", ERR_GENERIC_ERROR);
    }

    string inFileName = argv[1];
    int numIter = atoi(argv[2]);
    string outFileName = argv[3];
    double threshold = atof(argv[4]);

    theSLPA = new SLPA(inFileName, outFileName);
    theSLPA->propagateLabels(numIter);
    theSLPA->outputCommunities(threshold);
    
    return ERR_SUCCESS;
}
