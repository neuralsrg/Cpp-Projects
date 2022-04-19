#ifndef CREEPER_H_SENTRY
#define CREEPER_H_SENTRY

#include "classes.h"
#include "constants.h"

namespace creeper
{
	class Body;
	class Shape;
	class Face;
	class Paw;
	class Blow;
	class Creeper;
}

class creeper::Body : public classes::SubObj
{
public:
	Body();

	void act(short) noexcept override;
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }
	virtual ~Body() {}
};

class creeper::Shape : public classes::SubObj
{
public:
	Shape();

	void act(short) noexcept override;
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }
	virtual ~Shape() {}
};

class creeper::Face : public classes::SubObj
{
public:
	Face();

	void act(short) noexcept override;
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }
	virtual ~Face() {}
};

class creeper::Paw : public classes::SubObj
{
public:
	Paw(short);

	void act(short) noexcept override;
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }
	virtual ~Paw() {}
};

class creeper::Blow : public classes::SubObj
{
public:
	Blow();

	void act(short) noexcept override;
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }
	virtual ~Blow() {}
};

class creeper::Creeper : public classes::Object
{
protected:
	void chooseAction() noexcept override;
	void moveSubObj() noexcept override;
public:
	Creeper(short, short);

	void move() noexcept override;
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l) noexcept override;
	virtual ~Creeper() {}
};

#endif
