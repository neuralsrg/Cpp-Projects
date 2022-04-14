#ifndef CLASSES_H_SENTRY
#define CLASSES_H_SENTRY

#include "interface.h"
#include <vector>
#include <memory>

namespace classes
{
	class Object;
	class SubObj;
}

class classes::Object : public interface::IObject
{
protected:
	short x, y;
	std::vector<std::shared_ptr<classes::SubObj>> subObjects;
	short action;
	short priority;

	Object(short x, short y, short len, short action) :
		x(x), y(y), subObjects(len), action(action), priority(-1) {}
};

class classes::SubObj : public interface::ISubObj
{
protected:
	short x, y;
	char symb;
	std::string color;
	std::vector<std::vector<short>> content;

	SubObj(short x, short y, char symb, std::string color, short len) :
		x(x), y(y), symb(symb), color(color), content(len) {}
};

#endif
