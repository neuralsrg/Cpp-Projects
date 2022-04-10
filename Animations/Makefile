all: output

output: main.o progressbar.o
	g++ -g -Wall main.o progressbar.o -o output

main.o: main.cpp constants.h
	g++ -g -Wall -c main.cpp

progressbar.o: progressbar.cpp constants.h
	g++ -g -Wall -c progressbar.cpp 

clean:
	rm *.o output

