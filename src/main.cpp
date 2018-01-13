
#include "GraphFileHandler.h"

using namespace std;

int main() {

    int start = (int)time(nullptr);


    /* NEEDED FOR Infocom06 AND RollerNet */
    string infn = "../graphs/sample.graph";
    string normfn = "../graphs/normalized.out";

    /* For GENERATED graphs the file has to be entered HERE */
    // (For Infocom06 and RollerNet this is an output)
    string evlistfn = "../graphs/event_list.out";

    /* OUT FILES */
    string distrfn = "../graphs/distr.out";
    string degdistrfn = "../graphs/deg_distr.out";
    string cdffn = "../graphs/ic_cdf.out";
    string intercfn = "../graphs/inter-cont.log";
    string degevofn = "../graphs/deg-evo.out";
    string linkfracfn = "../graphs/link_frac.out";
    string densevofn = "../graphs/dens_evo.out";
    string trfn = "../graphs/trans_ratio.out";

    // change this variable to print drbug lines (WARNING! Very Verbose!!)
    // you may want to change the single debug value in the single function
    bool debug = false;

    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): normalizing graph file..." << endl;
    GraphFileHandler::remove_offest(infn, normfn, debug);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;

    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): genrating event list..." << endl;
    GraphFileHandler::generate_event_list(normfn, evlistfn, debug);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;

    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): computing intercontacts duration time..." << endl;
    GraphFileHandler::compute_intercont_distr(evlistfn, intercfn, distrfn, debug);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;

    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): computing ic cdf..." << endl;
    GraphFileHandler::compute_ic_cdf(distrfn, cdffn, debug);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;

    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): computing intercontacts duration time..." << endl;
    GraphFileHandler::compute_avg_degree(evlistfn, degevofn, degdistrfn, debug);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;

    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): computing link evolution fractions..." << endl;
    GraphFileHandler::compute_link_evo_fract(evlistfn, linkfracfn, densevofn, debug);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;


    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): computing transitive ratio..." << endl;
    GraphFileHandler::compute_transitive_ratio(evlistfn, trfn, true);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;


/*
    DynamicVector<int> a;

    a.insert_order(1);
    a.insert_order(2);
    a.insert_order(3);
    a.insert_order(5);
    a.insert_order(1);
    a.insert_order(4);
    a.insert_order(9);
    a.insert_order(8);
    a.insert_order(10);

    a.f_print(cout);

    cout << a.find(7) << endl;
*/

    return 0;
}