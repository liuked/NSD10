
#include "GraphFileHandler.h"

using namespace std;

int main() {

    int start = (int)time(nullptr);

    string infn = "../graphs/sample.graph";
    string normfn = "../graphs/normalized.out";
    string evlistfn = "../graphs/event_list.out";
    string distrfn = "../graphs/distr.out";
    string intercfn = "../graphs/inter-cont.log";
    string degevofn = "../graphs/deg-evo.out";
    string linkfracfn = "../graphs/link_frac.out";

    bool debug = false;

    ifstream file(infn);
    if (!file.good()) {
        cout << time(nullptr)-start << "s: " <<  "[ERROR] - main(): No such file ..." << endl;
        exit(0);
    }

    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): parsing file..." << endl;
    GraphFileHandler::remove_offest(infn, normfn, true);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;

    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): genrating event list..." << endl;
    GraphFileHandler::generate_event_list(normfn, evlistfn, true);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;

    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): computing intercontacts duration time..." << endl;
    GraphFileHandler::compute_intercont_distr(evlistfn, intercfn, distrfn, true);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;


    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): computing intercontacts duration time..." << endl;
    GraphFileHandler::compute_avg_degree(evlistfn, degevofn, true);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;

    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): computing link evolution fractions..." << endl;
    GraphFileHandler::compute_link_evo_fract(evlistfn, linkfracfn, true);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;

    return 0;
}