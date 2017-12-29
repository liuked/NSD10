
#include "GraphFileHandler.h"

using namespace std;

int main() {

    int start = (int)time(nullptr);

    string infn = "../Infocom/Infocom06";
    string normfn = "../Infocom/normalized.out";
    string evlistfn = "../Infocom/event_list.out";
    string distrfn = "../Infocom/distr.out";
    string intercfn = "../Infocom/inter-cont.log";
    string degevofn = "../Infocom/deg-evo.out";
    string linkfracfn = "../Infocom/link_frac.out";

    bool debug = false;

    ifstream file(infn);
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


    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): computing intercontacts duration time..." << endl;
    GraphFileHandler::compute_avg_degree(evlistfn, degevofn, debug);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;

    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): computing link evolution fractions..." << endl;
    GraphFileHandler::compute_link_evo_fract(evlistfn, linkfracfn, debug);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;

    return 0;
}