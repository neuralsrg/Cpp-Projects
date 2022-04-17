#ifndef COW_H_SENTRY 
#define COW_H_SENTRY

#include "classes.h"

namespace cow
{
	class Head;
	class Body;
	class Paw;
	class Tail;
	class Tongue;
	class Grass;
	class Cow;
}

class cow::Head : public classes::SubObj
{
public:
	Head();

	//TODO Delete all mirrors!
	void mirror() noexcept override {}
	void act(short) noexcept override;
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }

};

class cow::Body : public classes::SubObj
{
public:
	Body();

	void mirror() noexcept override {}
	void act(short) noexcept override {}
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }
};

class cow::Paw : public classes::SubObj
{
public:
	Paw(short);

	void mirror() noexcept override {}
	void act(short) noexcept override;
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }

};

class cow::Tail : public classes::SubObj
{
public:
	Tail();

	void mirror() noexcept override {}
	void act(short) noexcept override;
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }
};

class cow::Tongue : public classes::SubObj
{
public:
	Tongue();

	//TODO Delete all mirrors!
	void mirror() noexcept override {}
	void act(short) noexcept override;
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }

};

class cow::Grass : public classes::SubObj
{
public:
	Grass();

	//TODO Delete all mirrors!
	void mirror() noexcept override {}
	void act(short) noexcept override;
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }

};

class cow::Cow : public classes::Object
{
protected:
	void chooseAction() noexcept override;
	void moveSubObj() noexcept override;
public:
	Cow(short, short);

	void move() noexcept override;
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l) noexcept override
	{ classes::Object::drawLine(s, clrs, l); }
};

#endif
