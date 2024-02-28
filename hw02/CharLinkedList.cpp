/*
 *  CharLinkedList.cpp
 *  Isaac Saland
 *  2/6/2024
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  implementation of CharLinkedList; names, purposes, args accepted,
 *  return values, and effects of functions are listed
 *
 */

#include "CharLinkedList.h"
#include <string>
#include <stdexcept>

/*
 * name:      CharLinkedList default constructor
 * purpose:   initialize an empty CharLinkedList
 * arguments: none
 * returns:   none
 * effects:   numNodes = 0, front and back = nullptr
 */
CharLinkedList::CharLinkedList() {
    numNodes = 0;
    front = nullptr;
    back = nullptr;
}

/*
 * name:      CharLinkedList overloaded constructor
 * purpose:   initialize a CharLinkedList with 1 node
 * arguments: char c
 * returns:   none
 * effects:   numNodes = 1, front and back = new Node*s
 */
CharLinkedList::CharLinkedList(char c) {
    front = nullptr;
    back = nullptr;
    pushAtFront(c);
}

/*
 * name:      CharLinkedList overloaded constructor
 * purpose:   initialize a CharLinkedList with numNodes equal to size
 * arguments: char arr[], int size
 * returns:   none
 * effects:   numNodes = size, front and back point to first and last
 * note: constructor fails if int size is incorrect
 */
CharLinkedList::CharLinkedList(char arr[], int size) {
    numNodes = size;
    front = nullptr;
    back = nullptr;
    for(int i = size - 1; i >= 0; i--) {
        pushAtFront(arr[i]);
    }
}

/*
 * name:      CharLinkedList overloaded constructor
 * purpose:   initialize a copy CharLinkedList of other
 * arguments: CharLinkedList &other
 * returns:   none
 * effects:   cycles through other and creates an equivalent LinkedList
 */
CharLinkedList::CharLinkedList(const CharLinkedList &other) {
    numNodes = 0;
    front = nullptr;
    back = nullptr;
    Node *curr = other.back;
    do {
        pushAtFront(curr->info);
        curr = curr->before;
    } while(curr!= nullptr);
}

/*
 * name: operator=
 * purpose: avoid shallow copies when using =
 * args: CharLinkedList &other
 * returns: a CharLinkedList
 * effects: creates copy of the inputted linked list when using the = operator
*/
CharLinkedList& CharLinkedList::operator=(const CharLinkedList &other) {
    if(this == (&other)) return *this;

    numNodes = 0;
    front = nullptr;
    back = nullptr;
    Node *curr = other.back;
    do {
        pushAtFront(curr->info);
        curr = curr->before;
    } while(curr!= nullptr);
    
    return *this;
}

/*
 * name: CharLinkedList destructor
 * purpose: delete memory associated with this
 * args: none
 * returns: none
 * effects: deletes all nodes at all pointers within this CharLinkedList
*/
CharLinkedList::~CharLinkedList() {
    del(back);
}

/*
 * name: del
 * purpose: deletes nodes (helper method for the destructor)
 * args: Node *currNode
 * returns: none
 * effects: recursively deletes all nodes before currNode
 * note: private function
*/
void CharLinkedList::del(Node *currNode) {
    if(currNode == front) {
        delete front;
        return;
    }
    Node *n = currNode->before;
    delete currNode;
    del(n);
}

/*
 * name: pushAtFront
 * purpose: add a new node to the front of the linkedlist
 * args: char c
 * returns: none
 * effects: sets front->before to a new node with info c and makes it front
*/
void CharLinkedList::pushAtFront(char c) {
    if(front != nullptr) { 
        Node* n = new Node;
        n->info = c;
        n->after = front;
        n->before = nullptr;
        front->before = n;
        front = n;
        numNodes++;
    }
    else {
        numNodes = 1;
        front = new Node;
        front->info = c;
        front->before = nullptr;
        front->after = nullptr;
        back = front;
    }
}

/*
 * name: isEmpty
 * purpose: checks if numNodes == 0
 * args: none
 * returns: bool if numNodes == 0
 * effects: returns numNodes == 0
*/
bool CharLinkedList::isEmpty() const {
    return numNodes == 0;
}

/*
 * name: toString
 * purpose: return a string displaying the size and contents of the list
 * args: none
 * returns: string with info of the charlinkedlist
 * effects: loops through the linkedlist and adds its size + contents to str
*/
std::string CharLinkedList::toString() const {
    std::string str = "[CharLinkedList of size ";
    str = str + std::to_string(numNodes) + " <<";

    Node *curr = front;
    for(int i = 0; i < numNodes; i++){
        str += curr->info;
        curr = curr->after;
    }

    return str + ">>]";
}

/*
 * name: toReverseString
 * purpose: return a string displaying the size + content of the list backwards
 * args: none
 * returns: string with info of the charlinkedlist backwards
 * effects: loops through the linkedlist and adds its size + contents to str
*/
std::string CharLinkedList::toReverseString() const {
    std::string str = "[CharLinkedList of size ";
    str += std::to_string(numNodes) + " <<";

    Node *curr = back;

    for(int i = 0; i < numNodes; i++) {
        str += curr->info;
        curr = curr->before;
    }

    return str + ">>]";
}

/*
 * name: removeAt
 * purpose: deletes the node at the given index and relinks surrounding nodes
 * args: int index
 * returns: none
 * effects: loops until it finds the correct index, deletes the node,
 *          and relinks the surrounding nodes. Throws errors if linkedlist is
 *          empty or index is out of bounds. Calls removePop for the first
 *          and last indexes
*/
void CharLinkedList::removeAt(int index) {
    if(isEmpty()) {
        std::string str = "cannot pop from empty LinkedList";
        throw std::runtime_error(str);
    }
    if(index >= numNodes or index < 0) {
        std::string str = "index (" + std::to_string(index);
        str = str + ") not in range [0.." + std::to_string(numNodes) + ")";
        throw std::range_error(str);
    }
    if(numNodes == 1){
        delete front;
        front = nullptr;
        back = nullptr;
        numNodes--;
        return;
    }
    if(index == 0 or index == numNodes - 1) {
        removePop(index);
        return;
    }
    Node *rem = front;
    for(int i = 0; i < index; i++) {
        rem = rem->after;
    }
    rem->before->after = rem->after;
    rem->after->before = rem->before;
    delete rem;
    numNodes--;
}

/*
 * name: removePop
 * purpose: helper method for removeAt for the first tand last indexes
 * args: index to remove
 * returns: none
 * effects: sets front/back to the second/second to last node, then deletes
 * notes: private function
*/
void CharLinkedList::removePop(int index) {
    //for if index is 0
    if(index == 0) {
        Node *temp = front;
        front = front->after;
        front->before = nullptr;
        delete temp;
        numNodes--;
        return;
    }
    //for if index is numNodes - 1
    if(index == numNodes - 1){
        Node *temp = back;
        back = back->before;
        back->after = nullptr;
        delete temp;
        numNodes--;
        return;
    }
}

/*
 * name: popFromFront
 * purpose: removes first element of the linkedlist
 * args: none
 * returns: none
 * effects: calles removeAt for the first index
*/
void CharLinkedList::popFromFront() {
    removeAt(0);
}

/*
 * name: popFromBack
 * purpose: removes last element of the linkedlist
 * args: none
 * returns: none
 * effects: calles removeAt for the last index
*/
void CharLinkedList::popFromBack() {
    removeAt(numNodes - 1);
}

/*
 * name: clear
 * purpose: turns the linkedlist empty
 * args: none
 * returns: none
 * effects: runs popFromFront numNodes times
*/
void CharLinkedList::clear() {
    int temp = numNodes;
    for(int i = 0; i < temp; i++) {
        popFromFront();
    }
}

/*
 * name: insertAt
 * purpose: inserts a new node with info c at index
 * args: char c, int index
 * returns: none
 * effects: if index is the front or the back, runs a push function
 *          otherwise iterates through the linkedlist and inserts a new node
 *          throws a range error if index is out of bounds
*/
void CharLinkedList::insertAt(char c, int index) {
    if(index >= numNodes or index < 0) {
        std::string str = "index (" + std::to_string(index);
        str = str + ") not in range [0.." + std::to_string(numNodes) + "]";
        throw std::range_error(str);
    }
    if(index == 0) {
        pushAtFront(c);
    }
    else if(index == numNodes){
        pushAtBack(c);
    }
    else {
        Node *add = front;
        Node *newNode = new Node;
        newNode->info = c;
        for(int i = 0; i < index; i++) {
            add = add->after;
        }
        add->before->after = newNode;
        newNode->after = add;
        newNode->before = add->before;
        add->before = newNode;
        numNodes++;
    }
}

/*
 * name: pushAtBack
 * purpose: add a new node to the back of the linkedlist
 * args: char c
 * returns: none
 * effects: sets back->after to a new node with info c and makes it back
*/
void CharLinkedList::pushAtBack(char c) {
    if(numNodes != 0) {
        Node* n = new Node;
        n->info = c;
        n->after = nullptr;
        n->before = back;
        back->after = n;
        back = n;
        numNodes++;
    }
    else {
        pushAtFront(c);
    }
}

/*
 * name: insertInOrder
 * purpose: add a new node to the linkedlist in the correct ASCII order
 * args: char c
 * returns: none
 * effects: inserts a new node with info c at the first correct place
*/
void CharLinkedList::insertInOrder(char c) {
    if(isEmpty()) {
        pushAtFront(c);
        return;
    }
    Node *curr = front;
    for(int i = 0; i < numNodes; i++) {
        if(curr->info >= c) {
            insertAt(c, i);
            return;
        }
        curr = curr->after;
   }
   pushAtBack(c);
}

/*
 * name: replaceAt
 * purpose: replace the info of the node at index
 * args: char c, int index
 * returns: none
 * effects: replaces the info of the node at index with c
 * notes: uses the findNode helper function
*/
void CharLinkedList::replaceAt(char c, int index) {
    if(index >= numNodes or index < 0) {
        std::string str = "index (" + std::to_string(index);
        str = str + ") not in range [0.." + std::to_string(numNodes) + ")";
        throw std::range_error(str);
    }
    Node *replace = findNode(front, index);
    replace->info = c;
}

/*
 * name: size
 * purpose: returns the # of nodes in the linkedlist
 * args: none
 * returns: int numNodes
 * effects: returns numNodes
*/
int CharLinkedList::size() const {
    return numNodes;
}

/*
 * name: first
 * purpose: returns the first char in the linkedlist
 * args: none
 * returns: the info of front
 * effects: returns front->info
*/
char CharLinkedList::first() const {
    if(isEmpty()) {
        throw std::runtime_error("cannot get first of empty LinkedList");
    }
    return front->info;
}

/*
 * name: last
 * purpose: returns the last char in the linkedlist
 * args: none
 * returns: the info of back
 * effects: returns back->info
*/
char CharLinkedList::last() const {
    if(isEmpty()) {
        throw std::runtime_error("cannot get last of empty LinkedList");
    }
    return back->info;
}

/*
 * name: concatenate
 * purpose: adds the elements of other to the end of this
 * args: CharLinkedList &other
 * returns: none
 * effects: runs pushAtBack for every element in other
*/
void CharLinkedList::concatenate(CharLinkedList *other) {
    int num = other->size();
    for(int i = 0; i < num; i++) {
        pushAtBack(other->elementAt(i));
    }
}

/*
 * name: elementAt
 * purpose: finds the char at the given index in the linkedlist
 * args: int index
 * returns: the char at the given index in the linkedlist
 * effects: uses findNode to find the node at index, then returns its info
 *          but throws a range error if index is out of bounds
*/
char CharLinkedList::elementAt(int index) const {
    if(index == 0) {
        return first();
    }
    if(index == numNodes - 1) {
        return last();
    }
    if(index >= numNodes or index < 0) {
        std::string str = "index (" + std::to_string(index);
        str = str + ") not in range [0.." + std::to_string(numNodes) + ")";
        throw std::range_error(str);
    }
    Node *node = findNode(front, index);
    return node->info;
}

/*
 * name: findNode
 * purpose: finds the node at a given index (helper method for elementAt)
 * args: Node *currNode, int number of nodes away
 * returns: the node at the initially given index
 * effects: recursively returns itself with the next node (and one less node
 *          away) until away == 0, where it returns the node it is at
 * note: private function
*/
CharLinkedList::Node* CharLinkedList::findNode(Node *currNode, int away) const {
    if(away == 0) return currNode;
    else {
        return findNode(currNode->after, away - 1);
    }
}