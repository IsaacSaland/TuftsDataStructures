/*
 *  PassengerQueue.h
 *  Isaac Saland
 *  2/22/2024
 *
 *
 *  interface of PassengerQueue; contains declarations of all public/private
 *  functions/variables
 *
 */

#include "Passenger.h"
#include <ostream>
#include <vector>

class PassengerQueue {
    public:
        Passenger front();
        void dequeue();
        void enqueue(const Passenger &passenger);
        int size();
        void print(std::ostream &output);
    private:
        std::vector<Passenger> line;
};