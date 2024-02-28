/*
 *  MetroSim.cpp
 *  Isaac Saland
 *  2/22/2024
 *
 *
 *  implementation of the MetroSim class
 *
 */

#include "MetroSim.h"
#include <fstream>
#include <string>
#include <vector>

/*
 * name: constructor for MetroSim
 * purpose: fills up the stations and train vector
 * args: ifstream &input
 * returns: none
*/
MetroSim::MetroSim(std::ifstream &input) {
    currStation = 0;
    std::string statName;

    do {
        std::getline(input, statName);
        if (statName == "") {
            train.resize(stations.size());
            currStation = 0;
            return ;
        }
        
        PassengerQueue queue;
        Station temp(statName, queue);
        stations.push_back(temp);

        currStation++;
    } while(not input.eof());

    currStation = 0;
}

/*
 * name: addPassengerToStation
 * purpose: adds the passenger to its correct station
 * args: Passenger &pass
 * returns: none
*/
void MetroSim::addPassengerToStation(Passenger pass) {
    stations[pass.from].passengers.enqueue(pass);
    printMetroSim(std::cout);
}

/*
 * name: addPassengerToTrain
 * purpose: adds the passengers at currstation to train
 * args: none
 * returns: none
*/
void MetroSim::addPassengersToTrain() {
    while(stations[currStation].passengers.size() > 0) {
        Passenger pass = stations[currStation].passengers.front();
        train[pass.to].enqueue(pass);
        stations[currStation].passengers.dequeue();
    }
}

/*
 * name: move
 * purpose: moves the train to the next index or wraps, also moves passengers
 * args: ostream &output
 * returns: none
*/
void MetroSim::move(std::ostream &output) {
    addPassengersToTrain();

    currStation++;

    if(currStation >= (int) stations.size()) currStation = 0;

    emptyCar(currStation, output);

    printMetroSim(std::cout);
}

/*
 * name: emptyCar
 * purpose: dequeues all passengers in a car of the train
 * args: int car, ostream &output
 * returns: none
 * note: helper method for move()
*/
void MetroSim::emptyCar(int car, std::ostream &output) {
    int size = train[car].size();
    for(int i = 0; i < size; i++) {
        output << "Passenger " << train[car].front().id
        << " left train at station " << stations[car].name << std::endl;
        train[car].dequeue();
    }
}

/*
 * name: printMetroSim
 * purpose: prints the info to output
 * args: ostream &output
 * returns: none
*/
void MetroSim::printMetroSim(std::ostream &output) {
        output << "Passengers on the train: {";
        for(int i = 0; i < (int) train.size(); i++) {
                train[i].print(output);
        }
        output << "}" << std::endl;

        for(int i = 0; i < (int) stations.size(); i++) {
                if(i != currStation) output << "       [";
                else output << "TRAIN: [";
                
                output << i << "] " << stations[i].name << " {";
                stations[i].passengers.print(output);
                output << "}" << std::endl;
        }
        output << "Command? ";
}