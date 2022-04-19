#include "cow.h"
#include "constants.h"
#include <algorithm>
#include <numeric>

extern const char* const colors[4];

cow::Head::Head() : SubObj(0, 2, '@', constants::CLR_RESET, 11)
{
	std::vector<short> tmp_sizes = {3, 5, 11, 13, 11, 9, 2, 1};
	std::vector<short> tmp_init = {10, 8, 2, 0, 2, 4, 8, 9, 10};
	for (int i = 3; i < 11; ++i) {
		content[i].resize(tmp_sizes[i - 3]);
		std::iota(content[i].begin(), content[i].end(), tmp_init[i - 3]);
	}
}

void cow::Head::act(short action) noexcept
{
	if (action != constants::COW_EATING) {
		if (content[0].empty())
			return;
		for (auto it = content.begin(); it != content.begin() + 3; it++)
			(*it).clear();
		std::vector<short> tmp_sizes = {3, 5, 11, 13, 11, 9, 2, 1};
		std::vector<short> tmp_init = {10, 8, 2, 0, 2, 4, 8, 9, 10};
		for (int i = 3; i < 11; ++i) {
			content[i].resize(tmp_sizes[i - 3]);
			std::iota(content[i].begin(), content[i].end(), tmp_init[i- 3]);
		}
		return;
	}
	if (!content[0].empty())
		return;
	std::vector<short> tmp_sizes = {2, 4, 6, 9, 9, 11, 9, 7, 5};
	std::vector<short> tmp_init = {4, 4, 3, 4, 4, 2, 4, 6, 8};
	for (int i = 0; i < 9; ++i) {
		content[i].resize(tmp_sizes[i]);
		std::iota(content[i].begin(), content[i].end(), tmp_init[i]);
	}
	for (auto it = content.end() - 1; it != content.end() - 3; it--)
		(*it).clear();
}

cow::Body::Body() : SubObj(13, 4, '@', constants::CLR_RESET, 7)
{
	std::vector<short> tmp_sizes = {17, 26, 26, 26, 27, 27, 26};
	std::vector<short> tmp_init = {4, 0, 0, 0, 0, 0, 0};
	for (int i = 0; i < 7; ++i) {
		content[i].resize(tmp_sizes[i]);
		std::iota(content[i].begin(), content[i].end(), tmp_init[i]);
	}
}

cow::Paw::Paw(short n) : SubObj(n ? 10 : 32, 0, '@', constants::CLR_RESET, 5)
{
	std::vector<short> tmp_sizes = {5, 4, 4, 5, 5};
	std::vector<short> tmp_init = {1, 2, 2, 2, 2};
	for (int i = 0; i < 5; ++i) {
		content[i].resize(tmp_sizes[i]);
		std::iota(content[i].begin(), content[i].end(), tmp_init[i]);
	}
}

void cow::Paw::act(short action) noexcept
{
	if (action == constants::COW_STAYING || action == constants::COW_EATING) {
		std::vector<short> tmp_sizes = {5, 4, 4, 5, 5};
		std::vector<short> tmp_init = {1, 2, 2, 2, 2};
		for (int i = 0; i < 5; ++i) {
			content[i].resize(tmp_sizes[i]);
			std::iota(content[i].begin(), content[i].end(), tmp_init[i]);
		}
		return;
	}
	if (action == constants::COW_WALKING) {
		if (content[0][0] != 0) {
			std::vector<short> tmp_sizes = {4, 4, 4, 4, 5};
			std::vector<short> tmp_init = {0, 1, 1, 2, 2};
			for (int i = 0; i < 5; ++i) {
				content[i].resize(tmp_sizes[i]);
				std::iota(content[i].begin(), content[i].end(), tmp_init[i]);
			}
			return;
		}
		std::vector<short> tmp_sizes = {4, 5, 4, 4, 5};
		std::vector<short> tmp_init = {5, 4, 3, 2, 2};
		for (int i = 0; i < 5; ++i) {
			content[i].resize(tmp_sizes[i]);
			std::iota(content[i].begin(), content[i].end(), tmp_init[i]);
		}
	}
}

cow::Tail::Tail() : SubObj(40, 5, '*', constants::CLR_RESET, 5)
{
	std::vector<short> tmp_sizes = {3, 2, 2, 2, 1};
	std::vector<short> tmp_init = {1, 0, 0, 1, 0};
	for (int i = 0; i < 5; ++i) {
		content[i].resize(tmp_sizes[i]);
		std::iota(content[i].begin(), content[i].end(), tmp_init[i]);
	}
}

void cow::Tail::act(short action) noexcept
{
	if (action != constants::COW_EATING) {
		std::vector<short> tmp_sizes = {3, 2, 2, 2, 1};
		std::vector<short> tmp_init = {1, 0, 0, 1, 0};
		for (int i = 0; i < 5; ++i) {
			content[i].resize(tmp_sizes[i]);
			std::iota(content[i].begin(), content[i].end(), tmp_init[i]);
		}
		return;
	}
	std::vector<short> tmp_sizes = {3, 3, 2, 2, 1};
	std::vector<short> tmp_init = {7, 4, 3, 1, 0};
	for (int i = 0; i < 5; ++i) {
		content[i].resize(tmp_sizes[i]);
		std::iota(content[i].begin(), content[i].end(), tmp_init[i]);
	}
}

cow::Tongue::Tongue() : SubObj(5, 1, '&', constants::CLR_RED, 1) {}

void cow::Tongue::act(short action) noexcept
{
	if (action != constants::COW_EATING) {
		content[0].clear();
		return;
	}
	if (content[0].empty())
		content[0] = {0};
	else
		content[0].clear();
}

cow::Grass::Grass() : SubObj(0, 0, '/', constants::CLR_GREEN, 2) {}

void cow::Grass::act(short action) noexcept
{
	if (action != constants::COW_EATING) {
		content[0].clear();
		content[1].clear();
		return;
	}
	content[0] = {0, 1, 2, 3, 4, 5, 6};
	content[1] = {2};
}

cow::Cow::Cow(short x, short y) : Object(x, y, 7, y)
{
	subObjects[0] = std::make_shared<cow::Body>();
	subObjects[1] = std::make_shared<cow::Head>();
	subObjects[2] = std::make_shared<cow::Paw>(0);
	subObjects[3] = std::make_shared<cow::Paw>(1);
	subObjects[4] = std::make_shared<cow::Tail>();
	subObjects[5] = std::make_shared<cow::Tongue>();
	subObjects[6] = std::make_shared<cow::Grass>();
}

void cow::Cow::chooseAction() noexcept
{
	action = std::rand() % 3;
}

void cow::Cow::moveSubObj() noexcept
{
	if (timeBeforeNewAction <= 0) {
		timeBeforeNewAction = constants::COW_DELAY;
		chooseAction();
		// To make paws move in asymmetric way 
		subObjects[2]->act(action);
	}
	for (auto it = subObjects.begin(); it != subObjects.end(); it++)
		(*it)->act(action);
	timeBeforeNewAction -= constants::DELAY;
}

void cow::Cow::move() noexcept
{
	if (action == constants::COW_WALKING) {
		if (std::rand() % 5 == 4) {
			if ((std::rand() % 2) && (y < constants::HEIGHT)) {
				++y;
				++priority;
			} else if (y > 12) {
				--y;
				--priority;
			}
		} else
			--x;
		if (x < 0)
			x = constants::WIDTH - 50;
	}
	moveSubObj();
}
