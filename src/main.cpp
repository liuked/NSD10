
#include "GraphFileHandler.h"

using namespace std;

int main() {

    int start = (int)time(nullptr);

    /*
    string infn = "../RollerNet/RollerNet";
    string normfn = "../RollerNet/normalized.out";
     */
    string evlistfn = "../infocomm_edgeMarkovian/infocomm_edgeMarkovian.graph";
    string distrfn = "../infocomm_edgeMarkovian/distr.out";
    string cdffn = "../infocomm_edgeMarkovian/ic_cdf.out";
    string intercfn = "../infocomm_edgeMarkovian/inter-cont.log";
    string degevofn = "../infocomm_edgeMarkovian/deg-evo.out";
    string linkfracfn = "../infocomm_edgeMarkovian/link_frac.out";

    bool debug = false;

    // ifstream file(infn);
    ifstream file(evlistfn);

    if (!file.good()) {
        cout << time(nullptr)-start << "s: " <<  "[ERROR] - main(): No such file ..." << endl;
        exit(0);
    }
/*
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): parsing file..." << endl;
    GraphFileHandler::remove_offest(infn, normfn, debug);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;

    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): genrating event list..." << endl;
    GraphFileHandler::generate_event_list(normfn, evlistfn, debug);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;
*/
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): computing intercontacts duration time..." << endl;
    GraphFileHandler::compute_intercont_distr(evlistfn, intercfn, distrfn, debug);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;

    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): computing ic cdf..." << endl;
    GraphFileHandler::compute_ic_cdf(distrfn, cdffn, debug);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;

    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): computing intercontacts duration time..." << endl;
    GraphFileHandler::compute_avg_degree(evlistfn, degevofn, debug);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;

    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): computing link evolution fractions..." << endl;
    GraphFileHandler::compute_link_evo_fract(evlistfn, linkfracfn, debug);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;

    return 0;
}