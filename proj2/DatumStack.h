/*
 *  DatumStack.h
 *  Isaac Saland
 *  2/25/2024
 *
 *
 *  interface of DatumStack; contains declarations of all public/private
 *  functions/variables
 *
 */

#include "Datum.h"
#include <ostream>
#include <vector>
#include <string>

class DatumStack {
    public:
        DatumStack();
        DatumStack(Datum arr[], int size);

        bool isEmpty() const;
        void clear();
        int size() const;
        Datum top() const;
        void pop();
        void push(const Datum &item);
    private:
        std::vector<Datum> data;
};