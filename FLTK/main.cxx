#include "classes.h"
#include "constants.h"

int main(int argc, char **argv)
{
	std::srand(438);
	Scene *sc = new Scene(3);
	sc->run();
	delete sc;
	return 0;
}
