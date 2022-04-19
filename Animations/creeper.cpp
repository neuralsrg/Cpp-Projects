#include "creeper.h"
#include <vector>
#include <algorithm>
#include <numeric>

creeper::Body::Body() : SubObj(0, 1, '/', constants::CLR_GREEN, 15)
{
	std::vector<short> tmp_sizes = {15,15,15,25,25,25,19,0,21,25,25,25,25,25,19};
	std::vector<short> tmp_init = {7,7,7,2,2,2,5,0,4,2,2,2,2,2,5};

	for (int i = 0; i < 15; ++i) {
		if (!tmp_sizes[i])
			continue;
		content[i].resize(tmp_sizes[i]);
		std::iota(content[i].begin(), content[i].end(), tmp_init[i]);
	}
}

void creeper::Body::act(short action) noexcept
{
	if (action == constants::CREEPER_BLINK) {
		color = color == constants::CLR_GREEN ?
			constants::CLR_RESET : constants::CLR_GREEN;
	}
	else if (action == constants::CREEPER_BLOW) {
		for (auto it = content.begin(); it != content.end(); it++)
			(*it).clear();
		content.clear();
	}
}

creeper::Shape::Shape() : SubObj(0, 1, '@', constants::CLR_GRAY, 16)
{
	content[0] = {5, 6, 12, 13, 14, 15, 16, 22, 23};
	content[1] = {5, 6, 22, 23};
	content[2] = {2, 3, 4, 5, 6, 22, 23, 24, 25, 26};
	content[3] = {0, 1, 5, 6, 22, 23, 27, 28};
	content[4] = content[3];
	content[5] = content[3];
	content[6] = {2, 3, 4, 24, 25, 26};
	content[7].resize(21);
	std::iota(content[7].begin(), content[7].end(), 4);
	content[8] = {1, 2, 3, 25, 26, 27};
	content[9] = {0, 1, 27, 28};
	content[10] = {0, 1, 27, 28};
	content[11] = {0, 1, 27, 28};
	content[12] = {0, 1, 27, 28};
	content[13] = {0, 1, 27, 28};
	content[14] = {2, 3, 4, 24, 25, 26}; content[15].resize(21); std::iota(content[15].begin(), content[15].end(), 4); } 
void creeper::Shape::act(short action) noexcept
{
	if (action == constants::CREEPER_BLOW) {
		for (auto it = content.begin(); it != content.end(); it++)
			(*it).clear();
		content.clear();
	}
}

creeper::Face::Face() : SubObj(7, 10, '@', constants::CLR_GRAY, 5)
{
	content[0] = {3, 4, 10, 11};
	content[1] = {3, 4, 5, 6, 7, 8, 9, 10, 11};
	content[2] = {5, 6, 7, 8, 9};
	content[3] = {0, 1, 2, 3, 4, 10, 11, 12, 13};
	content[4] = content[3];
}

void creeper::Face::act(short action) noexcept
{
	if (action == constants::CREEPER_BLOW) {
		for (auto it = content.begin(); it != content.end(); it++)
			(*it).clear();
		content.clear();
	}
}

creeper::Paw::Paw(short n) : SubObj(n ? 4 : 16, 0, '@', constants::CLR_GRAY, 1)
{
	content[0] = {1, 2, 3, 4, 5, 6, 7};
}

void creeper::Paw::act(short action) noexcept
{
	auto inc {
		[](short &n) { ++n; }
	};
	auto dec {
		[](short &n) { --n; }
	};
	switch (action) {
		case constants::CREEPER_LEFT:
			if (content[0][0] == 0)
				std::for_each(content[0].begin(), content[0].end(), inc);
			else
				std::for_each(content[0].begin(), content[0].end(), dec);
			return;
		case constants::CREEPER_RIGHT:
			if (content[0][0] == 1)
				std::for_each(content[0].begin(), content[0].end(), dec);
			else
				std::for_each(content[0].begin(), content[0].end(), inc);
			return;
		case constants::CREEPER_BLINK:
			if (content[0][0] != 1)
				content[0] = {1, 2, 3, 4, 5, 6, 7};
			return;
		case constants::CREEPER_BLOW:
			for (auto it = content.begin(); it != content.end(); it++)
				(*it).clear();
			content.clear();
			return;
	}
}

creeper::Blow::Blow() : SubObj(7, 5, '%', constants::CLR_GRAY, 8) {}

void creeper::Blow::act(short action) noexcept
{
	if (action == constants::CREEPER_DEAD) {
		if (!content.empty()) {
			for (auto it = content.begin(); it != content.end(); it++)
				(*it).clear();
			content.clear();
		}
		return;
	}
	if (action == constants::CREEPER_BLOW && content[0].size() == 0) {
		content[0] = {1, 9, 10, 20};
		content[1] = {3, 4, 8, 9, 10, 11, 12, 13, 18, 19, 20, 21};
		content[2].resize(18);
		std::iota(content[2].begin(), content[2].end(), 5);
		content[3].resize(20);
		std::iota(content[3].begin(), content[3].end(), 3);
		content[4].resize(20);
		std::iota(content[4].begin(), content[4].end(), 0);
		content[5].resize(19);
		std::iota(content[5].begin(), content[5].end(), 4);
		content[6] = {5, 6, 7, 8, 9, 10, 15, 16, 17, 18};
		content[7] = {3, 4, 9, 10, 16};
	}
	if (action == constants::CREEPER_BLOW)
		color = color == constants::CLR_GRAY ?
			constants::CLR_RESET : constants::CLR_GRAY;
}

creeper::Creeper::Creeper(short x, short y) : Object(x, y, 6, y)
{
	subObjects[0] = std::make_shared<creeper::Body>();
	subObjects[1] = std::make_shared<creeper::Shape>();
	subObjects[2] = std::make_shared<creeper::Face>();
	subObjects[3] = std::make_shared<creeper::Paw>(0);
	subObjects[4] = std::make_shared<creeper::Paw>(1);
	subObjects[5] = std::make_shared<creeper::Blow>();
}

void creeper::Creeper::chooseAction() noexcept
{
	/*
	if (action == -1) {
		action = 0;
		return;
	}
	if (action == 0) {
		action = 1;
		return;
	}
	if (action == 1) {
		action = 2;
		return;
	}
	if (action == 2) {
		action = 3;
		return;
	}
	if (action == 3) {
		action = 4;
		return;
	}
	*/
	if (action == constants::CREEPER_DEAD)
		return;
	if (action == constants::CREEPER_BLINK) {
		action = constants::CREEPER_BLOW;
		return;
	}
	if (action == constants::CREEPER_BLOW) {
		action = constants::CREEPER_DEAD;
		return;
	}
	if (std::rand() % 6 == 5) {
		action = constants::CREEPER_BLINK;
		return;
	}
	action = std::rand() % 2;
}

void creeper::Creeper::moveSubObj() noexcept
{
	if (action == constants::CREEPER_DEAD)
		return;
	if (timeBeforeNewAction <= 0) {
		timeBeforeNewAction = constants::CREEPER_DELAY;
		chooseAction();
	}
	for (auto it = subObjects.begin(); it != subObjects.end(); it++) {
		(*it)->act(action);
	}
	timeBeforeNewAction -= constants::DELAY;
}

void creeper::Creeper::move() noexcept
{
	if (action == constants::CREEPER_LEFT || action == constants::CREEPER_RIGHT) {
		if (std::rand() % 5 == 4) {
			if ((std::rand() % 2) && (y < constants::HEIGHT)) {
				++y;
				++priority;
			} else if (y > 17) {
				--y;
				--priority;
			}
		}
	}
	if ((action == constants::CREEPER_LEFT) && (x > 0))
		--x;
	else if ((action == constants::CREEPER_RIGHT) && (x < constants::WIDTH - 29))
		++x;
	moveSubObj();
}

void creeper::Creeper::drawLine(std::string &s,
		std::vector<short> &clrs, short l) noexcept
{
	if (action != constants::CREEPER_DEAD) {
		classes::Object::drawLine(s, clrs, l); 
	}
}
