//
// Created by Luca De Mori on 29/12/2017.
//


#include "Event.h"

Event::Event(unsigned int t, unsigned int n1, unsigned int n2, e_type e) : t(t), n1(n1), n2(n2), e(e) {}

bool Event::operator<(const Event &rhs) const {
    return this->t < rhs.t;
}

ostream& operator<<(ostream &os, const Event &rhs) {
    os    << rhs.t << " " << rhs.n1 << " " << rhs.n2 << " " << ((rhs.e)?'S':'C') << endl;
}