#include "classes.h"
#include "constants.h"

int main(int argc, char **argv)
{
	int seed, n;
	float scale;

	std::cout << "Enter seed:" << std::endl;
	std::cin >> seed;
	std::srand(seed);

	std::cout << "Enter cells number:" << std::endl;
	std::cin >> n;

	std::cout << "Enter scaling param:" << std::endl;
	std::cin >> scale;

	Scene *sc = new Scene(n, scale);
	sc->run();
	delete sc;
	return 0;
}
