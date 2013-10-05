#include "Node.h"
#include<iostream>
using namespace std;
int main()
{
    Node node = new Node(1);
    std::cout<<node.isCommunityPresent(1);
    return 0;
}
