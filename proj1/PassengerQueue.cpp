/*
 *  PassengerQueue.cpp
 *  Isaac Saland
 *  2/22/2024
 *
 *
 *  implementation of the PassengerQueue class
 *
 */

#include "PassengerQueue.h"
#include <ostream>
#include <vector>
#include <stdexcept>

/*
 * name: front
 * purpose: returns the first Passenger of the queue
 * args: none
 * returns: the first passenger
 */
Passenger PassengerQueue::front() {
    if(not line.empty()) {
        return line[0];
    }
    else {
        throw std::runtime_error("cannot find front of empty queue");
    }
}

/*
 * name: dequeue
 * purpose: removes the first element of the queue (or does nothing if empty)
 * args: none
 * returns: none
*/
void PassengerQueue::dequeue() {
    //does nothing if the queue is empty
    if(not line.empty()) {
        line.erase(line.begin());
    }
}

/*
 * name: dequeue
 * purpose: removes the first element of the queue (or does nothing if empty)
 * args: none
 * returns: none
*/
void PassengerQueue::enqueue(const Passenger &passenger) {
    line.push_back(passenger);
}

/*
 * name: size
 * purpose: returns the size of the queue
 * args: none
 * returns: the size of the queue
*/
int PassengerQueue::size() {
    return line.size();
}

/*
 * name: print
 * purpose: prints all the Passengers in this
 * args: ostream &output
 * returns: none
*/
void PassengerQueue::print(std::ostream &output) {
    for(int i = 0; i < size(); i++) {
        line[i].print(output);
    }
}