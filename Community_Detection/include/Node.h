#ifndef NODE_H
#define NODE_H

//#include "Graph.h"
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstdlib>

using namespace std;

typedef unsigned int Label;
typedef unsigned int NodeID;
typedef std::map<Label, unsigned int> Community_Map;
typedef std::map<Label, unsigned int> Listener_Map;
typedef vector<NodeID> Neighbors;
typedef std::set<Label> MaxLabel;

class Node
{
public:
        /** Default constructor */
        Node();
        /** Parameterized Constructor */
        Node(NodeID);
        /** Default destructor */
        virtual ~Node();
        NodeID GetNodeID();
        Neighbors GetNeighbors();
        void AddNeighbor(NodeID);
        /** Default destructor */
        //virtual ~Node();
        Label Getlabel();
        Neighbors Getneighbors();
        Community_Map getMyMap();
        /** Speaker;
         * \return a random lable with probability proportional to its occurence
         */
        Label speak();
        /** Access count;
         * \return The current value of count;
         */
        unsigned int Getcount() { return community_count; }
        unsigned int GetListenedCount() { return listen_count; }
        bool isCommunityPresent(Label);
        void AddCommunity(Label);
        unsigned int GetCommunityCount(Label);
        void AddListenedLabel(Label);
        bool isLabelListened(Label);
        double doubleRand();
        /** Listener;
         *  Adds a label to mymap depending on the labels
         *  listened from the neighbors
         */
        void listen();
        /** getPopularLabel
         * \return the most popular label in the listener map
         */
        Label getPopularLabel();

    protected:
    private:
        NodeID nodeID; //!<member variable "nodeID"

        unsigned int getNodeID();
        //void listen();

    protected:
    private:
        //unsigned int nodeID;
        //Label label; //!< Member variable "label"
        Neighbors neighbors; //!< Member variable "neighbors"
        Community_Map mymap; //!< Member variable "mymap"
        Listener_Map mylistener;  //!< Member variable "mylistener"
        MaxLabel maxlabel;  //!<Member variable "maxlabel"
        unsigned int community_count; //!< Member variable "count;"
        unsigned int listen_count;
};

#endif // NODE_H
