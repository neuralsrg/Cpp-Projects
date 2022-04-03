#ifndef CLASSES_H_SENTRY
#define CLASSES_H_SENTRY

#include "constants.h"
#include "array.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Radio_Round_Button.H>
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

	//short objType;

	Cell(int, int, int, int, short);

	virtual void click(Fl_Widget *, void *) = 0;

public:
	short objType;

	void setCallback(Scene *);
	virtual int getIndex(int, int, bool) const = 0;
	virtual short getDirection() const = 0;
	virtual void setDirection(short) = 0;

	static void callback_cell(Fl_Widget *w, void *u);
	static Array<SellInfo> field;

	void fillField(std::shared_ptr<Cell>);
	virtual void chooseLocation(int, int, std::shared_ptr<Cell>)  = 0;
	static void boomBubblePretenders(int);
	static void moveObjects(int);
	static void destroyBubblesLeft(int);
	//moveObjects again
	static void balloonTrials(int, int = 3);

	static void move(Scene *);

	virtual ~Cell() {}
};


class EmptyCell : public Cell
{
protected:

	void click(Fl_Widget *, void *) override;

public:
	
	EmptyCell(int, int, int, int);
	EmptyCell(const std::shared_ptr<Cell> &);
	int getIndex(int, int, bool) const override { return -1; }
	short getDirection() const override { return -1; };
	void setDirection(short) override {};
	void chooseLocation(int, int, std::shared_ptr<Cell>) override {}
	virtual ~EmptyCell() {}
};

class RoundObj : public Cell
{
protected:

	RoundObj(int, int, int, int, short);
	RoundObj(const std::shared_ptr<Cell> &, short);
	short direction;

public:

	int getIndex(int, int, bool) const override;
	short getDirection() const override { return direction; };
	void setDirection(short d) override { direction = d; };

	void chooseLocation(int, int, std::shared_ptr<Cell>) override;
	virtual ~RoundObj() {}
};

class Bubble : public RoundObj
{
protected:
	
	void click(Fl_Widget *, void *) override;

public:
	
	Bubble(int, int, int, int);
	Bubble(const std::shared_ptr<Cell> &);
	virtual ~Bubble() {}
};

class Balloon : public RoundObj
{
protected:
	
	void click(Fl_Widget *, void *) override;

public:
	
	Balloon(int, int, int, int);
	Balloon(const std::shared_ptr<Cell> &);
	virtual ~Balloon() {}
};

class Controls 
{
protected:

	Fl_Radio_Round_Button *rb[4];
	Controls() {}

public:
	
	short getState() const;
	virtual ~Controls() {}

};

class Scene : public Fl_Window, public Controls
{
	Fl_Group *ctrl_gr;
	Fl_Button *nextStepBtn;

public:

	Array<std::shared_ptr<Cell> *> cells;

	Scene(int);
	static void nsCallback(Fl_Widget *, void *);
	int run() const { return Fl::run(); }
	virtual	~Scene();
};

#endif
