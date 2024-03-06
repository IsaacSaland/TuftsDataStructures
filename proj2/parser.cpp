/*
 *  perser.cpp
 *  Isaac Saland
 *  3/5/2024
 *
 *
 *  file containing implementation of the parseRString method
 *
 */

#include <string>
#include <sstream>
using namespace std;


/*
 * name: parseRString
 * purpose: find and format a postfix expression from input
 * args: istream &input
 * returns: a formatted rstring of a postfix expression
*/
string parseRString(istream &input) {
    string info;
    string str = "{ ";
    int extraBrackets = 1;

    while(input >> info) {
        str += info;

        if(info == "{") extraBrackets++;
        if(info == "}") extraBrackets--;
        if(extraBrackets == 0) return str;

        str += " ";
    }
    return str;
}