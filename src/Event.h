//
// Created by Luca De Mori on 29/12/2017.
//

#ifndef NSD10_EVENT_H
#define NSD10_EVENT_H

#include <iostream>
#include <cstdlib>

using namespace std;

enum e_type{C,S};

class Event {
public:
    unsigned int t;
    unsigned int n1;
    unsigned int n2;
    e_type       e;

    Event(unsigned int t, unsigned int n1, unsigned int n2, e_type e);

    bool operator<( const Event& rhs ) const;
    friend ostream& operator<<(ostream& os, const Event& rhs);

};


#endif //NSD10_EVENT_H
