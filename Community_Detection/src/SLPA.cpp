/*
 * SLPA.cpp is the business part of Speaker-listener Label Propagation Algorithm (SLPA).
 *
 *  Created on: Oct 7, 2013
 *      Author: tolik, kpadia
 *
 */

#include "SLPA.h"

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

    //unsigned int randID;
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
            //cout<<"----------- Current Listeners label is "<<listener->GetNodeID()<<"-----------"<<endl;
            listener->listen();
        }
        //cout<<"Propagating labels iteration number = " <<i<<endl;
    }
    
    delete[] randomNodeIDs;
}

void SLPA::writeCommunities()
{
    ofstream outFile;
    outFile.open(outputFileName.c_str(), ios::out);
    cout<<"\n\nPrinting final communities to the output file\n";
    /*
    cout<<"These values will be printed\n\n";
    cout<<"-----------------------------------------------------\n";
    cout<<"Community\t\t\tMember Nodes\n";
    cout<<"-----------------------------------------------------\n";
    outFile<<"-----------------------------------------------------\n";
    outFile<<"Community\t\t\tMember Nodes\n";
    outFile<<"-----------------------------------------------------\n";
    */
    Community::iterator it;
    for(it = final_communities.begin(); it != final_communities.end(); ++it)
    {
        //unsigned int temp = it->first;
        //stringstream ss;
        //ss << temp;
        //string com = ss.str();
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
        //string final_string = com.append(node_list);
        //cout<<final_string<<endl;
        //char *line = final_string.c_str();
        //outFile<<node_list.c_str()<<'\n';
        final_set.insert(node_list);
    }
    Set::iterator sit;
    for(sit = final_set.begin(); sit!= final_set.end(); ++sit)
        outFile<<*sit<<'\n';
    outFile.close();
    cout<<"Output file is ready\n";
    //cout<<"-----------------------------------------------------\n";
}

void SLPA::outputCommunities(double thresh)
{
    for (unsigned int i = 0; i < theGraph->NN; i++){
        Node* nd = Graph::getNode(i);
        NodeID id = nd->GetNodeID();
        //cout<<"Node ID for extracting community labels is " <<id<<endl;
        Community_Map coMap = nd->getMyMap();
        unsigned int total_count = nd->getTotalCommunityCount();
        Community_Map::iterator mapIt;
        //cout<<"Printing the communities of every node before post-processing\n";
        for (mapIt=coMap.begin(); mapIt!=coMap.end(); ++mapIt){
            //cout<<mapIt->first<<":"<<mapIt->second<<endl;
            if((double)mapIt->second/total_count >= thresh) {
                //cout<<id<<" is part of "<<mapIt->first<<" community\n";
                final_communities[mapIt->first].push_back(id);
            }
        }
        //cout<<endl;
    }
    writeCommunities();
}



