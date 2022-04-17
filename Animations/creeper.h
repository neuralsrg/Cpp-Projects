#ifndef CREEPER_H_SENTRY
#define CREEPER_H_SENTRY

#include "classes.h"

namespace creeper
{
	class Shape;
	class Body;
	class Face;
	class Paw;
	class Blow;
	class Creeper;
}

class creeper::Shape : public classes::SubObj
{
public:
	Shape();

	//TODO Delete all mirrors!
	void mirror() noexcept override {}
	void act(short) noexcept override {}
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }

};

class creeper::Body : public classes::SubObj
{
public:
	Body();

	void mirror() noexcept override {}
	void act(short) noexcept override {}
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }
};

class creeper::Face : public classes::SubObj
{
public:
	Face();

	void mirror() noexcept override {}
	void act(short) noexcept override {}
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }
};

class creeper::Paw : public classes::SubObj
{
public:
	Paw(short);

	void mirror() noexcept override {}
	void act(short) noexcept override;
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }

};

class creeper::Blow : public classes::SubObj
{
public:
	Blow();

	//TODO Delete all mirrors!
	void mirror() noexcept override {}
	void act(short) noexcept override;
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }

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
			short l) noexcept override
	{ classes::Object::drawLine(s, clrs, l); }
};

#endif
