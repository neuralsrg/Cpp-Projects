all: output

output: lagrange_relaxation.o solver_doc.o
	g++ -g -Wall lagrange_relaxation.o solver_doc.o -o output

lagrange_relaxation.o: lagrange_relaxation.cpp
	g++ -g -Wall -c lagrange_relaxation.cpp

solver_doc.o: solver_doc.hpp solver_doc.cpp
	g++ -g -Wall -c solver_doc.cpp 

clean:
	rm *.o output

