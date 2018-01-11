//
// Created by luca on 11/01/18.
//

#include "Node.h"

void Node::add_nbr(unsigned int nbr) {
    nbrs.insert(nbr);
    cout << "[DEBUG] Node::add_nbr: added" << nbr << endl;
}

void Node::remove_nbr(unsigned int nbr) {
    nbrs.erase(nbr);
    cout << "[DEBUG] Node::remove_nbr: deleted" << nbr << endl;
}

ostream& operator<<(ostream &os, const Node &node) {

    os << "d= " << node.get_degree() << ", l:{ ";
    set<unsigned int>::iterator it;
    for (it=node.nbrs.begin(); it!=node.nbrs.end(); ++it) {
        os << *it << " ";
    }

    os << "}";

}