#ifndef CLASSES_H_SENTRY
#define CLASSES_H_SENTRY

#include "constants.h"
#include "array.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <iostream>

class Cell;
class RoundObj;
class Scene;

class SellInfo
{
public:

	std::shared_ptr<Cell> owner;
	Array<std::shared_ptr<Cell>> pretendList;

	SellInfo() : owner(), pretendList() {}
	SellInfo(std::shared_ptr<Cell> o) : owner(o), pretendList() {}
};

class Cell : public Fl_Button
{
protected:

	short objType;

	Cell(int, int, int, int, short);

	virtual void click(Fl_Widget *, void *) = 0;
	void setCallback(Scene *);

public:

	int btnParams[4];
	virtual int getCurrentIndex(int, int) const = 0;

	static void callback_cell(Fl_Widget *w, void *u);
	static Array<SellInfo> field;

	void fillField(std::shared_ptr<Cell>);
	virtual void chooseLocation(int, int, std::shared_ptr<Cell>) = 0;
	static void boomBubblePretenders(int);

	virtual ~Cell() {}
};


class EmptyCell : public Cell
{
protected:

	void click(Fl_Widget *, void *) override;

public:
	
	EmptyCell(int, int, int, int);
	EmptyCell(int[4]);
	int getCurrentIndex(int, int) const override { return -1; }
	void chooseLocation(int, int, std::shared_ptr<Cell>) override {}
	virtual ~EmptyCell() {}
};

class RoundObj : public Cell
{
protected:

	RoundObj(int, int, int, int, short);
	//RoundObj(int[4], short);
	short direction;

public:

	int getCurrentIndex(int, int) const override;

	void chooseLocation(int, int, std::shared_ptr<Cell>) override;
	virtual ~RoundObj() {}
};

class Bubble : public RoundObj
{
protected:
	
	void click(Fl_Widget *, void *) override;

public:
	
	Bubble(int, int, int, int);
	virtual ~Bubble() {}
};

class Scene
{
public:

	Array<Cell> cells;
};

#endif
