/*
 * Graph.cpp
 *
 *  Created on: Oct 7, 2013
 *      Author: tolik, kpadia
 */

#include "Graph.h"
#include "Node.h"
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>

NodeMap Graph::IDtoNodeMap;

Graph::Graph(string inFileName)
{
    NE=0;
    NN=0;
    inputFileName = inFileName;
    cout<<"Trying to open and read graph file: "<<inputFileName<<endl;
    readGraph();
}

Graph::~Graph(){

}

void Graph::readGraph()
{
    NodeID fromID, toID;
    char *contents;
    int fd;
    struct stat s;
    size_t length;
    
    //open
    fd = open(inputFileName.c_str(), O_RDONLY);
    if (fd == -1)
        handle_error("open",ERR_OPENING_FILE);

    
    //obtain file size
    if (fstat(fd, &s) == -1)
        handle_error("fstat",ERR_READING_FILE);
    length = s.st_size;
    
    //map the contents
    contents = (char*) mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0);
    if (contents == MAP_FAILED)
        handle_error("mmap",ERR_MEMORY_ALLOC);
    
    istringstream iss(contents);
    iss>>NN>>NE;
    cout<<"The number of nodes in the graph is NN = "<<NN <<" and the number of edges is NE = "<<NE<<endl<<endl;
    while(iss>>fromID>>toID)
    {
        storeEdge(fromID,toID);
    }
    
    //close input file
    munmap(contents,length);
    close(fd);
}//end of readGraph()


void Graph::storeEdge(NodeID fromID, NodeID toID){
    Node *nd;
    if(IDtoNodeMap.count(fromID)>0){ //node from already in the map
        nd=IDtoNodeMap[fromID];
        nd->AddNeighbor(toID);
    } else {
        nd = new Node(fromID);
        nd->AddNeighbor(toID);
        IDtoNodeMap[fromID] = nd;
    }
    //for undirected graph if edges are listed only once we have to insert both nodes
    unsigned int swapt;
    swapt = fromID;
    fromID=toID;
    toID=swapt;
    if(IDtoNodeMap.count(fromID)>0){ //node from already in the map
        nd=IDtoNodeMap[fromID];
        nd->AddNeighbor(toID);
    } else {
        nd = new Node(fromID);
        nd->AddNeighbor(toID);
        IDtoNodeMap[fromID] = nd;
    }
}

Node* Graph::getNode(NodeID x)
{
    return Graph::IDtoNodeMap[x];
}

