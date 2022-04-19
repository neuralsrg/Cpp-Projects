#include "tree.h"
#include "constants.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

extern const char* const constants::colors[4];

tree::Stem::Stem() : SubObj(9, 0, '&', constants::CLR_GRAY, 5)
{
	content[0] = {2, 3};
	content[1] = content[0];
	content[2] = {2, 3, 4};
	content[3] = {2, 3, 5, 6};
	content[4] = {1, 2, 3, 6};
}

tree::Foliage::Foliage() : SubObj(0, 5, '+', constants::CLR_GREEN, 5)
{
	//content[0] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22};
	content[0].resize(21);
	std::iota(content[0].begin(), content[0].end(), 2);
	content[1] = content[0];
	content[2].assign(content[0].begin() + 1, content[0].end() - 1);
	content[3].assign(content[0].begin() + 5, content[0].end() - 5);
	content[4].assign(content[0].begin() + 8, content[0].end() - 8);
}

void tree::Foliage::act(short state) noexcept
{
	auto inc {
		[](short &n) { ++n; }
	};
	auto inc2 {
		[](short &n) { n += 2; }
	};

	auto dec {
		[](short &n) { --n; }
	};
	auto dec2 {
		[](short &n) { n -= 2; }
	};

	switch(state) {
		case constants::TREE_CALM:
			return;
		case constants::TREE_LEFT:
			if (content[2][0] != 0) {
				std::for_each(content[2].begin(), content[2].end(), dec);
				std::for_each(content[3].begin(), content[3].end(), dec2);
				std::for_each(content[4].begin(), content[4].end(), dec2);
			}
			return;
		case constants::TREE_RIGHT:
			if (content[2][0] != 6) {
				std::for_each(content[2].begin(), content[2].end(), inc);
				std::for_each(content[3].begin(), content[3].end(), inc2);
				std::for_each(content[4].begin(), content[4].end(), inc2);
			}
			return;
	}	
}

tree::Tree::Tree(short x, short y) : Object(x, y, 2, y)
{
	subObjects[0] = std::make_shared<tree::Stem>();
	subObjects[1] = std::make_shared<tree::Foliage>();
}

void tree::Tree::chooseAction() noexcept
{
	switch(action) {
		case -1:
			action = std::rand() % 3;
			return;
		case constants::TREE_CALM:
			action = std::rand() % 3;
			return;
		case constants::TREE_LEFT:
			action = std::rand() % 2 ? constants::TREE_CALM : constants::TREE_RIGHT;
			return;
		case constants::TREE_RIGHT:
			action = std::rand() % 2 ? constants::TREE_CALM : constants::TREE_LEFT;
			return;
	}
}

void tree::Tree::moveSubObj() noexcept
{
	if (timeBeforeNewAction <= 0) {
		timeBeforeNewAction = constants::TREE_DELAY;
		chooseAction();
	}
	for (int i = 0; i < (int)subObjects.size(); ++i) {
		subObjects[i]->act(action);
	}
	timeBeforeNewAction -= constants::DELAY;
}

void tree::Tree::move() noexcept
{
	moveSubObj();
}
