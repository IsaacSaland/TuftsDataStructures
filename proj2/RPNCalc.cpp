/*
 *  RPNCalc.cpp
 *  Isaac Saland
 *  3/5/2024
 *
 *
 *  implementation of the RPNCalc class
 *
 */

#include "RPNCalc.h"
#include "parser.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <istream>
#include <fstream>

/*
 * name: default constructor
 * purpose: creates a blank RPNCalc instance
 * args: none
 * returns: none
*/
RPNCalc::RPNCalc() {
    quit = false;
}

/*
 * name: push
 * purpose: pushes a datum onto dstack
 * args: datum dat
 * returns: none
*/
void RPNCalc::push(const Datum &dat) {
    dstack.push(dat);
}

/*
 * name: isEmpty
 * purpose: tells if there is or isnt data
 * args: none
 * returns: true if data is empty, false if not
*/
bool RPNCalc::isEmpty() const {
    return dstack.isEmpty();
}

/*
 * name: clear
 * purpose: gets rid of all Datum in data
 * args: none
 * returns: none
*/
void RPNCalc::clear() {
    dstack.clear();
}

/*
 * name: size
 * purpose: finds amount of data
 * args: none
 * returns: int size of data
*/
int RPNCalc::size() const {
    return dstack.size();
}

/*
 * name: peek
 * purpose: see the top Datum without removing it
 * args: none
 * returns: top Datum of data
*/
Datum RPNCalc::peek() const {
    return dstack.top();
}

/*
 * name: pop
 * purpose: get rid of the top Datum in data
 * args: none
 * returns: none
*/
void RPNCalc::pop() {
    dstack.pop();
}

/*
 * name: peekpEqual
 * purpose: compares the top element of dstack to &dat
 * args: Datum dat
 * returns: a bool if both datum are of the same type and same value
 * note: this method is to solve a bug with operator== of Datum
*/
bool RPNCalc::peekEqual(const Datum dat) const {
    Datum compare = peek();
    
    if(compare.isBool() and dat.isBool())
        return compare.getBool() == dat.getBool();
    if(compare.isInt() and dat.isInt())
        return compare.getInt() == dat.getInt();
    if(compare.isRString() and dat.isRString())
        return compare.getRString() == dat.getRString();
    
    return false;
}

/*
 * name: printTop
 * purpose: prints the top Datum of dstack
 * args: none
 * returns: none
*/
void RPNCalc::printTop() {
    std::cout << peek().toString() << std::endl;
}

/*
 * name: dup
 * purpose: duplicates the top Datum of the stack and pushes it
 * args: none
 * returns: none
*/
void RPNCalc::dup() {
    Datum temp = peek();
    push(temp);
}

/*
 * name: swap
 * purpose: swaps the first two Datum on dstack, does nothing if stack is < 2
 * args: none
 * returns: none
*/
void RPNCalc::swap() {
    if(size() < 2) return;
    Datum temp = peek();
    pop();
    Datum other = peek();
    pop();
    push(temp);
    push(other); 
}

/*
 * name: got_int
 * purpose: checks if a string has an int
 * args: string s, int *resultp
 * returns: true if has an int, false if not
*/
bool RPNCalc::got_int(std::string s, int *resultp)
{
        /* Holds the first non-whitespace character after the integer */
        char extra;

        return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

/*
 * name: doOperator
 * purpose: applies the given operator to the top 2
 *          Datum in dstack if theyre ints
 * args: char op
 * returns: none
*/
void RPNCalc::doOperator(char op) {
    Datum num2 = peek();
    pop();
    Datum num1 = peek();
    pop();

    if(not num1.isInt() or not num2.isInt()) {
        std::cerr << "Error: datum_not_int\n";
        return ;
    }

    switch(op) {
        case '+':
            push(Datum(num1.getInt() + num2.getInt()));
            break;
        case '-':
            push(Datum(num1.getInt() - num2.getInt()));
            break;
        case '*':
            push(Datum(num1.getInt() * num2.getInt()));
            break;
        case '/':
            if(num2.getInt() == 0) std::cerr << "Error: division by 0.\n";
            else push(Datum(num1.getInt() / num2.getInt()));
            break;
        case '%':
            if(num2.getInt() == 0) std::cerr << "Error: division by 0.\n";
            else push(Datum(num1.getInt() % num2.getInt()));
            break;
        default:
            std::cerr << std::to_string(op) + "not valid operator";
    }
}

/*
 * name: compare
 * purpose: compares the top two Datum using the inputted operator
 *          and pushes the result as a Datum to dstack
 * args: std::string op
 * returns: none
*/
void RPNCalc::compare(std::string op) {
    Datum el2 = peek();
    pop();
    Datum el1 = peek();
    pop();

    if(op == "==") {
        push(Datum(el1 == el2));
        return ;
    }

    if(not el1.isInt() or not el2.isInt()) {
        std::cerr << "Error: datum_not_int\n";
        return ;
    }

    if(op == ">") push(Datum(el2 < el1));
    if(op == "<") push(Datum(el1 < el2));
    if(op == "<=") push(Datum(el1 < el2 or el1 == el2));
    if(op == ">=") push(Datum(el2 < el1 or el1 == el2));
}

/*
 * name: exec
 * purpose: attempts to execute the top (rstring) of dstack as a comm sequence
 * args: none
 * returns: none
*/
void RPNCalc::exec() {
    Datum temp = peek();
    pop();
    if(not temp.isRString()) {
        std::cerr << "Error: cannot execute non rstring\n";
    }
    else{
        std::stringstream stream;
        stream << temp.getRString().substr(2, temp.getRString().size() - 4);
        runHelper(stream);
    }
}

/*
 * name: doFile
 * purpose: attempts to execute commands in the file
 * args: none
 * returns: none
*/
void RPNCalc::doFile() {
        Datum temp = peek();
        pop();
        if(not temp.isRString()) {
            std::cerr << "Error: file operand not rstring\n";
        }
        else {
            std::string fileName = temp.getRString();
            fileName = fileName.substr(2, fileName.size() - 4);
            //should now be left with just a filename

            std::ifstream fileStream(fileName);
            if(not fileStream.is_open()) {
                std::cerr << "Unable to read " << fileName << std::endl;
                return;
            }
            runHelper(fileStream);
        }
}

/*
 * name: doIf
 * purpose: executes the top rstring if true, bottom if false
 * args: none
 * returns: none
*/
void RPNCalc::doIf() {
    Datum ifF = peek();
    pop();
    Datum ifT = peek();
    pop();
    Datum check = peek();
    pop();

    if(not ifF.isRString() or not ifT.isRString()) {
        std::cerr << "Error: expected rstring in if branch\n";
        return ;
    }
    if(not check.isBool()) {
        std::cerr << "Error: expected boolean in if test\n";
        return ;
    }

    bool con = check.getBool();
        

    if(con) push(ifT);
    else push(ifF);

    exec();
}

/*
 * name: run
 * purpose: runs the simulation using runHelper
 * args: none
 * returns: none
*/
void RPNCalc::run() {
    runHelper(std::cin);
    std::cerr << "Thank you for using CalcYouLater.\n";
}

/*
 * name: runHelper
 * purpose: runs the simulation using input
 * args: istream &input
 * returns: none
*/
void RPNCalc::runHelper(std::istream &input) {
    std::string comm;
    while(not quit and input >> comm){
        try{
            int gotNum;
            if(comm == "quit"){ 
                quit = true;
            }
            else if (got_int(comm, &gotNum)) 
                push(Datum(gotNum));
            else if (comm == "#t") 
                push(Datum(true));
            else if (comm == "#f") 
                push(Datum(false));
            else if (comm == "{") 
                push(Datum(parseRString(input)));
            else if (comm == "not") {
                Datum temp(not peek().getBool());
                pop();
                push(temp);
            }
            else if (comm == "print") 
                printTop();
            else if (comm == "clear") 
                clear();
            else if (comm == "drop") 
                pop();
            else if (comm == "dup") 
                dup();
            else if (comm == "swap") 
                swap();
            else if (comm == "+") 
                doOperator('+');
            else if (comm == "-") 
                doOperator('-');
            else if (comm == "*") 
                doOperator('*');
            else if (comm == "/") 
                doOperator('/');
            else if (comm == "mod") 
                doOperator('%');
            else if (comm == "==") 
                compare("==");
            else if (comm == ">=") 
                compare(">=");
            else if (comm == "<=") 
                compare("<=");
            else if (comm == ">") 
                compare(">");
            else if (comm == "<") 
                compare("<");
            else if (comm == "exec") 
                exec();
            else if (comm == "file") 
                doFile();
            else if (comm == "if") 
                doIf();
            else if (comm == "#") 
                std::cerr << "Error: invalid boolean #\n";
            else 
                std::cerr << comm << ": unimplemented\n";
        }
        catch(std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}