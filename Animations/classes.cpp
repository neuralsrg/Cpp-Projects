#include "classes.h"

void classes::SubObj::drawLine(std::string &s,
		std::vector<short> &clrs, short l, short dx) noexcept
{
	l -= y;
	dx += x;
	if (l < 0 || l > (short)content.size())
		return;
	if (!content[l - 1].empty())
		for (auto it = content[l - 1].begin(); it != content[l - 1].end(); it++) {
			s[dx + *it] = symb;
			clrs[dx + *it] = color;
		}
}

void classes::Object::drawLine(std::string &s,
		std::vector<short> &clrs, short l) noexcept
{
	for (auto it = subObjects.begin(); it != subObjects.end(); it++) {
		(*it)->drawLine(s, clrs, y - l, x);
	}
}
