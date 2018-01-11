//
// Created by luca on 11/01/18.
//

#ifndef NSD10_NODE_H
#define NSD10_NODE_H

#include <iostream>
#include <set>

using namespace std;

class Node {

public:

    void add_nbr(unsigned int nbr);
    void remove_nbr(unsigned int nbr);

    unsigned int get_degree() const { return nbrs.size(); }

    friend ostream& operator<<(ostream& os, const Node& node);

private:
    set<unsigned int> nbrs;

};


#endif //NSD10_NODE_H
