#!/bin/bash

g++ -g -Wall -c variable.cpp 
g++ -g -Wall -c expression.cpp 
g++ -g -Wall -c function.cpp 
g++ -g -Wall -c longnum.cpp 

g++ -g -Wall test.cpp variable.o expression.o function.o longnum.o -o test.out
valgrind ./test.out
