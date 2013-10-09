#ifndef NODE_H
#define NODE_H

#include "Graph.h"
#include <iostream>
#include <vector>
#include <map>
#include <set>

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
        Node(NodeID id)
        {
            nodeID = id;
            mymap[nodeID] = 1;
            community_count = 1;
            listen_count = 0;
            //maxlabel.insert(1);
        }
        /** Default destructor */
        virtual ~Node();
        NodeID GetNodeID();
        Neighbors GetNeighbors();
        void AddNeighbor(NodeID);

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

        /** Listener;
         *  Adds a label to mymap depending on the labels
         *  listened from the neighbors
         */
        void listen();

        /** getPopularLabel
         * \return the most popular label in the listener map
         */
        Label getPopularLabel();

        /** Speaker;
         * \return a random lable with probability proportional to its occurence
         */
        Label speak();

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
