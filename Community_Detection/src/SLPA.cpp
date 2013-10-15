/*
 * SLPA.cpp is the business part of Speaker-listener Label Propagation Algorithm (SLPA).
 *
 *  Created on: Oct 7, 2013
 *      Author: tolik, kpadia
 *
 */

#include "SLPA.h"
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>

SLPA::SLPA(string inFileName, string outFileName){
    inputFileName = inFileName;
    outputFileName = outFileName;
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
 *         All nodes are marked unvisited
 *         While (there is any unvisited node)
 *         a. One unvisited node is randomly selected as a listener.
 *         b. Each neighbor (speaker) of the selected node randomly selects label
 *             with probability proportional to the occurance frequency in the memory
 *             and sends the selected label to the listener
 *         c. The listener adds the most popular label received to its memory.
 *         d. Mark the listener visited
 * 3) The post-processing based on the labels in the memories and the threshold THRESH
 *         is applied to output the communities
 */
//uses a Fisher-Yates shuffle
void shuffle(unsigned int*& a, unsigned int max)
{
    unsigned int r, temp;
    for (unsigned int i = max-1;i>0;i--)
    {
        r = rand()%i;
        temp = a[r];
        a[r] = a[i];
        a[i] = temp;
    }
}

void SLPA::propagateLabels(int numIter)
{
    unsigned int numNodes = theGraph->NN;
    unsigned int* randomNodeIDs = new unsigned int[numNodes];
    if (!randomNodeIDs)
    {
        handle_error("new",ERR_MEMORY_ALLOC);
    }
    
    for (unsigned int i = 0;i<numNodes;i++)
        randomNodeIDs[i] = i;

    for (int i=0;i<numIter;i++)
    {
        //this reshuffling of node IDs in effect does marking all nodes unvisited
        shuffle(randomNodeIDs, numNodes);
        for (unsigned int j=0;j<numNodes;j++)
        {
            Node *listener;
            listener = theGraph->IDtoNodeMap[randomNodeIDs[j]];
            listener->listen();
        }
    }
    
    delete[] randomNodeIDs;
}

void SLPA::writeCommunities()
{
    ostringstream os;
    cout<<"\n\nPrinting final communities to the output file\n";
    Community::iterator it;
    for(it = final_communities.begin(); it != final_communities.end(); ++it)
    {
        std::vector<NodeID> nodes = it->second;
        std::vector<NodeID>::iterator vit;
        string node_list;
        for(vit = nodes.begin(); vit != nodes.end(); ++vit)
        {
            int node = *vit;
            stringstream ss1;
            ss1 << node;
            string temp_node = ss1.str();
            node_list.append(temp_node);
            node_list.append(" ");
        }
        final_set.insert(node_list);
    }
    Set::iterator sit;
    for(sit = final_set.begin(); sit!= final_set.end(); ++sit)
        os<<*sit<<'\n';
    
    int outFile = open (outputFileName.c_str(), O_RDWR | O_CREAT,S_IRUSR|S_IWUSR);
    ftruncate(outFile, os.str().length());
    if (outFile == -1)
        handle_error("open",ERR_OPENING_FILE);
    char* mem = (char*) mmap (NULL, os.str().length(), PROT_WRITE, MAP_SHARED, outFile, 0);
    if (mem == MAP_FAILED)
        handle_error("mmap");
    sprintf(mem,"%s",os.str().c_str());
    munmap(mem,os.str().length());
    close(outFile);
    
    cout<<"Output file is ready\n";
}

void SLPA::outputCommunities(double thresh)
{
    for (unsigned int i = 0; i < theGraph->NN; i++){
        Node* nd = Graph::getNode(i);
        NodeID id = nd->GetNodeID();
        Community_Map coMap = nd->getMyMap();
        unsigned int total_count = nd->getTotalCommunityCount();
        Community_Map::iterator mapIt;
        for (mapIt=coMap.begin(); mapIt!=coMap.end(); ++mapIt){
            if((double)mapIt->second/total_count >= thresh) {
                final_communities[mapIt->first].push_back(id);
            }
        }
    }
    writeCommunities();
}



