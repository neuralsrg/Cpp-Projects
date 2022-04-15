#include "tree.h"
#include "constants.h"
#include <iostream>
#include <vector>

tree::Stem::Stem() : SubObj(9, 0, '&', "\033[30m", 5)
{
	content[0] = {2, 3};
	content[1] = {2, 3};
	content[2] = {2, 3, 4};
	content[3] = {1, 2, 3, 6};
}
