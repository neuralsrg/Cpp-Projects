#ifndef PARTS_H_SENTRY 
#define PARTS_H_SENTRY

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
	void act() noexcept override {}
};

class tree::Foliage : public classes::SubObj
{
public:
	Foliage();

	void mirror() noexcept override {}
	void act() noexcept override;
};

class tree::Tree : public classes::Object
{
protected:
	void chooseAction() noexcept override;
	void moveSubObj() noexcept override;
public:
	void move() noexcept override;
	void draw(std::string *) noexcept override;
};

#endif
