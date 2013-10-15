#ifndef NODE_H
#define NODE_H

/*
 *      Author: Anatoli Melechko, Gaurav Saraf, Kalpesh Padia
 *      Based on algorithm by Jierui Xie and Boleslaw K. Szymanski published in
 *      "Towards Linear Time Overlapping Community Detection in Social Networks"
 */
#include <iostream>
#include <vector>
#include <tr1/unordered_map>
#include <set>
#include <cstdlib>
#include "error.h"

using namespace std;

typedef unsigned int Label;
typedef unsigned int NodeID;
typedef std::tr1::unordered_map<Label, unsigned int> Community_Map;
typedef std::tr1::unordered_map<Label, unsigned int> Listener_Map;
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
        unsigned int getTotalCommunityCount();
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
        Neighbors neighbors; //!< Member variable "neighbors"
        Community_Map mymap; //!< Member variable "mymap"
        Listener_Map mylistener;  //!< Member variable "mylistener"
        MaxLabel maxlabel;  //!<Member variable "maxlabel"
        unsigned int community_count; //!< Member variable "count;"
        unsigned int listen_count;
};

#endif // NODE_H
