/*
 * SLPA.cpp is the business part of Speaker-listener Label Propagation Algorithm (SLPA).
 *
 *  Created on: Oct 7, 2013
 *      Author: tolik
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
 * 		All nodes are marked unvisited
 * 		While (there is any unvisited node)
 * 		a. One unvisited node is randomly selected as a listener.
 * 		b. Each neighbor (speaker) of the selected node randomly selects label
 * 			with probability proportional to the occurance frequency in the memory
 * 			and sends the selected label to the listener
 * 		c. The listener adds the most popular label received to its memory.
 * 		d. Mark the listener visited
 * 3) The post-processing based on the labels in the memories and the threshold THRESH
 * 		is applied to output the communities
 */
int myrandom (int i){return std::rand()%i;}

void SLPA::propagateLabels(int numIter){

	//unsigned int randID;
	vector<unsigned> randomNodeIDs;
	//http://www.cplusplus.com/reference/algorithm/random_shuffle/
	unsigned int numNodes = theGraph->NN;
	cout<<"number of nodes numNodes = "<<numNodes<<endl;
	for (unsigned int j=0;j<numNodes;j++){
	//for (unsigned int j=0;j<theGraph->NN;j++){
		randomNodeIDs.push_back(j);
	}

	for (int i=0;i<numIter;i++){
        cout<<"------------------------------------------Iteration "<<i<<" ------------------------------------------\n";
		//this reshuffling of node IDs in effect does marking all nodes unvisited
		random_shuffle(randomNodeIDs.begin(),randomNodeIDs.end(),myrandom);
		for (std::vector<unsigned>::iterator it=randomNodeIDs.begin(); it!=randomNodeIDs.end(); ++it){
			Node *listener;
			listener = theGraph->IDtoNodeMap[*it];
			cout<<"----------- Current Listeners label is "<<listener->GetNodeID()<<"-----------"<<endl;
			listener->listen();
		}
		//cout<<"Propagating labels iteration number = " <<i<<endl;
	}
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
        unsigned int temp = it->first;
        stringstream ss;
        ss << temp;
        string com = ss.str();
        std::vector<NodeID> nodes = it->second;
        std::vector<NodeID>::iterator vit;
        string node_list = string("\t\t\t\t");
        for(vit = nodes.begin(); vit != nodes.end(); ++vit)
        {
            int node = *vit;
            stringstream ss1;
            ss1 << node;
            string temp_node = ss1.str();
            node_list.append(temp_node);
            node_list.append(", ");
        }
        string final_string = com.append(node_list);
        //cout<<final_string<<endl;
        //char *line = final_string.c_str();
        outFile<<final_string.c_str()<<'\n';
    }
    outFile.close();
    cout<<"Output file is ready\n";
    //cout<<"-----------------------------------------------------\n";
}

void SLPA::outputCommunities(double thresh)
{
    for (unsigned int i = 0; i < theGraph->NN; i++){
        Node* nd = Graph::getNode(i);
        NodeID id = nd->GetNodeID();
        cout<<"Node ID for extracting community labels is " <<id<<endl;
        Community_Map coMap = nd->getMyMap();
        unsigned int total_count = nd->getTotalCommunityCount();
        Community_Map::iterator mapIt;
        cout<<"Printing the communities of every node before post-processing\n";
        for (mapIt=coMap.begin(); mapIt!=coMap.end(); ++mapIt){
            cout<<mapIt->first<<":"<<mapIt->second<<endl;
            if((double)mapIt->second/total_count >= thresh) {
                cout<<id<<" is part of "<<mapIt->first<<" community\n";
                final_communities[mapIt->first].push_back(id);
            }
        }
        cout<<endl;
    }
    writeCommunities();
}



