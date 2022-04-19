#ifndef CONSTANTS_H_SENTRY
#define CONSTANTS_H_SENTRY

namespace constants
{
	enum sizes {WIDTH = 170, HEIGHT = 40};
	enum time {DELAY = 500}; // 50 ms delay
	enum color_inds {CLR_RESET, CLR_RED, CLR_GREEN, CLR_GRAY};
	const char* const colors[4] = {"\033[0m", "\033[31m", "\033[32m", "\033[90m"};

	enum tree {TREE_CALM, TREE_LEFT, TREE_RIGHT, TREE_DELAY = 3 * DELAY};
	enum cow {COW_STAYING, COW_WALKING, COW_EATING, COW_DELAY = 6 * DELAY};
	enum creeper {CREEPER_LEFT, CREEPER_RIGHT, CREEPER_BLINK, CREEPER_BLOW, 
					CREEPER_DEAD, CREEPER_DELAY = 4 * DELAY};
}

#endif
