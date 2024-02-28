/*
 *  CharArrayList.cpp
 *  Isaac Saland
 *  1/23/2024
 *
 *  COMP 15 HW 1 Cheshire ConCATenation
 *
 *  Implementation of CharArrayList.cpp
 *
 */

#include "CharArrayList.h"
#include <string>
#include <stdexcept>

using namespace std;

/*
 * name:      CharArrayList default constructor
 * purpose:   initialize an empty CharArrayList
 * arguments: none
 * returns:   none
 * effects:   numItems to 0 (also updates capacity and data array)
 */
CharArrayList::CharArrayList() {
    numItems = 0;
    capacity = 0;
    data = nullptr;
}

/*
 * name:      CharArrayList overloaded constructor
 * purpose:   initialize an empty CharArrayList
 * arguments: char c
 * returns:   none
 * effects:   numItems to 1 (also updates capacity and data array)
 */
CharArrayList::CharArrayList(char c) {
    numItems = 1;
    capacity = 1;
    data = new char[capacity];
    data[0] = c;
}

/*
 * name:      CharArrayList overloaded constructor
 * purpose:   initialize an empty CharArrayList
 * arguments: char[] arr, int size
 * returns:   none
 * effects:   creates an array based on the array inputted with its size
 */
CharArrayList::CharArrayList(char arr[], int size) {
    numItems = size;
    capacity = size;
    data = new char[capacity];
    for(int i = 0; i < numItems; i++){
        data[i] = arr[i];
    }
}

/*
 * name:      CharArrayList overloaded constructor
 * purpose:   create a copy of another CharArrayList
 * arguments: const CharArrayList &other
 * returns:   none
 * effects:   creates a copy of the given CharArrayList
 */
CharArrayList::CharArrayList(const CharArrayList &other) {
    numItems = other.numItems;
    capacity = other.capacity;

    data = new char[capacity];    
    for(int i = 0; i < numItems; i++){
        data[i] = other.data[i];
    }

}

/*
 * name: CharArrayList default destructor
 * purpose: destroys this instance of CharArrayList
 * args: none
 * returns: none
 * effects: frees up the memory associated with this instance fo CharArrayList
*/
CharArrayList::~CharArrayList() {
    delete [] data;
}

/*
 * name: operator=
 * purpose: avoid shallow copies when using =
 * args: CharArrayList &other
 * returns: a CharArrayList
 * effects: creates a copy of the inputted ArrayList when using the = operator
*/
CharArrayList& CharArrayList::operator=(const CharArrayList &other) {

    numItems = other.numItems;
    capacity = other.capacity;

    data = new char[capacity];    
    for(int i = 0; i < numItems; i++){
        data[i] = other.data[i];
    }

    return *this;
}

/*
 * name: isEmpty
 * purpose: tells whether the CharArrayList is empty or not
 * args: none
 * returns: a boolean
 * effects: returns true if this CharArrayList is empty, false if not
*/
bool CharArrayList::isEmpty() const {
    return numItems == 0;
}

/*
 * name: clear
 * purpose: clears the CharArrayList
 * args: none
 * returns: none
 * effects: clears out the CharArrayList
*/
void CharArrayList::clear() {
    delete [] data;
    data = nullptr;
    capacity = 0;
    numItems = 0;
}

/*
 * name: size
 * purpose: finds the amount of items in the CharArrayList
 * args: none
 * returns: an int size of the CharArrayList
 * effects: returns the number of items in the CharArrayList
*/
int CharArrayList::size() const {
    return numItems;
}

/*
 * name: first
 * purpose: to give the first char in the arraylist
 * args: none
 * returns: the first char in the arraylist
 * effects: returns the first char in the CharArrayList (or throws an error)
*/
char CharArrayList::first() const {
    if(isEmpty()){
        throw runtime_error("cannot get first of empty ArrayList");
    }
    else return data[0];
}

/*
 * name: last
 * purpose: to give the last char in the arraylist
 * args: none
 * returns: the last char in the arraylist
 * effects: returns the last char in the CharArrayList (or throws an error)
*/
char CharArrayList::last() const {
    if(isEmpty()){
        throw runtime_error("cannot get last of empty ArrayList");
    }
    else return data[numItems - 1];
}

/*
 * name: elementAt
 * purpose: to give the char in the arraylist at a certain index
 * args: int index
 * returns: a char in the CharArrayList
 * effects: returns the char in the CharArrayList at index or throws an error
*/
char CharArrayList::elementAt(int index) const {
    if(index < numItems and index >= 0) return data[index];
    else{
        string str = "index (" + to_string(index);
        str += ") not in range [0.." + to_string(numItems) + ")";
        throw range_error(str);
    }
}

/*
 * name: toString
 * purpose: give the CharArrayList as a string
 * args: none
 * returns: a string of all the chars
 * effects: returns a string containing all the chars in the CharArrayList
*/
string CharArrayList::toString() const {
    string str = "[CharArrayList of size " + to_string(numItems);
    str += " <<";

    for(int i = 0; i < numItems; i++){
        str += data[i];
    }
    return str + ">>]";
}

/*
 * name: toReverseString
 * purpose: give the CharArrayList as a string in reverse
 * args: none
 * returns: a string of all the chars in reverse order
 * effects: returns a (reversed) string containing all the chars
*/
string CharArrayList::toReverseString() const {
    string str = "[CharArrayList of size " + to_string(numItems);
    str += " <<";
    for(int i = numItems - 1; i >= 0; i--){
        str += data[i];
    }
    return str + ">>]";
}

/*
 * name: pushAtBack
 * purpose: add an element to the back of the arraylist
 * args: char c to be added
 * returns: none
 * effects: adds char c to the back of the CharArrayList
*/
void CharArrayList::pushAtBack(char c) {
    insertAt(c, numItems);
}

/*
 * name: pushAtBack
 * purpose: add an element to the front of the arraylist
 * args: char c to be added
 * returns: none
 * effects: adds char c to the front of the CharArrayList
*/
void CharArrayList::pushAtFront(char c) {
    insertAt(c, 0);
}

/*
 * name: insertAt
 * purpose: add an element at a given position in the arraylist
 * args: char c to be added at int index
 * returns: none
 * effects: inserts char c at int index in the CharArrayList
*/
void CharArrayList::insertAt(char c, int index) {
    if(index >= numItems + 1 or index < 0){
        string str = "index (" + to_string(index);
        str += ") not in range [0.." + to_string(numItems) + "]";
        throw range_error(str);
    }
    if(numItems + 1 > capacity) expand();
    for(int i = numItems; i > index; i--){
        data[i] = data[i - 1];
    }
    data[index] = c;
    numItems++;
}

/*
 * name: insertInOrder
 * purpose: add an element to the arraylist in order
 * args: char c to be added
 * returns: none
 * effects: inserts char c in the CharArrayList in order
*/
void CharArrayList::insertInOrder(char c) {
    if(c < data[0]){
        pushAtFront(c);
        return;
    }
    for(int i = 0; i < numItems - 1; i++){
        if(c > data[i] and c <= data[i + 1]){
            insertAt(c, i + 1);
            return;
        }
    }
    pushAtBack(c);
}

/*
 * name: popFromFront
 * purpose: remove first element in the arraylist
 * args: none
 * returns: none
 * effects: removes the first element in CharArrayList
*/
void CharArrayList::popFromFront() {
    if(isEmpty()){
        throw runtime_error("cannot pop from empty ArrayList");
    }
    else removeAt(0);
}

/*
 * name: popFromBack
 * purpose: remove last element in the arraylist
 * args: none
 * returns: none
 * effects: removes the last element in CharArrayList
*/
void CharArrayList::popFromBack() {
    if(isEmpty()){
        throw runtime_error("cannot pop from empty ArrayList");
    }
    else removeAt(numItems - 1);
}

/*
 * name: removeAt
 * purpose: remove element at index
 * args: int index to be removed
 * returns: none
 * effects: removes the element at index
*/
void CharArrayList::removeAt(int index) {
    if (index >= numItems or index < 0){
        string str = "index (" + to_string(index);
        str += ") not in range [0.." + to_string(numItems) + ")";
        throw range_error(str);
    }
    else{
        for(int i = index; i < numItems - 1; i++){
            data[i] = data[i + 1];
        }
        numItems--;
    }
}

/*
 * name: replaceAt
 * purpose: replaces element at index
 * args: int index will be replaced by char c
 * returns: none
 * effects: replaces element at int index with char c
*/
void CharArrayList::replaceAt(char c, int index) {
    if (index >= numItems or index < 0){
        string str = "index (" + to_string(index);
        str += ") not in range [0.." + to_string(numItems) + ")";
        throw range_error(str);
    }
    else data[index] = c;
}

/*
 * name: concatenate
 * purpose: combines this CharArrayList with other
 * args: CharArrayList* other to be combined
 * returns: none
 * effects: adds the elements of other to this
*/
void CharArrayList::concatenate(CharArrayList *other) {
    while(capacity < numItems + other->numItems) expand();

    for(int i = 0; i < other->numItems; i++){
        pushAtBack(other->data[i]);
    }
}

/*
 * name: expand
 * purpose: helper method to ensure enough space for more items in data
 * args: none
 * returns: none
 * effects: allocates more memory for spac in data
*/
void CharArrayList::expand() {
    capacity = capacity * 2 + 2;
    char *temp = new char[capacity];
    for(int i = numItems - 1; i >= 0; i--){
        temp[i] = data[i];
    }
    delete [] data;
    data = temp;
}