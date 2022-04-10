#include <iostream>
#include <chrono>
#include <thread>
#include "progressbar.h"

int main()
{
	pb::ProgressBar pbar(1, 100);
	for (int i = 1; i < 100; ++i) {
		pbar.print();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		pbar.update(i);
		std::system("clear");
	}
}
