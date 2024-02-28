/*
 *  unit_tests.h
 *  Isaac Saland
 *  2/6/2024
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to linked up in Fur
 *
 *  Testing each aspect of CharLinkedList; each method has its own test,
 *  with extra tests for edge cases/failures and a tester for the constructors
 *
 */

#include "CharLinkedList.h"
#include <cassert>
#include <iostream>

using namespace std;

//tests the default constructor
void testDefaultConstructor() {
    CharLinkedList test = CharLinkedList();

    assert(test.isEmpty());
    assert(test.toString() == "[CharLinkedList of size 0 <<>>]");
}

//tests all the other constructors and the toString() function
void testConstructors() {
    CharLinkedList single('f');
    char arr[] = {'a', 'b', 'c'};
    CharLinkedList multi(arr, 3);
    CharLinkedList copy(multi);

    assert(single.toString() == "[CharLinkedList of size 1 <<f>>]");
    assert(multi.toString() == "[CharLinkedList of size 3 <<abc>>]");
    assert(copy.toString() == multi.toString());
}

//tests the = operator and the toReverseString function
void testOperatorEQ() {
    char arr[] = {'a', 'b', 'c'};
    CharLinkedList base(arr, 3);
    CharLinkedList copy;
    copy = base;
    assert(&copy != &base);
    assert(copy.toReverseString() == base.toReverseString());
    copy = copy;
    assert(copy.toReverseString() == base.toReverseString());

    assert(base.toReverseString() == "[CharLinkedList of size 3 <<cba>>]");
}

//tests the toReverseString function
void testReverseString() {
    char arr[] = {'z', 'b', 'd', 'f'};
    CharLinkedList test(arr, 4);

    assert(test.toReverseString() == "[CharLinkedList of size 4 <<fdbz>>]");
}

//tests the removeAt, popFromBack, and popFromFront functions
void testRemovePop() {
    char arr[] = {'i', 's', 'a', 'a', 'c'};
    CharLinkedList test(arr, 5);

    assert(test.toString() == "[CharLinkedList of size 5 <<isaac>>]");

    test.removeAt(1);
    //should be iaac

    assert(test.toString() == "[CharLinkedList of size 4 <<iaac>>]");

    test.popFromFront();
    //should be aac

    assert(test.toString() == "[CharLinkedList of size 3 <<aac>>]");

    test.popFromBack();
    //should be aa

    assert(test.toString() == "[CharLinkedList of size 2 <<aa>>]");

    test.popFromFront();
    //should be a
    test.popFromFront();
    //should be empty
    assert(test.toString() == "[CharLinkedList of size 0 <<>>]");

    test.pushAtFront('a');
    //should be a
    test.popFromBack();
    //should be empty
    assert(test.toString() == "[CharLinkedList of size 0 <<>>]");
}

//tests removeAt in the case that it fails
void testRemoveFail() {
    char arr[] = {'i', 's', 'a', 'a', 'c'};
    CharLinkedList test(arr, 5);

    std::string em = "";
    bool thrown = false;

    try{
        test.removeAt(5);
    }
    catch(const std::range_error &e){
        thrown = true;
        em = e.what();
    }
    assert(thrown);
    assert(em == "index (5) not in range [0..5)");
}

//tests the clear method
void testClear() {
    char arr[] = {'i', 's', 'a', 'a', 'c'};
    CharLinkedList test(arr, 5);
    
    assert(test.toString() == "[CharLinkedList of size 5 <<isaac>>]");

    test.clear();

    assert(test.toString() == "[CharLinkedList of size 0 <<>>]");
    assert(test.isEmpty());
}

//tests the insertAt method
void testInsert() {
    char arr[] = {'t', 'e', 's', 't'};
    CharLinkedList test(arr, 4);

    assert(test.toString() == "[CharLinkedList of size 4 <<test>>]");

    test.insertAt('a', 2);
    //should now be teast

    assert(test.toString() == "[CharLinkedList of size 5 <<teast>>]");

    test.insertAt('o', 3);
    //should now be teaost

    assert(test.toString() == "[CharLinkedList of size 6 <<teaost>>]");
}

//tests the pushAtFront and pushAtBack functions
void testPush() {
    char arr[] = {'p', 'u', 's', 'h'};
    CharLinkedList test(arr, 4);

    assert(test.toString() == "[CharLinkedList of size 4 <<push>>]");

    test.pushAtBack('z');
    //should now be pushz

    assert(test.toString() == "[CharLinkedList of size 5 <<pushz>>]");

    test.pushAtFront('a');
    //should now be apushz

    assert(test.toString() == "[CharLinkedList of size 6 <<apushz>>]");
}

//tests the insertAt function for an out of bounds index
void testInsertFail() {
    char arr[] = {'i', 's', 'a', 'a', 'c'};
    CharLinkedList test(arr, 5);

    std::string em = "";
    bool thrown = false;

    try{
        test.insertAt('z', 6);
    }
    catch(const std::range_error &e){
        thrown = true;
        em = e.what();
    }
    assert(thrown);
    assert(em == "index (6) not in range [0..5]");

    thrown = false;
    em = "";

    try{
        test.insertAt('z', -1);
    }
    catch(const std::range_error &e){
        thrown = true;
        em = e.what();
    }
    assert(thrown);
    assert(em == "index (-1) not in range [0..5]");
}

//tests the insertInOrder function
void testInsertOrder() {
    char arr[] = {'b', 'b', 'c', 'd'};
    CharLinkedList test(arr, 4);

    assert(test.toString() == "[CharLinkedList of size 4 <<bbcd>>]");

    test.insertInOrder('a');
    //should now be abbcd
    assert(test.toString() == "[CharLinkedList of size 5 <<abbcd>>]");

    test.insertInOrder('f');
    //should now be abbcdf
    assert(test.toString() == "[CharLinkedList of size 6 <<abbcdf>>]");

    test.insertInOrder('e');
    //should now be abbcdef
    assert(test.toString() == "[CharLinkedList of size 7 <<abbcdef>>]");

    test.insertInOrder('a');
    //should now be aabbcdef
    assert(test.toString() == "[CharLinkedList of size 8 <<aabbcdef>>]");
    
    test.insertInOrder('f');
    //should now be aabbcdeff
    assert(test.toString() == "[CharLinkedList of size 9 <<aabbcdeff>>]");
}

void testInsertOrderEmpty() {
    CharLinkedList empty = CharLinkedList();

    empty.insertInOrder('w');
    //should now be w

    assert(empty.toReverseString() == "[CharLinkedList of size 1 <<w>>]");
}

//tests the replaceAt function
void testReplace() {
    char arr[] = {'a', 'a', 'a'};
    CharLinkedList test(arr, 3);

    assert(test.toString() == "[CharLinkedList of size 3 <<aaa>>]");

    test.replaceAt('b', 1);
    //should now be aba

    assert(test.toString() == "[CharLinkedList of size 3 <<aba>>]");

    test.replaceAt('c', 0);
    //should now be cba
    
    assert(test.toString() == "[CharLinkedList of size 3 <<cba>>]");

    test.replaceAt('z', 2);
    //should now be cbz

    assert(test.toString() == "[CharLinkedList of size 3 <<cbz>>]");
}

//tests the replaceAt function with an out of bounds index
void testReplaceFail() {
    char arr[] = {'i', 's', 'a', 'a', 'c'};
    CharLinkedList test(arr, 5);

    std::string em = "";
    bool thrown = false;

    try{
        test.replaceAt('z', 6);
    }
    catch(const std::range_error &e){
        thrown = true;
        em = e.what();
    }
    assert(thrown);
    assert(em == "index (6) not in range [0..5)");

    thrown = false;
    em = "";

    try{
        test.replaceAt('z', -1);
    }
    catch(const std::range_error &e){
        thrown = true;
        em = e.what();
    }
    assert(thrown);
    assert(em == "index (-1) not in range [0..5)");
}

//tests the first and last functions
void testFirstLast() {
    char arr[] {'h', 'e', 'l', 'l', 'o'};
    CharLinkedList test(arr, 5);

    assert(test.first() == 'h');
    assert(test.last() == 'o');
}

//tests the concatenate function
void testConcat() {
    char arr[] = {'a', 'd', 'd'};
    CharLinkedList base(arr, 3);
    CharLinkedList empty = CharLinkedList();

    assert(base.toString() == "[CharLinkedList of size 3 <<add>>]");
    assert(empty.toString() == "[CharLinkedList of size 0 <<>>]");

    base.concatenate(&empty);
    //should still be add

    assert(base.toString() == "[CharLinkedList of size 3 <<add>>]");

    empty.pushAtBack('z');
    empty.pushAtFront('i');
    //should now be iz

    assert(empty.toString() == "[CharLinkedList of size 2 <<iz>>]");

    base.concatenate(&empty);
    //should now be addiz

    assert(base.toString() == "[CharLinkedList of size 5 <<addiz>>]");

    base.concatenate(&base);
    //should now be addizaddiz

    assert(base.toString() == "[CharLinkedList of size 10 <<addizaddiz>>]");
}

//tests the elementAt function
void testElementAt() {
    char arr[] = {'a', 'b', 'c', 'd', 'e'};
    CharLinkedList test(arr, 5);

    assert(test.elementAt(2) == 'c');
    assert(test.elementAt(0) == 'a');
    assert(test.elementAt(test.size() - 1) == 'e');
}

//tests the elementAt function for an out of bounds index
void testElementAtFail() {
    char arr[] = {'a', 'b', 'c', 'd', 'e'};
    CharLinkedList test(arr, 5);
    bool thrown = false;
    std::string em = "";

    try{
        test.elementAt(5);
    }
    catch(const std::range_error &e){
        thrown = true;
        em = e.what();
    }
    assert(thrown);
    assert(em == "index (5) not in range [0..5)");

    thrown = false;
    em = "";

    try {
        test.elementAt(-1);
    }
    catch(const std::range_error &e) {
        thrown = true;
        em = e.what();
    }
    assert(thrown);
    assert(em == "index (-1) not in range [0..5)");
}

//tests the edge cases for remove and pop of an empty list
void testRemoveEmpty() {
    CharLinkedList empty = CharLinkedList();
    bool thrown = false;
    std::string em = "";

    try {
        empty.removeAt(0);
    }
    catch(const std::runtime_error &e) {
        thrown = true;
        em = e.what();
    }

    assert(thrown);
    assert(em == "cannot pop from empty LinkedList");
}

//tests the edge cases for remove and pop of an empty list
void testPopEmpty() {
    CharLinkedList empty = CharLinkedList();
    bool thrown = false;
    std::string em = "";

    try {
        empty.popFromFront();
    }
    catch(const std::runtime_error &e) {
        thrown = true;
        em = e.what();
    }

    assert(thrown);
    assert(em == "cannot pop from empty LinkedList");

    thrown = false;
    em = "";
    try {
        empty.popFromBack();
    }
    catch(const std::runtime_error &e) {
        thrown = true;
        em = e.what();
    }

    assert(thrown);
    assert(em == "cannot pop from empty LinkedList");
}

//tests the first and last functions on an empty linkedlist
void testFirstLastError() {
    CharLinkedList empty = CharLinkedList();
    bool thrown = false;
    std::string em = "";

    try {
        empty.first();
    }
    catch(const std::runtime_error &e) {
        thrown = true;
        em = e.what();
    }

    assert(thrown);
    assert(em == "cannot get first of empty LinkedList");

    thrown = false;
    em = "";
    try {
        empty.last();
    }
    catch(const std::runtime_error &e) {
        thrown = true;
        em = e.what();
    }

    assert(thrown);
    assert(em == "cannot get last of empty LinkedList");
}