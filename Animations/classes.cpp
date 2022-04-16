#include "classes.h"

void classes::SubObj::drawLine2(std::string &s,
		std::vector<short> &clrs, short l, short dx) noexcept
{
	if (l < 0 || l > (short)content.size())
		return;
	for (auto it = content[l].begin(); it != content[l].end(); it++) {
		s[dx + *it] = symb;
		clrs[dx + *it] = color;
	}
}

void classes::Object::drawLine1(std::string &s,
		std::vector<short> &clrs, short l) noexcept
{
	for (auto it = subObjects.begin(); it != subObjects.end(); it++) {
		(*it)->drawLine2(s, clrs, y - l, x);
	}
}
