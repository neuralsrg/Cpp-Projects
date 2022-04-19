#include "scene.h"
#include "constants.h"
#include <string>
#include <thread>
#include <algorithm>

extern const char* const constants::colors[4];

scene::Scene::Scene(short trees, short cows, short creepers) :
	objects(trees + cows + creepers)
{
	for (int i = 0; i < trees; ++i) {
		objects[i] = std::make_shared<tree::Tree>(std::rand() % (constants::WIDTH - 22),
				std::rand() % (constants::HEIGHT - 10) + 10);
	}
	for (int i = 0; i < cows; ++i) {
		objects[trees + i] =
			std::make_shared<cow::Cow>(std::rand() % (constants::WIDTH - 50),
				std::rand() % (constants::HEIGHT - 12) + 12);
	}
	for (int i = 0; i < creepers; ++i) {
		objects[trees + cows + i] =
			std::make_shared<creeper::Creeper>(std::rand() % (constants::WIDTH - 30),
				std::rand() % (constants::HEIGHT - 18) + 18);
	}
}

void scene::Scene::run(int ms)
{
	auto srt {
		[](std::shared_ptr<classes::Object> &o1, std::shared_ptr<classes::Object> &o2)
		{ return o1->priority <= o2->priority; }
	};

	pb::ProgressBar pbar(1, ms / constants::DELAY);
	float progress = 0;
	std::string fullStr;
	std::string emptyLine(constants::WIDTH, ' ');
	std::vector<short> emptyCls(constants::WIDTH, constants::CLR_RESET);

	// time cycle 
	while (ms > 0) {
		fullStr.clear();
		pbar.update(progress++);

		for (auto it = objects.begin(); it != objects.end(); it++)
			(*it)->move();

		std::sort(objects.begin(), objects.end(), srt);

		for (int i = 0; i < constants::HEIGHT; ++i) {
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
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(constants::DELAY));
		std::system("clear");
		pbar.print();
		std::cout << fullStr;
		ms -= constants::DELAY;
	}
	std::system("clear");
}

