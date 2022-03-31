#ifndef CLASSES_H_SENTRY
#define CLASSES_H_SENTRY

#include "constants.h"
#include "array.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <iostream>

class Scene;

class Cell : public Fl_Button
{
protected:

	short objType;

	Cell(int, int, int, int, short);
	virtual ~Cell() {}

	virtual void click(Fl_Widget *, void *) = 0;
	void setCallback(Scene *);

	virtual void chooseDirection(int, int) = 0;
	//virtual int move() = 0;

public:

	static void callback_cell(Fl_Widget *w, void *u);
};

class EmptyCell : public Cell
{
protected:

	void click(Fl_Widget *, void *) override;
	void chooseDirection(int, int) override {}
	//int move() override { return MOVING_OK; }

public:
	
	EmptyCell(int, int, int, int);
	virtual ~EmptyCell() {}
};

class RoundObj : public Cell
{
protected:

	RoundObj(int, int, int, int, short);
	int nextLocation;
	short newDirection;

	void chooseDirection(int, int) override;
	void checkAbilityToMove(Array<RoundObj *> *);

public:

	virtual short fixIssue() = 0;
	void doneMoving();

	static Array<int> takenLocations;
	virtual ~RoundObj() {}
};

class Bubble : public RoundObj
{
protected:
	
	//int move() override;
	void click(Fl_Widget *, void *) override;
	short fixIssue() override;

public:
	
	Bubble(int, int, int, int);
	virtual ~Bubble() {}
};

#endif
