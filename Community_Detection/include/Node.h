#include <unordered_map>
##include <vector>
#ifndef NODE_H
#define NODE_H

typedef unsigned_int32 Label;

class Node
{
    public:
        Node(Lable node_label)
        {
            label = node_label;
            std::pair<Label,unsigned_int32> community(label,1);
            mymap.insert(community);
        }
        virtual ~Node();

        Label Getlabel() { return label; }

        vector<unsigned_int> Getneighbors() { return neighbors; }

        void Addneighbor(Label x)
        {
            neighbors.insert(val);
        }

        unsigned_int32 Getcount() { return count; }

        bool isCommunityPresent(Label x)
        {
            std::unordered_map<Label,int>::const_iterator got = mymap.find(x);
            got == mymap.end()? return false : return true;
        }

        int GetCommunityCount(Label x)
        {
            if(isCommunityPresent(x))
            {
                std::unordered_map<Label,int>::const_iterator got = mymap.find(x);
                return got->second;
            }
            else
                return 0;
        }

        void AddCommunity(Label x)
        {
            if(isCommunityPresent(x))
            {
                std::unordered_map<Label,int>::const_iterator got = mymap.find(x);
                got->second++;
            }
            else
            {
                std::pair<Label,unsigned_int32> community(label,1);
                mymap.insert(community);
            }
        }

    protected:
    private:
        Label label;
        vector<unsigned_int> neighbors;
        std::unordered_map<Label,int> mymap;
        unsigned_int32 count;
};

#endif // NODE_H
