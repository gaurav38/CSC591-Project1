#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

typedef unsigned int Label;
typedef std::map<Label, unsigned int> Community_Map;
typedef std::map<Label, unsigned int> Listener_Map;
typedef vector<Label> Neighbors;
typedef std::set<Label> MaxLabel;

class Node
{
    public:
        /** Default constructor */
        Node();
        /** Parameterized Constructor */
        Node(Label node_label)
        {
            label = node_label;
            mymap[label] = 1;
            community_count++;
            maxlabel.insert(1);
        }
        /** Default destructor */
        virtual ~Node();
        Label Getlabel();
        Neighbors Getneighbors();
        void AddNeighbor(Label);

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

    protected:
    private:
        Label label; //!< Member variable "label"
        Neighbors neighbors; //!< Member variable "neighbors"
        Community_Map mymap; //!< Member variable "mymap"
        Listener_Map mylistener;  //!< Member variable "mylistener"
        MaxLabel maxlabel;  //!<Member variable "maxlabel"
        unsigned int community_count; //!< Member variable "count;"
        unsigned int listen_count;
};

#endif // NODE_H
