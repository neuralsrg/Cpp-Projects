#include <iostream>
#include <chrono>
#include <thread>
#include "progressbar.h"
#include "scene.h"
#include "tree.h"

int main(int argc, const char *argv[])
{
	if (argc < 5) {
		std::cout << "Please, enter number of: trees, cows, creepers, time, and seed (optional)" << std::endl;
		exit(1);
	}
	std::srand(argc == 6 ? atoi(argv[5]) : 89);
	scene::Scene sc(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	sc.run(atoi(argv[4]));
}
