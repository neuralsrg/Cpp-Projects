all: output

output: main.o Env.o Parser.o
	g++ -g -Wall main.o Env.o Parser.o -o output

main.o: main.cpp namespace.h
	g++ -g -Wall -c main.cpp

Env.o: Env.h Env.cpp
	g++ -g -Wall -c Env.cpp 

Parser.o: Parser.h Parser.cpp
	g++ -g -Wall -c Parser.cpp 

clean:
	rm *.o output
