//
// Created by Luca De Mori on 28/12/2017.
//

#ifndef NSD10_GRAPHFILEHANDLER_H
#define NSD10_GRAPHFILEHANDLER_H

#define MIN_INTERCONTACT 10
#define MIN_NODES 10

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <set>
#include <map>
#include "Event.h"
#include "DynamicVector.h"
#include "DynAdjList.h"

using namespace std;

class GraphFileHandler {
public:

    GraphFileHandler();

    static int remove_offest(string in_fn, string out_fn, bool debug=false);
    static int generate_event_list(string in_fn, string out_fn, bool debug=false);

    // starting from a event list file
    static int compute_intercont_distr(string ev_list_fn, string intercont_fn, string distr_fn, bool debug=false);
    static int compute_ic_cdf(string distr_fn, string cdf_fn, bool debug=false);
    static int compute_avg_degree(string ev_list_fn, string deg_evo_fn, string deg_distr_fn, bool debug=false);
    static int compute_link_evo_fract(string ev_list_fn, string link_evo_fn, string dens_evo_fn, bool debug=false);

    static int compute_transitive_ratio(string ev_list_fn, string tr_evo_fn, bool debug=false);

private:
    static unsigned int find_minimum(fstream &infile, bool debug=false);
    static int          write_normalized(fstream &infile, fstream &outfile, unsigned int offest, bool debug=false);

protected:



};


class LinkEvolutionFraction {
public:
    LinkEvolutionFraction();
    LinkEvolutionFraction(int common_default);
    friend ostream &operator<<(ostream &os, const LinkEvolutionFraction &fraction);

    bool operator!=(const int &rhs) const;

    LinkEvolutionFraction operator/(const int &rhs) const;
    LinkEvolutionFraction& operator+=(const LinkEvolutionFraction &rhs);

    float created;
    float deleted;


private:

};






#endif //NSD10_GRAPHFILEHANDLER_H



