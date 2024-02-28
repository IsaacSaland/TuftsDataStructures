/*
 *  MetroSim.h
 *  Isaac Saland
 *  2/22/2024
 *
 *
 *  header file for the MetroSim class; also contains the Station struct
 *
 */

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "Passenger.h"
#include "PassengerQueue.h"

// Put any other necessary includes here
#include <vector>
#include <string>

// Put any other structs you need here
class MetroSim
{
    public:
        MetroSim(std::ifstream &input);

        void addPassengerToStation(Passenger pass);
        void addPassengersToTrain();
        void move(std::ostream &output);
        void removePassenger(std::ostream &output);
        void printMetroSim(std::ostream &output);
        void minusStation();
    private:
        struct Station {
            std::string name;
            PassengerQueue passengers;

            Station(std::string newName, PassengerQueue newPassengers) {
                name = newName;
                passengers = newPassengers;
            }
        };
        std::vector<Station> stations;
        std::vector<PassengerQueue> train; //each index represents a car
        int currStation;

        void emptyCar(int car, std::ostream &output);
};

#endif
