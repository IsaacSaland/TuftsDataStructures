/*
 *  Passenger.cpp
 *  Isaac Saland
 *  2/22/2024
 *
 *
 *  implementation of the function of Passenger
 *
 */

#include <iostream>
#include <string>
#include "Passenger.h"

/*
 * name: print
 * purpose: prints the contents of Passenger to output
 * args: ostream &output
 * returns: none
 */
void Passenger::print(std::ostream &output)
{
        output << "[" << id << ", " << from << "->" << to << "]";
}
