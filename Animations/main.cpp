#include <iostream>
#include <chrono>
#include <thread>
#include "progressbar.h"
#include "scene.h"
#include "tree.h"

int main()
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
	std::srand(31);
	scene::Scene sc(2);
	sc.run(30000);
}
