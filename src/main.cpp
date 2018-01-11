
#include "GraphFileHandler.h"

using namespace std;

int main() {

    int start = (int)time(nullptr);


    string infn = "../graphs/sample.graph";
    string normfn = "../graphs/normalized.out";
    string evlistfn = "../graphs/event_list.out";
    string distrfn = "../graphs/distr.out";
    string degdistrfn = "../graphs/deg_distr.out";
    string cdffn = "../graphs/ic_cdf.out";
    string intercfn = "../graphs/inter-cont.log";
    string degevofn = "../graphs/deg-evo.out";
    string linkfracfn = "../graphs/link_frac.out";
    string densevofn = "../graphs/dens_evo.out";
    string trfn = "../graphs/trans_ratio.out";

    bool debug = false;

    // ifstream file(infn);
    ifstream file(evlistfn);

    if (!file.good()) {
        cout << time(nullptr)-start << "s: " <<  "[ERROR] - main(): No such file ..." << endl;
        exit(0);
    }

    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): parsing file..." << endl;
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