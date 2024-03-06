/*
 *  RPNCalc.h
 *  Isaac Saland
 *  2/25/2024
 *
 *
 *  interface of DatumStack; contains declarations of all public/private
 *  functions/variables
 *
 */

#include "Datum.h"
#include "DatumStack.h"
#include <string>
#include <istream>

class RPNCalc {
    public:
        RPNCalc();

        //run command
        void run();
        

    private:
        DatumStack dstack;
        bool quit;
        
        bool got_int(std::string s, int *resultp);
        void runHelper(std::istream &input);
        void push(const Datum &dat);
        bool isEmpty() const;
        void clear();
        int size() const;
        Datum peek() const;
        void pop();
        bool peekEqual(const Datum dat) const;

        //other command functions:
        void printTop();
        void dup();
        void swap();
        void doOperator(char op);
        void compare(std::string op);
        void exec();
        void doFile();
        void doIf();
};