/*
 *      Author: Anatoli Melechko, Gaurav Saraf, Kalpesh Padia
 *      Based on algorithm by Jierui Xie and Boleslaw K. Szymanski published in
 *      "Towards Linear Time Overlapping Community Detection in Social Networks"
 */
#include "Node.h"
#include "Graph.h"
#include <tr1/unordered_map>
#include <vector>

//Node::Node()
//{
    //ctor
//}

Node::Node(NodeID id)
{
    nodeID = id;
    mymap[nodeID] = 1;
    community_count = 1;
    listen_count = 0;
}

Node::~Node()
{
    //dtor
}

/** Access label
 * \return The current value of label
 */
Label Node::GetNodeID()
{
    return nodeID;
}

/** Access neighbors
 * \return The current value of neighbors
 */
Neighbors Node::GetNeighbors()
{
    return neighbors;
}

/** Set neighbors
 * \param val New value to set
 */
void Node::AddNeighbor(NodeID x)
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

Label Node::getPopularLabel()
{
    Label max_label = mylistener.begin()->first;
    float max_popular_probability = (float)mylistener.begin()->second/listen_count;
    for(Listener_Map::iterator it = mylistener.begin(); it != mylistener.end(); ++it)
    {
        Label current_label = it->first;
        unsigned int current_label_count = it->second;
        float current_probability = (float)current_label_count/listen_count;
        if(current_probability > max_popular_probability)
        {
            max_label = current_label;
            max_popular_probability = current_probability;
        }
    }
    return max_label;
}

void Node::listen()
{
    int i = 0;
    for(Neighbors::iterator it = neighbors.begin(); it != neighbors.end(); ++it)
    {
        Node* node = Graph::getNode(*it);
        Label listened_label = node->speak();
        if(isLabelListened(listened_label))
            mylistener[listened_label]++;
        else
            mylistener[listened_label] = 1;
        listen_count++;
        i++;
    }
    // End of listening phase
    Label popular_label = getPopularLabel();
    // Add the popular_label to mymap
    if(isCommunityPresent(popular_label))
        mymap[popular_label]++;
    else
        mymap[popular_label] = 1;
    community_count++;
    listen_count = 0;
    mylistener.clear();
}


Label Node::speak(){
	Label mostLabel=nodeID;//returns most probable label
	double randy = doubleRand();
	double intervalEdge = 0;
	Community_Map::iterator mapIt;
	for (mapIt = mymap.begin(); mapIt!=mymap.end(); ++mapIt){
		Label currentLabel = mapIt->first;
		unsigned int currentLabelCount = mapIt->second;  //points to value
		intervalEdge = intervalEdge + ((double)currentLabelCount)/community_count;
		if(randy<=intervalEdge){
			return currentLabel;
		}

	}

	return mostLabel;
}

double Node::doubleRand(){
	double f = (double)rand()/RAND_MAX;
	return f;
}

Community_Map Node::getMyMap()
{
    return mymap;
}

unsigned int Node::getTotalCommunityCount()
{
    return community_count;
}

