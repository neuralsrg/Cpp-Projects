#include <iostream>
#include <chrono>
#include <thread>
#include "progressbar.h"
#include "scene.h"
#include "tree.h"

int main(int argc, const char *argv[])
{
	/*
	pb::ProgressBar pbar(1, 100);
	for (int i = 1; i < 100; ++i) {
		pbar.print();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		pbar.update(i);
		std::system("clear");
	}
	*/
	std::srand(89); //32
	if (argc != 5)
		exit(1);
	scene::Scene sc(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	sc.run(atoi(argv[4]));
}
