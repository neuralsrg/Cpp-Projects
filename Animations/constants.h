#ifndef CONSTANTS_H_SENTRY
#define CONSTANTS_H_SENTRY

namespace constants
{
	enum sizes {WIDTH = 100, HEIGHT = 20};
	enum time {DELAY = 500}; // 50 ms delay
	enum color_inds {CLR_RESET, CLR_RED, CLR_GREEN, CLR_GRAY};
	const char* const colors[4] = {"\033[0m", "\033[31m", "\033[32m", "\033[90m"};

	enum tree {TREE_CALM, TREE_LEFT, TREE_RIGHT, TREE_DELAY = 3 * DELAY};

	enum cow {COW_STAYING, COW_LEFT, COW_RIGHT, COW_EATING};
	enum creeper {CREEPER_STAYING, CREEPER_LEFT, CREEPER_RIGHT, CREEPER_BLOW};
}

#endif
