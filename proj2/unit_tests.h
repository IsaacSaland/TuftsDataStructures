/*
 *  unit_tests.h
 *  Isaac Saland
 *  3/5/2024
 *
 *
 *  testing of various functions of each class of the CalcULater project
 *
 */

#include "Datum.h"
#include "parser.h"
#include "RPNCalc.h"
#include <cassert>
#include <string>
#include <sstream>
#include <stdexcept>

//tests the overloaded constructor of DatumStack
void testDSConstructor() {
    Datum arr[] = {Datum(5), Datum(true)};

    DatumStack test(arr, 2);

    assert(not test.isEmpty());

    assert(test.top().getBool());

    test.pop();
    //should now be just Datum(5)

    assert(test.top().getInt() == 5);

    test.pop();
    //should now be empty

    assert(test.isEmpty());
}

//tests isEmpty() and clear() in DatumStack
void testDSEmptyClear() {
    Datum arr[] = {Datum(5), Datum(true)};

    DatumStack test(arr, 2);

    assert(not test.isEmpty());
    
    test.clear();
    //should now be empty

    assert(test.isEmpty());
}

//tests the top() function in DatumStack
void testDSTop() {
    Datum arr[] = {Datum(5), Datum(true)};

    DatumStack test(arr, 2);

    assert(test.top().getBool());

    test.pop();
    //should now be Datum(5)

    assert(test.top().getInt() == 5);
}

//tests the top() function in DatumStack when failed
void testDSTopFail() {
    bool thrown = false;
    std::string em = "";

    DatumStack test;

    try {
        test.top();
    } catch(std::runtime_error &e) {
        thrown = true;
        em = e.what();
    }

    assert(thrown);
    assert(em == "empty_stack");
}

//tests the pop() function in DatumStack
void testDSPop() {
    Datum arr[] = {Datum(5), Datum(true)};

    DatumStack test(arr, 2);

    assert(test.top().getBool());
    assert(not test.isEmpty());

    test.pop();

    assert(test.top().getInt() == 5);
    assert(not test.isEmpty());

    test.pop();

    assert(test.isEmpty());
}

//tests the pop() function in DatumStack when failed
void testDSPopFail() {
    bool thrown = false;
    std::string em = "";

    DatumStack test;

    try {
        test.pop();
    } catch(std::runtime_error &e) {
        thrown = true;
        em = e.what();
    }

    assert(thrown);
    assert(em == "empty_stack");
}

//tests the push() function in DatumStack
void testDSPush() {
    DatumStack test;

    assert(test.isEmpty());

    test.push(Datum(false));

    assert(not test.isEmpty());
    assert(not test.top().getBool());
}

//tests the parseRString function in parser
void testParseRString() {
    std::string eq = " 1 2 + }";
    std::stringstream stream;
    stream << eq;

    assert((parseRString(stream) == "{ 1 2 + }"));

    std::stringstream test;
    eq = "  \n 1  2\n\n + }";
    test << eq;
    assert(parseRString(test) == "{ 1 2 + }");

    std::stringstream empty;
    eq = " }";
    empty << eq;
    assert(parseRString(empty) == "{ }");

    std::stringstream nested;
    eq = " 2 { 3 1 + } - }";
    nested << eq;
    assert(parseRString(nested) == "{ 2 { 3 1 + } - }");
}

//tests the isEmpty() and clear() functions of RPNCalc
void testRPNEmptyClear() {
    Datum arr[] = {Datum(5), Datum(true)};
    DatumStack data(arr, 2);
    RPNCalc test(data);

    assert(not test.isEmpty());
    test.clear();
    assert(test.isEmpty());
}

//tests the peek() and pop() functions of RPNCalc
void testRPNPeekPop() {
    Datum arr[] = {Datum(5), Datum(true)};
    DatumStack data(arr, 2);
    RPNCalc test(data);

    assert(test.peekEqual(Datum(true)));
    assert(test.peekEqual(test.peek()));
    test.pop();
    //should now just be Datum(5)

    assert(not test.isEmpty());
    assert(test.peekEqual(Datum(5)));

    test.pop();
    //should now be empty

    assert(test.isEmpty());
}