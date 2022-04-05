#include "classes.h"
#include "constants.h"

int main(int argc, char **argv)
{
	std::srand(123);
	Scene *sc = new Scene(4);
	sc->run();
	delete sc;
	return 0;
}
