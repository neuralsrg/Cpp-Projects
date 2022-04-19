#ifndef TREE_H_SENTRY 
#define TREE_H_SENTRY

#include "classes.h"

namespace tree
{
	class Stem;
	class Foliage;
	class Tree;
}

class tree::Stem : public classes::SubObj
{
public:
	Stem();

	void mirror() noexcept override {}
	void act(short) noexcept override {}
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }
	virtual ~Stem() {}
};

class tree::Foliage : public classes::SubObj
{
public:
	Foliage();

	void mirror() noexcept override {}
	void act(short) noexcept override;
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l, short dx) noexcept override
	{ classes::SubObj::drawLine(s, clrs, l, dx); }
	virtual ~Foliage() {}
};

class tree::Tree : public classes::Object
{
protected:
	void chooseAction() noexcept override;
	void moveSubObj() noexcept override;
public:
	Tree(short, short);

	void move() noexcept override;
	virtual void drawLine(std::string &s, std::vector<short> &clrs,
			short l) noexcept override
	{ classes::Object::drawLine(s, clrs, l); }
	virtual ~Tree() {}
};

#endif
