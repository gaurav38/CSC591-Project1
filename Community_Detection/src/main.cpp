#include "Node.h"
#include "SLPA.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{

	SLPA* theSLPA;

	string inFileName=argv[0];

	theSLPA = new SLPA(inFileName);

    Node *node = new Node(1);
    std::cout<<"Label="<<node->Getlabel();
    for(int i=2; i<=10; i++)
        node->AddNeighbor(i);
    Neighbors neighbors = node->Getneighbors();
    Neighbors::iterator it;
    for(it=neighbors.begin(); it<neighbors.end(); it++)
        std::cout<<"\nNeighbors="<<*it;

    node->AddCommunity(3);
    node->AddCommunity(3);
    node->AddCommunity(2);
    std::cout<<"\nCount for Community 3="<<node->GetCommunityCount(3);
    std::cout<<"\nTotal Count="<<node->Getcount();
}
