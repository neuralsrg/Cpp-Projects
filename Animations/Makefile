all: output

output: main.o scene.o progressbar.o tree.o cow.o creeper.o classes.o
	g++ -g -Wall main.o scene.o progressbar.o tree.o cow.o creeper.o classes.o -o output

main.o: main.cpp constants.h
	g++ -g -Wall -c main.cpp

scene.o: scene.h scene.cpp constants.h interface.h classes.h
	g++ -g -Wall -c scene.cpp 

progressbar.o: progressbar.cpp constants.h
	g++ -g -Wall -c progressbar.cpp 

tree.o: tree.h tree.cpp constants.h interface.h classes.h
	g++ -g -Wall -c tree.cpp 

cow.o: cow.h cow.cpp constants.h interface.h classes.h
	g++ -g -Wall -c cow.cpp 

creeper.o: creeper.h creeper.cpp constants.h interface.h classes.h
	g++ -g -Wall -c creeper.cpp 

classes.o: classes.h classes.cpp
	g++ -g -Wall -c classes.cpp 

clean:
	rm *.o output

