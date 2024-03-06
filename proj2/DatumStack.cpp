/*
 *  DatumStack.cpp
 *  Isaac Saland
 *  2/25/2024
 *
 *
 *  implementation of the DatumStack class
 *
 */

#include "DatumStack.h"
#include "Datum.h"
#include <vector>
#include <stdexcept>
#include <string>

/*
 * name: constructor
 * purpose: default constructor for DatumStack
 * args: none
 * returns: none
*/
DatumStack::DatumStack() {
    //nothing happens
}

/*
 * name: overloaded constructor
 * purpose: overloaded constructor for DatumStack
 * args: Datum arr[], int size
 * returns: none
*/
DatumStack::DatumStack(Datum arr[], int size) {
    for(int i = 0; i < size; i++) push(arr[i]);
}

/*
 * name: isEmpty
 * purpose: tells if this DatumStack is empty
 * args: none
 * returns: true if DatumStack is empty, false if not
*/
bool DatumStack::isEmpty() const {
    return data.empty();
}

/*
 * name: clear
 * purpose: clears out all elements of this DatumStack
 * args: none
 * returns: none
*/
void DatumStack::clear() {
    while(data.size() > 0) pop();
}

/*
 * name: size
 * purpose: returns the size of the stack
 * args: none
 * returns: the size of the stack
*/
int DatumStack::size() const {
    return data.size();
}

/*
 * name: top
 * purpose: returns the first Datum of the stack
 * args: none
 * returns: the first Datum
 * note: throws runtime_error if empty
 */
Datum DatumStack::top() const {
    if(isEmpty()) throw std::runtime_error("empty_stack");
    return data[data.size() - 1];
}

/*
 * name: pop
 * purpose: pops the first Datum of the stack
 * args: none
 * returns: none
 * note: throws runtime_error if empty
 */
void DatumStack::pop() {
    if(isEmpty()) throw std::runtime_error("empty_stack");
    data.pop_back();
}

/*
 * name: push
 * purpose: adds a Datum to the top of the stack
 * args: Datum &item
 * returns: none
*/
void DatumStack::push(const Datum &item) {
    data.push_back(item);
}