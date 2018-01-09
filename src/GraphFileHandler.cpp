//
// Created by Luca De Mori on 28/12/2017.
//

#include "GraphFileHandler.h"

int GraphFileHandler::remove_offest(string in_fn, string out_fn, bool debug) {

    // Variables
    fstream      infile;
    fstream      outfile;
    unsigned int t_min;
    // ---------------------------------------------------------------------------------------------


    if (debug) cout << "[DEBUG] - GraphFileHandler::remove_offest: starting the function..." << endl;

    if (debug)
        cout << "[DEBUG] - GraphFileHandler::remove_offest: opening the file..." << endl;

    infile.open(in_fn, ios::in);

    // ---   ---
    if (infile.is_open()) {
        if(debug) cout <<  "[DEBUG] - GraphFileHandler::remove_offest: graph opening succeed! measuring size and volume..." << endl;
        t_min = find_minimum(infile, debug);

        if (debug) cout << "[DEBUG] - GraphFileHandler::remove_offest: min value: " << t_min;
        if (debug) cout << "[DEBUG] - GraphFileHandler::remove_offest: done" << endl;

        infile.close();

    } else {
        cout << "[ERROR] - GraphFileHandler::remove_offest: unable to open the file " << in_fn << endl;
        return -1;
    }

    outfile.open(out_fn, ios::out);


    // ---   ---
    if (outfile.is_open()) {

        infile.open(in_fn, ios::in);

        if (infile.is_open()) {

            if(debug) cout <<  "[DEBUG] - GraphFileHandler::remove_offest: graph opening succeed! writing normalized file..." << endl;

            write_normalized(infile, outfile, t_min, debug);

            if (debug) cout << "[DEBUG] - GraphFileHandler::remove_offest: done" << endl;

            infile.close();
            outfile.close();

        } else {
            cout << "[ERROR] - GraphFileHandler::remove_offest: unable to open the file " << in_fn << endl;
            return -1;
        }
    } else {
        cout << "[ERROR] - GraphFileHandler::remove_offest: unable to open the file " << out_fn << endl;
        return -1;
    }


}

int GraphFileHandler::write_normalized(fstream &infile, fstream &outfile, unsigned int offest, bool debug) {
    unsigned int line[4];

    while(!infile.eof()){

        line[0] = line[1] = line[2] = line[3] = -1;
        infile >> line[0] >> line[1] >>  line[2] >> line[3];

        if (line[0]==-1||line[1]==-1||line[2]==-1||line[3]==-1){
            continue;
        }

        outfile << line[0] << " " << line[1] << " " <<  line[2]-offest << " " << line[3]-offest << endl;

        if (debug)
            cout << line[0] << " " << line[1] << " " <<  line[2]-offest << " " << line[3]-offest << endl;

    }
}

unsigned int GraphFileHandler::find_minimum(fstream &infile, bool debug) {

    unsigned int line[4];
    unsigned int t_min;

    t_min = -1;

    while(!infile.eof()){

        infile >> line[0] >> line[1] >>  line[2] >> line[3];

        if (line[0]==-1||line[1]==-1||line[2]==-1||line[3]==-1){
            continue;
        }

        if (debug)
            cout << line[0] << " " << line[1] << " " <<  line[2] << " " << line[3]<< endl;

        if (line[2] < t_min){
            t_min = line[2];
        }

    }

    return t_min;
}

GraphFileHandler::GraphFileHandler() {}


int GraphFileHandler::generate_event_list(string in_fn, string out_fn, bool debug) {

    fstream         infile;
    fstream         outfile;
    unsigned int    line[4];    // n1 n2 ts te
    multiset<Event> events;


    if (debug) cout << "[DEBUG] - GraphFileHandler::grnerate_event_list: starting the function..." << endl;
    if (debug) cout << "[DEBUG] - GraphFileHandler::grnerate_event_list: opening the file..." << endl;

    infile.open(in_fn, ios::in);

    // ---   ---

    if (infile.is_open()) {

        if(debug) cout <<  "[DEBUG] - GraphFileHandler::grnerate_event_list: graph opening succeed! Grnerating event list" << endl;

        while(!infile.eof()) {

            line[0] = line[1] = line[2] = line[3] = -1;

            // n1 n2 ts te
            infile >> line[0] >> line[1] >> line[2] >> line[3];

            if (line[0]==-1||line[1]==-1||line[2]==-1||line[3]==-1){
                continue;
            }

            if(debug) cout <<  "[DEBUG] - GraphFileHandler::grnerate_event_list: read " <<  line[0] << line[1] << line[2] << line[3] << endl;

            // link creation
            events.insert(Event(line[2],  // t
                                line[0],  // n1
                                line[1],  // n2
                                C         // event 0=C, 1=S
                          )
            );

            if(debug) cout <<  "[DEBUG] - GraphFileHandler::grnerate_event_list: generating\n       " << Event(line[2],line[0],line[1],C);

            // link suppression
            events.insert(Event(line[3] + 1, // t
                                line[0],   // n1
                                line[1],   // n2
                                S          // event 0=C, 1=S
                          )
            );

            if(debug) cout <<  "   and " << Event(line[3]+1,line[0],line[1],S) << endl;

        }


        if (debug) cout << "[DEBUG] - GraphFileHandler::grnerate_event_list: done" << endl;

        infile.close();

    } else {
        cout << "[ERROR] - GraphFileHandler::grnerate_event_list: unable to open the file " << in_fn << endl;
        return -1;
    }

    outfile.open(out_fn, ios::out);

    if (outfile.is_open()) {
        if(debug) cout <<  "[DEBUG] - GraphFileHandler::grnerate_event_list: output file opening succeed! Writing events list " << endl;

        while (events.begin()!=events.end()){
            outfile << events.begin()->t << " " << events.begin()->n1 << " " << events.begin()->n2 << " " << ((events.begin()->e)?'S':'C') << endl;
            if (debug) cout    << events.begin()->t << " " << events.begin()->n1 << " " << events.begin()->n2 << " " << ((events.begin()->e)?'S':'C') << endl;
            events.erase(events.begin());
        }

        if (debug) cout << "[DEBUG] - GraphFileHandler::grnerate_event_list: done" << endl;
        outfile.close();

    } else {
        cout << "[ERROR] - GraphFileHandler::grnerate_event_list: unable to open the file " << out_fn << endl;
        return -1;
    }

}

int GraphFileHandler::compute_intercont_distr(string ev_list_fn, string intercont_fn, string distr_fn, bool debug) {


    // Variables
    fstream       infile;
    fstream       outfile;
    unsigned int  line[3];
    char          e;
    unsigned int  t_intercont;

    DynamicVector<unsigned int> distr(MIN_INTERCONTACT);

    pair<unsigned int, unsigned int> c;
    map<pair<unsigned int, unsigned int>, unsigned int> contact;
    map<pair<unsigned int, unsigned int>, unsigned int>::iterator c_it;

    // ---------------------------------------------------------------------------------------------


    if (debug) cout << "[DEBUG] - GraphFileHandler::compute_intercont_distr: starting the function..." << endl;

    if (debug)
        cout << "[DEBUG] - GraphFileHandler::compute_intercont_distr: opening the file..." << endl;

    infile.open(ev_list_fn, ios::in);


    // ---   ---
    if (infile.is_open()) {

        outfile.open(intercont_fn, ios::out);

        if (outfile.is_open()) {

            if (debug)
                cout
                        << "[DEBUG] - GraphFileHandler::compute_intercont_distr: graph opening succeed! Counting inter-contacts time..."
                        << endl;


            while (!infile.eof()) {

                line[0] = line[1] = line[2] = -1;
                e = '\0';

                // t n1 n2 e
                infile >> line[0] // t
                       >> line[1] // n1
                       >> line[2] // n2
                       >> e;      // e

                if (line[0] == -1 || line[1] == -1 || line[2] == -1 || e == '\0') {
                    continue;
                }

                if (debug) cout << line[0] << " " << line[1] << " " << line[2] << " " << e << endl;

                // if a contact is finisced i store the event in memory (in the map) to be able to measure the time to the next contact
                if (e == 'S') {
                    c.first = line[1];      // n1
                    c.second = line[2];     // n2
                    contact[c] = line[0];   // t
                }

                if (e == 'C') {

                    c.first = line[1];      // n1
                    c.second = line[2];     // n2

                    // if there is a record in the map, then calculate the inter contact duration time
                    c_it = contact.find(c);
                    if (c_it != contact.end()) {
                        t_intercont = line[0] - contact[c];   // = time this event (new C) - time previous (old S)

                        // write log in file
                        outfile << "interc " << line[1] << "-" << line[2] << " duration: " << t_intercont << endl;

                        if (debug)
                            cout << "[DEBUG] - GraphFileHandler::compute_intercont_distr: (pair " << line[1] << "-"
                                 << line[2] << ") elapsed time: " << t_intercont << endl;

                        // remove the record
                        contact.erase(c_it);

                        // increment by one the counter in the distribution array
                        distr[t_intercont] ++;
                    }


                }


            }

            if (debug) cout << "[DEBUG] - GraphFileHandler::remove_offest: done" << endl;

            infile.close();
            outfile.close();


            // Write distribution file
            outfile.open(distr_fn, ios::out);

            if (outfile.is_open()) {
                if (debug)
                    cout    << "[DEBUG] - GraphFileHandler::grnerate_event_list: output file opening succeed! Writing distribution file "
                            << endl;

                distr.f_print(outfile);

                if (debug) cout << "[DEBUG] - GraphFileHandler::grnerate_event_list: done" << endl;

                outfile.close();

            } else {
                cout << "[ERROR] - GraphFileHandler::grnerate_event_list: unable to open the file " << distr_fn << endl;
                return -1;
            }


        } else {
            cout << "[ERROR] - GraphFileHandler::grnerate_event_list: unable to open the file " << ev_list_fn << endl;
            return -1;
        }

    }else {
        cout << "[ERROR] - GraphFileHandler::grnerate_event_list: unable to open the file " << intercont_fn << endl;
        return -1;
    }


}


int GraphFileHandler::compute_avg_degree(string ev_list_fn, string deg_evo_fn, bool debug) {


    // Variables
    fstream       infile;
    fstream       outfile;
    unsigned int  line[3];
    char          e;
    unsigned int  num_nodes;
    unsigned int  t_max;
    float         avg_deg;
    DynamicVector<unsigned int> degree(MIN_NODES);
    // ---------------------------------------------------------------------------------------------


    if (debug) cout << "[DEBUG] - GraphFileHandler::compute_avg_degree: starting the function..." << endl;

    if (debug)
        cout << "[DEBUG] - GraphFileHandler::compute_avg_degree: opening the file..." << endl;

    infile.open(ev_list_fn, ios::in);

    if (infile.is_open()) {
        if (debug)
            cout << "[DEBUG] - GraphFileHandler::compute_avg_degree: graph opening succeed! Counting nodes..."
                 << endl;

        num_nodes = 0;

        while (!infile.eof()) {
            line[0] = line[1] = line[2] = -1;
            e = '\0';

            // t n1 n2 e
            infile >> line[0] // t
                   >> line[1] // n1
                   >> line[2] // n2
                   >> e;      // e

            if (line[0] == -1 || line[1] == -1 || line[2] == -1 || e == '\0') {
                continue;
            }

            // since n2>n1 by definition, I check only n2
            if (line[2]>num_nodes){
                num_nodes = line[2];
            }

            t_max = line[0];

        }
        if (debug) cout << "[DEBUG] - GraphFileHandler::compute_avg_degree: num_nodes= " << num_nodes << endl;
        if (debug) cout << "[DEBUG] - GraphFileHandler::compute_avg_degree: max time= " << t_max << endl << endl;

        if (num_nodes==0){
            cout << "[ERROR] - GraphFileHandler::compute_avg_degree: graph is empty" << endl;
            return -1;
        }

        if (debug) cout << "[DEBUG] - GraphFileHandler::compute_avg_degree: done" << endl;

        infile.close();


    }else {
        cout << "[ERROR] - GraphFileHandler::compute_avg_degree: unable to open the file " << ev_list_fn << endl;
        return -1;
    }




    infile.open(ev_list_fn, ios::in);

    // ---   ---
    if (infile.is_open()) {

        outfile.open(deg_evo_fn, ios::out);

        if (outfile.is_open()) {


            DynamicVector<float> deg_evo(t_max+1);
            avg_deg = 0;


            while (!infile.eof()) {
                line[0] = line[1] = line[2] = -1;
                e = '\0';

                // t n1 n2 e
                infile >> line[0] // t
                       >> line[1] // n1
                       >> line[2] // n2
                       >> e;      // e

                if (line[0] == -1 || line[1] == -1 || line[2] == -1 || e == '\0') {
                    continue;
                }

                if (debug) cout << line[0] << " " << line[1] << " " << line[2] << " " << e << endl;

                // when a link establish or estinguish, it add or remove 2 to the total degree -> avg_deg +- 2/num_nodes
                // update degree increase if C, decrease if S
                if (e == 'S') {
                    //degree[line[1]] --;
                    //degree[line[2]] --;
                    avg_deg -= (float)2/num_nodes;
                    if (debug) cout << "avg_deg decremented: " << avg_deg << endl;
                }

                if (e == 'C') {
                    //degree[line[1]] ++;
                    //degree[line[2]] ++;
                    avg_deg += (float)2/num_nodes;
                    if (debug) cout << "avg_deg incremented: " << avg_deg << endl;
                }

                deg_evo[line[0]] = avg_deg;

            }

            outfile << "# Nodes:   " << num_nodes << endl;
            outfile << "# Time:    "  << t_max << endl;

            deg_evo.f_print_nz(outfile);

            infile.close();
            outfile.close();

        } else {
            cout << "[ERROR] - GraphFileHandler::compute_avg_degree: unable to open the file " << deg_evo_fn << endl;
            return -1;
        }

    }else {
        cout << "[ERROR] - GraphFileHandler::compute_avg_degree: unable to open the file " << ev_list_fn << endl;
        return -1;
    }

}


int GraphFileHandler::compute_link_evo_fract(string ev_list_fn, string link_evo_fn, bool debug) {

    // Variables
    fstream       infile;
    fstream       outfile;
    unsigned int  line[3];
    char          e;
    unsigned int  t_max;
    unsigned int  num_nodes;
    unsigned long max_links;
    unsigned long existing_links;
    unsigned long old_exist_links;
    int           created_links;
    int           deleted_links;
    unsigned int  t_current;

    // ---------------------------------------------------------------------------------------------


    if (debug) cout << "[DEBUG] - GraphFileHandler::compute_link_evo_fract: starting the function..." << endl;

    if (debug)
        cout << "[DEBUG] - GraphFileHandler::compute_link_evo_fract: opening the file..." << endl;

    infile.open(ev_list_fn, ios::in);

    if (infile.is_open()) {
        if (debug)
            cout << "[DEBUG] - GraphFileHandler::compute_link_evo_fract: graph opening succeed! Counting nodes..."
                 << endl;

        num_nodes = 0;

        while (!infile.eof()) {
            line[0] = line[1] = line[2] = -1;
            e = '\0';

            // t n1 n2 e
            infile >> line[0] // t
                   >> line[1] // n1
                   >> line[2] // n2
                   >> e;      // e

            if (line[0] == -1 || line[1] == -1 || line[2] == -1 || e == '\0') {
                continue;
            }

            // since n2>n1 by definition, I check only n2
            if (line[2]>num_nodes){
                num_nodes = line[2];
            }
            t_max = line[0];

        }



        if (num_nodes==0){
            cout << "[ERROR] - GraphFileHandler::compute_link_evo_fract: graph is empty" << endl;
            return -1;
        }

        max_links = num_nodes*(num_nodes-1)/2;
        if (debug) cout << "[DEBUG] - GraphFileHandler::compute_link_evo_fract: num_nodes= " << num_nodes << " max_links= " << max_links << endl;

        if (debug) cout << "[DEBUG] - GraphFileHandler::compute_link_evo_fract: done" << endl;

        infile.close();


    }else {
        cout << "[ERROR] - GraphFileHandler::compute_link_evo_fract: unable to open the file " << ev_list_fn << endl;
        return -1;
    }

    DynamicVector<LinkEvolutionFraction> fraction(t_max+1);
    LinkEvolutionFraction avg_frac(0);

    existing_links = old_exist_links = 0;
    created_links = deleted_links = 0;

    t_current = 0;

    infile.open(ev_list_fn, ios::in);

    // ---   ---
    if (infile.is_open()) {

        outfile.open(link_evo_fn, ios::out);

        if (outfile.is_open()) {

            while (!infile.eof()) {

                line[0] = line[1] = line[2] = -1;
                e = '\0';

                // t n1 n2 e
                infile >> line[0] // t
                       >> line[1] // n1
                       >> line[2] // n2
                       >> e;      // e

                if (line[0] == -1 || line[1] == -1 || line[2] == -1 || e == '\0') {
                    continue;
                }

                if (t_current!=line[0]) {
                    fraction[t_current].created = (max_links != old_exist_links) ? ((float) created_links / (max_links - old_exist_links)) : -1;
                    fraction[t_current].deleted = (old_exist_links != 0) ? ((float) deleted_links / old_exist_links) : -1;

                    if (debug) cout << "[DEBUG] - GraphFileHandler::compute_link_evo_fract: " << endl
                         << "     STATS AT TIME   " << t_current << endl
                         << "     old exis links= " << old_exist_links << endl
                         << "     link_created=   " << created_links << endl
                         << "     link deleted=   " << deleted_links << endl
                         << "     fractions=      " << fraction[t_current] << endl;
                    old_exist_links = existing_links;
                    created_links = deleted_links = 0;
                    t_current = line[0];
                }

                if (debug) cout << line[0] << " " << line[1] << " " << line[2] << " " << e << endl;


                // update link counter (existing_links: increase if C, decrease if S
                if (e == 'S') {
                    if(existing_links>0) existing_links--;
                    deleted_links++;
                    //if (debug) cout << "links decremented: " << existing_links << endl;
                }

                if (e == 'C') {
                    existing_links++;
                    created_links++;
                    //if (debug) cout << "links incremented: " << existing_links << endl;
                }



            }

            // compute averages
            unsigned int c_count = 0;
            unsigned int d_count = 0;

            for (unsigned int i = 0; i < fraction.getSize(); i++) {
                if (fraction[i].created != -1) {
                    avg_frac.created += fraction[i].created;
                    c_count++;
                }
                if (fraction[i].deleted != -1) {
                    avg_frac.deleted += fraction[i].deleted;
                    d_count++;
                }
            }

            avg_frac.created /= c_count;
            avg_frac.deleted /= d_count;

            outfile << "# Nodes:   " << num_nodes << endl;
            outfile << "# Time:    "  << t_max << endl;
            outfile << "# Averages:" << endl << "# " << avg_frac.created << endl << "# " << avg_frac.deleted << endl;

            cout << "Averages:" << endl << avg_frac.created << endl << avg_frac.deleted << endl;
            cout << "Nodes: " << num_nodes << endl;
            cout << "Time: "  << t_max;


            fraction.f_print(outfile);


            infile.close();
            outfile.close();

        } else {
            cout << "[ERROR] - GraphFileHandler::compute_avg_degree: unable to open the file " << link_evo_fn << endl;
            return -1;
        }

    }else {
        cout << "[ERROR] - GraphFileHandler::compute_avg_degree: unable to open the file " << ev_list_fn << endl;
        return -1;
    }
}

ostream &operator<<(ostream &os, const LinkEvolutionFraction &fraction) {
    os <<  fraction.created << " " << fraction.deleted;
    return os;
}


int GraphFileHandler::compute_ic_cdf(string distr_fn, string cdf_fn, bool debug) {

    // Variables
    fstream      infile;
    fstream      outfile;
    unsigned int t;     // ic duration
    unsigned int occ;   // occurencies
    unsigned int cum;   // cumulative occurrencies
    // ---------------------------------------------------------------------------------------------


    if (debug) cout << "[DEBUG] - GraphFileHandler::compute_ic_cdf: starting the function..." << endl;

    if (debug)
        cout << "[DEBUG] - GraphFileHandler::compute_ic_cdf: opening the file..." << endl;

    outfile.open(cdf_fn, ios::out);

    // ---   ---
    if (outfile.is_open()) {

        infile.open(distr_fn, ios::in);

        if (infile.is_open()) {

            if(debug) cout <<  "[DEBUG] - GraphFileHandler::compute_ic_cdf: graph opening succeed! computing cumulative distribution..." << endl;

            t = occ = -1;
            cum = 0;

            while (!infile.eof()) {
                // t occ
                infile >> t    // t
                       >> occ; // occ

                if (t == -1 || occ == -1) {
                    continue;
                }

                if (debug) cout << t << " " << occ << endl;

                // accumulate occurrences and write to file
                cum += occ;
                outfile << t << " " << cum << endl;


            }


            if (debug) cout << "[DEBUG] - GraphFileHandler::compute_ic_cdf: done" << endl;

            infile.close();
            outfile.close();

        } else {
            cout << "[ERROR] - GraphFileHandler::compute_ic_cdf: unable to open the file " << distr_fn << endl;
            return -1;
        }
    } else {
        cout << "[ERROR] - GraphFileHandler::compute_ic_cdf: unable to open the file " << cdf_fn << endl;
        return -1;
    }


}


LinkEvolutionFraction::LinkEvolutionFraction() : created(0), deleted(-1) {}

LinkEvolutionFraction::LinkEvolutionFraction(int common_default)  : created(common_default), deleted(common_default)  {}

bool LinkEvolutionFraction::operator!=(const int &rhs) const {
    return (this->deleted!=0||this->created!=0);
}

LinkEvolutionFraction LinkEvolutionFraction::operator/(const int &rhs) const {
    LinkEvolutionFraction temp;

    temp.created = (float)this->created/rhs;
    temp.deleted = (float)this->deleted/rhs;

    return temp;
}

LinkEvolutionFraction& LinkEvolutionFraction::operator+=(const LinkEvolutionFraction &rhs) {
    this->created += rhs.created;
    this->deleted += rhs.deleted;

    return *this;
}



