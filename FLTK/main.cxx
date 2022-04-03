#include "classes.h"
#include "constants.h"

int main(int argc, char **argv)
{
	Scene *sc = new Scene(10);
	sc->run();
	delete sc;
	return 0;
}
