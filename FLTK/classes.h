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

	Cell(int, int, int, int, const char *, int);
	virtual ~Cell() {}

	virtual void click(Fl_Widget *, void *) = 0;
	void setCallback(Scene *);
	virtual void chooseDirection(int, int) = 0;
	virtual short move() = 0;

public:

	static void callback_cell(Fl_Widget *w, void *u);
};

class EmptyCell : public Cell
{
protected:

	void click(Fl_Widget *, void *) override;
	void chooseDirection(int, int) override {}
	short move() override { return  }

public:
	
	EmptyCell(int, int, int, int, const char *);
	virtual ~EmptyCell() {}
};

class RoundObj : public Cell
{
protected:

	RoundObj(int, int, int, int, const char *, short);
	int nextLocation;
	short newDirection;
	void chooseDirection(int, int);
	virtual void move(Scene *) = 0;

public:

	static Array<int> takenLocations;
};

class Bubble : public RoundObj
{
protected:
	
	void move(Scene *);
};

#endif
