//
// Created by luca on 11/01/18.
//

#include "DynAdjList.h"

void DynAdjList::add_link(unsigned int n1, unsigned int n2, bool debug) {
    nodes[n1].add_nbr(n2);
    nodes[n2].add_nbr(n1);
}

void DynAdjList::delete_link(unsigned int n1, unsigned int n2, bool debug) {
    nodes[n1].remove_nbr(n2);
    nodes[n2].remove_nbr(n1);
}

ostream& operator<<(ostream &os, const DynAdjList &adj) {
    adj.nodes.f_print(os);
}

DynAdjList::DynAdjList(unsigned int num_nodes) {
    nodes[num_nodes];
}
