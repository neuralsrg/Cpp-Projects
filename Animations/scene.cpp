#include "scene.h"
#include "constants.h"
#include <string>
#include <thread>

extern const char* const constants::colors[4];

scene::Scene::Scene(int trees) : objects(trees)
{
	objects[0] = std::make_shared<tree::Tree>(40, 60);
}

void scene::Scene::run(short ms)
{
	std::string fullStr;
	std::string emptyLine(constants::WIDTH, ' ');
	std::vector<short> emptyCls(constants::WIDTH, constants::CLR_RESET);

	// time cycle 
	while (ms > 0) {
		fullStr.clear();
		for (int i = 0; i < constants::HEIGHT; ++i) {
			std::string line = emptyLine;
			std::vector<short> clrs = emptyCls;
			for (auto it = objects.begin(); it != objects.end(); it++) {
				(*it)->move();
				(*it)->drawLine1(line, clrs, i);
			}
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
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(constants::DELAY));
		std::system("clear");
		std::cout << fullStr;
		ms -= constants::DELAY;
	}
}

