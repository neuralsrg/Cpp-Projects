#ifndef CLASSES_H_SENTRY
#define CLASSES_H_SENTRY

#include "interface.h"
#include <vector>
#include <memory>

namespace classes
{
	class SubObj;
	class Object;
}

class classes::SubObj : public interface::ISubObj
{
protected:
	short x, y;
	char symb;
	short color;
	std::vector<std::vector<short>> content;

	SubObj(short x, short y, char symb, short color, short len) :
		x(x), y(y), symb(symb), color(color), content(len) {}

public:
	virtual void drawLine(std::string &, std::vector<short> &,
			short, short) noexcept override = 0;
};

class classes::Object : public interface::IObject
{
protected:
	short x, y;
	std::vector<std::shared_ptr<classes::SubObj>> subObjects;
	short action;
	short priority;
	int timeBeforeNewAction;

	Object(short x, short y, short len, short p = -1) :
		x(x), y(y), subObjects(len), action(-1), priority(p), timeBeforeNewAction(0)
	{}
public:
	virtual void drawLine(std::string &, std::vector<short> &,
			short) noexcept override = 0;
};

#endif
