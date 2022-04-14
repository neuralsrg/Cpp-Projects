#include <iostream>
#include <chrono>
#include <thread>
#include "progressbar.h"

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
	std::string red = "\033[31m";
	std::string reset = "\033[0m";
	std::string message1 = "Hello ";
	std::string message2 = "World ";
	std::string message3 = "!aa";
	std::string message4 = "   bbbb";
	std::string res = message1 + red + message2 + reset + message3 + message4;
	std::cout << res << std::endl;
}
