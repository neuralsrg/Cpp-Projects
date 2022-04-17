#include "scene.h"
#include "constants.h"
#include <string>
#include <thread>
#include <algorithm>

extern const char* const constants::colors[4];

scene::Scene::Scene(int obj) : objects(obj)
{
	objects[0] = std::make_shared<tree::Tree>(40, 10);
	objects[1] = std::make_shared<cow::Cow>(50, 20);
}

void scene::Scene::run(short ms)
{
	auto srt {
		[](std::shared_ptr<classes::Object> &o1, std::shared_ptr<classes::Object> &o2)
		{ return o1->priority <= o2->priority; }
	};

	std::string fullStr;
	std::string emptyLine(constants::WIDTH, ' ');
	std::vector<short> emptyCls(constants::WIDTH, constants::CLR_RESET);

	// time cycle 
	while (ms > 0) {
		fullStr.clear();
		for (auto it = objects.begin(); it != objects.end(); it++)
			(*it)->move();

		std::sort(objects.begin(), objects.end(), srt);

		for (int i = 0; i < constants::HEIGHT; ++i) {
			//std::cout << "Entered i= " << i << std::endl;
			std::string line = emptyLine;
			std::vector<short> clrs = emptyCls;
			for (auto it = objects.begin(); it != objects.end(); it++)
				(*it)->drawLine(line, clrs, i);

			short curColor = clrs[0];
			fullStr += constants::colors[curColor];
			for (int i = 0; i < constants::WIDTH; ++i) {
				if (clrs[i] == curColor)
					fullStr += line[i];
				else {
					curColor = clrs[i];
					fullStr += constants::colors[curColor];
					fullStr += line [i];
				}
			}
			fullStr += constants::colors[constants::CLR_RESET];
			fullStr += "|\n";
			//std::cout << "Exited i= " << i << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(constants::DELAY));
		std::system("clear");
		std::cout << fullStr;
		ms -= constants::DELAY;
	}
	std::system("clear");
}

