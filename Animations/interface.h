#ifndef INTERFACE_H_SENTRY 
#define INTERFACE_H_SENTRY

#include <iostream>
#include <vector>

namespace interface
{
	class IObject;
	class ISubObj;
}

class interface::IObject
{
protected:
	virtual void chooseAction() noexcept = 0;
	virtual void moveSubObj() noexcept = 0;
public:
	virtual void move() noexcept = 0;
	virtual void drawLine(std::string &, std::vector<short> &, short) noexcept = 0;
};

class interface::ISubObj
{
public:
	virtual void act(short) noexcept = 0;
	virtual void drawLine(std::string &, std::vector<short> &,
			short, short) noexcept = 0;
};

#endif
