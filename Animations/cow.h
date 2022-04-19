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

	void act(short) noexcept override;
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }
	virtual ~Head() {}
};

class cow::Body : public classes::SubObj
{
public:
	Body();

	void act(short) noexcept override {}
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }
	virtual ~Body() {}
};

class cow::Paw : public classes::SubObj
{
public:
	Paw(short);

	void act(short) noexcept override;
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }
	virtual ~Paw() {}
};

class cow::Tail : public classes::SubObj
{
public:
	Tail();

	void act(short) noexcept override;
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }
	virtual ~Tail() {}
};

class cow::Tongue : public classes::SubObj
{
public:
	Tongue();

	void act(short) noexcept override;
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }
	virtual ~Tongue() {}
};

class cow::Grass : public classes::SubObj
{
public:
	Grass();

	void act(short) noexcept override;
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }
	virtual ~Grass() {}
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
	virtual ~Cow() {}
};

#endif
