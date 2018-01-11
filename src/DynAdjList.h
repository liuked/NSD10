//
// Created by luca on 11/01/18.
//

#ifndef NSD10_DYNADJLIST_H
#define NSD10_DYNADJLIST_H

#include "DynamicVector.h"
#include "Node.h"

class DynAdjList {

public:
    DynAdjList(unsigned int num_nodes);

    void add_link(unsigned int n1, unsigned int n2, bool debug = false);
    void delete_link(unsigned int n1, unsigned int n2, bool debug = false);

    friend ostream& operator<<(ostream& os, const DynAdjList& adj);

private:
    DynamicVector<Node> nodes;

};


#endif //NSD10_DYNADJLIST_H
