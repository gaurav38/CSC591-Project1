#ifndef NODE_H
#define NODE_H


class Node
{
    public:
        /** Default constructor */
        Node();
        /** Default destructor */
        virtual ~Node();
        /** Access label
         * \return The current value of label
         */
        Label Getlabel() { return label; }
        /** Access neighbors
         * \return The current value of neighbors
         */
        vector<unsigned_int> Getneighbors() { return neighbors; }
        /** Set neighbors
         * \param val New value to set
         */
        void Setneighbors(vector<unsigned_int> val) { neighbors = val; }
        /** Access mymap
         * \return The current value of mymap
         */
        std::unordered_map<Label,int> Getmymap() { return mymap; }
        /** Set mymap
         * \param val New value to set
         */
        void Setmymap(std::unordered_map<Label,int> val) { mymap = val; }
        /** Access count;
         * \return The current value of count;
         */
        unsigned_int32 Getcount;() { return count;; }
    protected:
    private:
        Label label; //!< Member variable "label"
        vector<unsigned_int> neighbors; //!< Member variable "neighbors"
        std::unordered_map<Label,int> mymap; //!< Member variable "mymap"
        unsigned_int32 count;; //!< Member variable "count;"
};

#endif // NODE_H
