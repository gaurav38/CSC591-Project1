#include "Node.h"
#include <map>
#include <vector>

Node::Node()
{
    //ctor
}

Node::Node(Label node_ID)
{
    nodeID = node_ID;
    mymap[nodeID] = 1;
    community_count++;
    maxlabel.insert(1);
}

Node::~Node()
{
    //dtor
}

/** Access label
 * \return The current value of label
 */
Label Node::Getlabel()
{
    return nodeID;
}

/** Access neighbors
 * \return The current value of neighbors
 */
Neighbors Node::Getneighbors()
{
    return neighbors;
}

/** Set neighbors
 * \param val New value to set
 */
void Node::AddNeighbor(Label x)
{
    neighbors.push_back(x);
}

/** Find community;
 * \return true if community found;
 */
bool Node::isCommunityPresent(Label x)
{
    Community_Map::const_iterator got = mymap.find(x);
    if(got == mymap.end())
        return false;
    else
        return true;
}

/** Get Community Frequency;
 * \return the frequency of a community;
 */
unsigned int Node::GetCommunityCount(Label x)
{
    if(isCommunityPresent(x))
    {
        Community_Map::const_iterator got = mymap.find(x);
        return got->second;
    }
    else
        return 0;
}

/** Add a Community;
 */
void Node::AddCommunity(Label x)
{
    if(isCommunityPresent(x))
        mymap[x]++;
    else
        mymap[x] = 1;
    community_count++;
}

void Node::AddListenedLabel(Label x)
{
    if(isLabelListened(x))
        mylistener[x]++;
    else
        mylistener[x] = 1;
    listen_count++;
}

bool Node::isLabelListened(Label x)
{
    Listener_Map::const_iterator got = mylistener.find(x);
    if(got == mylistener.end())
        return false;
    else
        return true;
}

unsigned int Node::getNodeID(){
	return nodeID;
}

void Node::listen(){
	cout<<"I am node " << nodeID << " and I am listening"<<endl;
}

Label Node::speak(){
	Label mostLabel;

	return mostLabel;
}
