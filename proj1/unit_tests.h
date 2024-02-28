/*
 *  unit_tests.h
 *  Isaac Saland
 *  2/22/2024
 *
 *
 *  testing of various functions of each class of the MetroSim project
 *
 */

#include "Passenger.h"
#include "PassengerQueue.h"
#include <cassert>
#include <ostream>
#include <sstream>
#include <cassert>
#include <string>

//tests the Print function of Passenger
void testPassPrint() {
    Passenger pass = {12345, 2, 4};
    std::stringstream output;
    pass.print(output);
    assert(output.str() == "[12345, 2->4]");
}

//tests the front() function of PassengerQueue
void testFront() {
    Passenger p = {1, 1, 2};
    Passenger p1 = {2, 1, 3};
    PassengerQueue queue;

    queue.enqueue(p);
    queue.enqueue(p1);

    Passenger Pnew = queue.front();

    assert(Pnew.id == p.id);
    assert(Pnew.to == p.to);
    assert(Pnew.from == p.from);
}

//tests the front() function of empty PassengerQueue
void testFrontFail() {
    PassengerQueue queue;

    std::string em = "";
    bool thrown = false;

    try{
        queue.front();
    }
    catch(const std::runtime_error &e){
        thrown = true;
        em = e.what();
    }
    assert(thrown);
    assert(em == "cannot find front of empty queue");
}

//tests the print() function of PassengerQueue
void testPrintQueue() {
    PassengerQueue queue;
    std::stringstream output;

    queue.print(output);

    assert(output.str() == "");

    Passenger p = {1, 1, 2};
    Passenger p1 = {2, 1, 3};

    queue.enqueue(p);
    queue.enqueue(p1);

    queue.print(output);

    assert(output.str() == "[1, 1->2][2, 1->3]");
}

//tests the Enqueue() function of PassengerQueue
void testEnqueue() {
    PassengerQueue queue;
    std::stringstream output;

    queue.print(output);

    assert(output.str() == "");

    Passenger p = {1, 1, 2};
    Passenger p1 = {2, 1, 3};

    queue.enqueue(p);
    queue.enqueue(p1);

    queue.print(output);

    assert(output.str() == "[1, 1->2][2, 1->3]");
    //This is the same code as testPrintQueue
    //but it is much easier to test both at the same time
}

//tests the dequeue() function of PassengerQueue
void testDequeue() {
    PassengerQueue queue;
    std::stringstream output;

    queue.print(output);

    assert(output.str() == "");

    queue.dequeue(); //should do nothing

    Passenger p = {1, 1, 2};
    Passenger p1 = {2, 1, 3};

    queue.enqueue(p);
    queue.enqueue(p1);

    queue.print(output);

    assert(output.str() == "[1, 1->2][2, 1->3]");

    output.clear();

    queue.dequeue();

    std::stringstream other;
    queue.print(other);

    assert(other.str() == "[2, 1->3]");
}

//tests the size() function of PassengerQueue
void testSize() {
    PassengerQueue queue;

    assert(queue.size() == 0);

    Passenger p = {1, 1, 2};
    Passenger p1 = {2, 1, 3};

    queue.enqueue(p);
    queue.enqueue(p1);

    assert(queue.size() == 2);

    queue.dequeue();

    assert(queue.size() == 1);
}