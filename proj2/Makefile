###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  Isaac Saland

MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

##
##  --- Delete these comments and put appropriate comments in ---
##
## Put your variables and rules here.  You can use previous Makefiles
## as examples, and you can refer to the "make" documentation on the
## course Reference page.
##
## CAUTION:  DO NOT JUST USE THE OLD RULES FOR 'clean'!!!
##           You do NOT want to remove Datum.o!!
##
##  --- Delete these comments and put appropriate comments in ---


## Rules for building an executable from Datum+vector_example.cpp
## This is useful in seeing the behavior of Datum::toString()
Datum+vector_example.o: Datum+vector_example.cpp Datum.h

Datum+vector_example: Datum+vector_example.o Datum.o
	${CXX} ${LDFLAGS} -o $@ $^

DatumStack.o: DatumStack.h DatumStack.cpp Datum.h
	$(CXX) $(CXXFLAGS) -c DatumStack.cpp

parser.o: parser.h parser.cpp
	$(CXX) $(CXXFLAGS) -c parser.cpp

RPNCalc.o: RPNCalc.h RPNCalc.cpp DatumStack.h Datum.h
	$(CXX) $(CXXFLAGS) -c RPNCalc.cpp

unit_test: unit_test_driver.o DatumStack.o Datum.o parser.o RPNCalc.o
	$(CXX) $(CXXFLAGS) $^

main.o: DatumStack.o Datum.o parser.o RPNCalc.o
	$(CXX) $(CXXFLAGS) $^ -c main.cpp

CalcYouLater: main.o RPNCalc.o DatumStack.o Datum.o parser.o
	$(CXX) $(LDFLAGS) $^ -o CalcYouLater

##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^

clean:
	rm main.o RPNCalc.o parser.o DatumStack.o Datum+vector_example.o *~ a.out