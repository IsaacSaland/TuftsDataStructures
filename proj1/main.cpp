/*
 *  main.cpp
 *  Isaac Saland
 *  2/22/2024
 *
 *
 *  the simulation for project MetroSim; handles user/file input
 *
 */

#include <iostream>
#include <fstream>
#include <string>

#include "MetroSim.h"

using namespace std;

/*
 * name: openFile
 * purpose: opens a file, outputs to cerr if failure
 * args: ofstream &output, file name
 * returns: none
*/
void openFile(ofstream &output, string file) {
        output.open(file);

        if(not output.is_open()) {
                cerr << "Error: could not open file " << file << endl;
                exit(EXIT_FAILURE);
        }
}

/*
 * name: openFile
 * purpose: opens a file, outputs to cerr if failure
 * args: ifstream &input, file name
 * returns: none
*/
void openFile(ifstream &input, string file) {
        input.open(file);

        if(not input.is_open()) {
                cerr << "Error: could not open file " << file << endl;
                exit(EXIT_FAILURE);
        }
}

/*
 * name: doSim
 * purpose: handles command input for the simulation and runs the
 *          cooresponding functinos
 * args: istream &input, ostream &output, MetroSim sim, int &currID
 * returns: none
*/
void doSim(istream &input, ostream &output, MetroSim sim, int &currID) {
        sim.printMetroSim(cout);
        string arg1;
        while (true) {
                input >> arg1;
                if(input.eof()) {
                        cout << "Thanks for playing MetroSim. ";
                        cout << "Have a nice day!" << endl;
                        return ;
                }
                else if(arg1 == "p") {
                        int arg2;
                        input >> arg2;
                        int arg3;
                        input >> arg3;
                        Passenger pass = {currID, arg2, arg3};
                        currID++;
                        sim.addPassengerToStation(pass);
                }
                else if(arg1 == "m") {
                        string arg2;
                        input >> arg2;
                        if(arg2 == "f") {
                                cout << "Thanks for playing MetroSim. ";
                                cout << "Have a nice day!" << endl;
                                return ;
                        }
                        else if(arg2 == "m") {
                                sim.move(output);
                        }
                }
        }
}

int main(int argc, char *argv[])
{
        if(argc < 3 or argc > 4) {
                cerr << "Usage: ./MetroSim stationsFile ";
                cerr << "outputFile [commandsFile]" << endl;
                exit(EXIT_FAILURE);
        }

        int currID = 1;
        ifstream stations;
        ofstream output;

        openFile(stations, argv[1]);
        openFile(output, argv[2]);
        MetroSim sim(stations);
        if(argc == 4) {
                ifstream comms;
                openFile(comms, argv[3]);
                doSim(comms, output, sim, currID);
                comms.close();
        }
        else doSim(cin, output, sim, currID);

        stations.close();
        output.close();

        return 0;
}