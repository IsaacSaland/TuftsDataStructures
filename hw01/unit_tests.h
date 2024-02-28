/*
 * unit_tests.h
 *
 * CS 15 homework 1
 * by Tyler Calabrese, January 2021
 *
 * edited by: Milod Kazerounian, January 2022
 *
 * Uses Matt Russell's unit_test framework to test the CharArrayList class.
 *
 * Instructions for using testing framework can be found at in CS 15's lab
 * 1 -- both in the spec and in the provided ArrayList_tests.h and Makefile.
 * More in-depth information for those who are curious as to how it works can
 * be found at http://www.github.com/mattrussell2/unit_test.
 */
#include "CharArrayList.h"
#include <cassert>
#include <iostream>

using namespace std;

/********************************************************************\
*                       CHAR ARRAY LIST TESTS                        *
\********************************************************************/

/* To give an example of thorough testing, we are providing
 * the unit tests below which test the insertAt function. Notice: we have
 * tried to consider all of the different cases insertAt may be
 * called in, and we test insertAt in conjunction with other functions!
 *
 * You should emulate this approach for all functions you define.
 */


// Tests correct insertion into an empty AL.
// Afterwards, size should be 1 and element at index 0
// should be the element we inserted.
void insertAt_empty_correct() { 

    CharArrayList test_list;
    test_list.insertAt('a', 0);
    assert(test_list.size() == 1);
    assert(test_list.elementAt(0) == 'a');

}

// Tests incorrect insertion into an empty AL.
// Attempts to call insertAt for index larger than 0.
// This should result in an std::range_error being raised.
void insertAt_empty_incorrect() {

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharArrayList test_list;
    try {
    // insertAt for out-of-range index
    test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
    // if insertAt is correctly implemented, a range_error will be thrown,
    // and we will end up here
    range_error_thrown = true;
    error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..0]");
    
}

// Tests correct insertAt for front of 1-element list.
void insertAt_front_singleton_list() {
    
    // initialize 1-element list
    CharArrayList test_list('a');

    // insert at front
    test_list.insertAt('b', 0);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'b');
    assert(test_list.elementAt(1) == 'a');
    
}

// Tests correct insertAt for back of 1-element list.
void insertAt_back_singleton_list() {
    
    // initialize 1-element list
    CharArrayList test_list('a');

    // insert at back
    test_list.insertAt('b', 1);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    
}

// Tests calling insertAt for a large number of elements.
// Not only does this test insertAt, it also checks that
// array expansion works correctly.
void insertAt_many_elements() {
    
    CharArrayList test_list;

    // insert 1000 elements
    for (int i = 0; i < 1000; i++) {
        // always insert at the back of the list
        test_list.insertAt('a', i);
    }

    assert(test_list.size() == 1000);

    for (int i = 0; i < 1000; i++) {
        assert(test_list.elementAt(i) == 'a');
    }
    
}

// Tests insertion into front of a larger list
void insertAt_front_large_list() {
    char test_arr[9] = { 'a', 'b', 'c', 'z', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 9);

    test_list.insertAt('y', 0);

    assert(test_list.size() == 10);
    assert(test_list.elementAt(0) == 'y');
    assert(test_list.toString()== "[CharArrayList of size 10 <<yabczdefgh>>]");

}

// Tests insertion into the back of a larger list
void insertAt_back_large_list() {

    char test_arr[10] = { 'y', 'a', 'b', 'c', 'z', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 10);  

    test_list.insertAt('x', 10);

    assert(test_list.size() == 11);
    assert(test_list.elementAt(10) == 'x');
    assert(test_list.toString() == 
    "[CharArrayList of size 11 <<yabczdefghx>>]"); 

}

// Tests insertion into the middle of a larger list
void insertAt_middle_large_list() {
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);

    test_list.insertAt('z', 3);

    assert(test_list.size() == 9);
    assert(test_list.elementAt(3) == 'z');
    assert(test_list.toString() == "[CharArrayList of size 9 <<abczdefgh>>]");

}

// Tests out-of-range insertion for a non-empty list.
void insertAt_nonempty_incorrect() {
   
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    try {
        test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..8]");
    
}

//tests the clear() and isEmpty() functions
void testClear() {
    char arr[] = {'a', 'b', 'c'};
    CharArrayList test(arr, 3);
    assert(not test.isEmpty());

    test.clear();
    assert(test.isEmpty());
}

//tests the first(), last(), popFront(), and popBack() functions
void testFirstLast() {
    char arr[] = {'a', 'b', 'c', 'd'};
    CharArrayList test(arr, 4);
    assert(test.first() == 'a');
    assert(test.last() == 'd');
    test.popFromBack();
    test.popFromFront();
    //test should now have {'b', 'c'}
    assert(test.first() == 'b');
    assert(test.last() == 'c');
    //test edge case of an empty CharArrayList
    // var to track whether range_error is thrown
    bool runtime_error_thrown = false;
    //var to track any error messages raised
    std::string error_message = "";
    CharArrayList empty = CharArrayList();
    try{
        empty.first();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "cannot get first of empty ArrayList");

    runtime_error_thrown = false;
    try{
        empty.last();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "cannot get last of empty ArrayList");
}

//tests the popFromBack() and popFromFront() methods on an empty ArrayList
void testPop() {
    // var to track whether range_error is thrown
    bool runtime_error_thrown = false;
    //var to track any error messages raised
    std::string error_message = "";
    CharArrayList empty = CharArrayList();

    runtime_error_thrown = false;
    try{
        empty.popFromBack();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot pop from empty ArrayList");

    runtime_error_thrown = false;
    try{
        empty.popFromFront();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot pop from empty ArrayList");
}

//tests the removeAt() method in the case of a pass
void removeTest() {
    char arr[] = {'i', 's', 'a', 'a', 'c'};
    CharArrayList  test(arr, 5);

    assert(test.toString() == "[CharArrayList of size 5 <<isaac>>]");

    test.removeAt(3);
    //should become isac

    assert(test.toString() == "[CharArrayList of size 4 <<isac>>]");
}

//tests the removeAt() method in the case of a fail
void removeTestFail() {
    char arr[] = {'i', 's', 'a', 'a', 'c'};
    CharArrayList  test(arr, 5);
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

//tests the replaceAt() method for both pass and fail
void replaceTest() {
    char arr[] = {'c', 'o', 'd', 'e'};
    CharArrayList test(arr, 4);

    assert(test.toString() == "[CharArrayList of size 4 <<code>>]");

    test.replaceAt('m', 0);
    //should become mode

    assert(test.toString() == "[CharArrayList of size 4 <<mode>>]");

    std::string em = "";
    bool thrown = false;

    try{
        test.replaceAt('m', 5);
    }
    catch(const std::range_error &e){
        thrown = true;
        em = e.what();
    }
    assert(thrown);
    assert(em == "index (5) not in range [0..4)");
}

//tests the concatenate() method
void concatTest() {
    char arr[] = {'w', 'o', 'r'};
    CharArrayList test = CharArrayList(arr, 3);
    CharArrayList other = CharArrayList();

    test.concatenate(&other);
    //should not change

    other.pushAtFront('d');
    assert(test.toString() == "[CharArrayList of size 3 <<wor>>]");

    test.concatenate(&other);
    //should become word

    assert(test.toString() == "[CharArrayList of size 4 <<word>>]");
}

void insertOrderTest() {
    char arr[] = {'a', 'b', 'd', 'e'};
    CharArrayList test(arr, 4);
    test.insertInOrder('c');
    //should now be abcde

    assert(test.toString() == "[CharArrayList of size 5 <<abcde>>]");

    test.insertInOrder('b');
    //should now be abbcde

    assert(test.toString() == "[CharArrayList of size 6 <<abbcde>>]");

    test.insertInOrder('z');
    //should now be abbcdez

    assert(test.toString() == "[CharArrayList of size 7 <<abbcdez>>]");
    test.popFromFront();

    //should now be bbcdez
    test.insertInOrder('a');
    //should now be abbcdez
    assert(test.toString() == "[CharArrayList of size 7 <<abbcdez>>]");
}

//tests if = creates shallow copies
void testOperator() {
    char arr[] = {'b', 'o', 'o'};
    CharArrayList test(arr, 3);

    CharArrayList newList = test;

    assert(&newList != &test);
    assert(newList.toString() == test.toString());
}

//tests the toReverseString() method
void testReverseString() {
    char arr[] = {'t', 'e', 's', 't', 's'};
    CharArrayList test(arr, 5);

    assert(test.toReverseString() == "[CharArrayList of size 5 <<stset>>]");
}