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

    //  Functions to be used starting from an "link list" file

    /**** REMOVE OFFSET ****
     *
     * arguments:
     *      - in_fn:  input "link list" file
     *      - out_fn: file name where to save the normalized file (t starting from 0)
     *      - debug:  whether to print or not the debug lines
     */
    static int remove_offest(string in_fn, string out_fn, bool debug=false);

    /**** GENERATE EVENT LIST FILE ****
    *
    * arguments:
    *      - in_fn:  input "link list" file (normalized or not)
    *      - out_fn: file name where to write the event list
    *      - debug:  whether to print or not the debug lines
    */
    static int generate_event_list(string in_fn, string out_fn, bool debug=false);
    //--------------------------------------------------------------------------------


    // Functions to be used starting from an "event list" file

    /**** INTERCONTACT DISTRIBUTION ****
     *
     * arguments:
     *      - ev_list_fn:   event list file name
     *      - intercont_fn: file where to save the log of the detected intercontacts
     *      - distr_fn:     file where to save the distribution of the intercontacts in
     *                      the form: <duration> <#interc>
     *      - debug:        whether to print or not the debug lines
     */
    static int compute_intercont_distr(string ev_list_fn, string intercont_fn, string distr_fn, bool debug=false);


    /**** INTERCONTACT CUMULATIVE DISTRIBUTION ****
     *
     * arguments:
     *      - distr_fn: the file name containing the row distribution to integrate
     *      - cdf_fn:   file where to save the cumulative distribution
     *      - debug:    whether to print or not the debug lines
     */
    static int compute_ic_cdf(string distr_fn, string cdf_fn, bool debug=false);

    /**** AVERAGE DEGREE OF THE GRAPH (for each t) ****
     *
     * arguments:
     *      - ev_list_fn:   event list file name
     *      - deg_evo_fn:   file where to save the average degree evolution in the form <t> <avgDegree>
     *      - deg_distr_fn: file where to save the distribution of the average degree during the graph life
     *      - debug:    whether to print or not the debug lines
     */
    static int compute_avg_degree(string ev_list_fn, string deg_evo_fn, string deg_distr_fn, bool debug=false);

    /**** FRACTION OF THE CREATED AND DELETED LINKS (for each t) ****
    *
    * arguments:
    *      - ev_list_fn:  event list file name
    *      - link_evo_fn: file where to save the values of the fractions <t> <frOfCreated> <frOfDeleted>
    *                     if <frOfCreated> is not computable is = -1;
    *      - dens_evo_fn: file where to save the values of the density of the graph per each time instant
    *      - debug:    whether to print or not the debug lines
    */
    static int compute_link_evo_fract(string ev_list_fn, string link_evo_fn, string dens_evo_fn, bool debug=false);

    /**** TRANSITIVE RATIO (for each t) ****
     *
     * arguments:
     *      - ev_list_fn:  event list file name
     *      - tr_evo_fn: file where to save the values of the transitive ratio <t> <TransitiveRatio>
     *      - debug:    whether to print or not the debug lines
     */
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



