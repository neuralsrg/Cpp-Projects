#include "classes.h"

/* Definitions of Classes functions */

/* Cell */

Cell::Cell(int x, int y, int w, int h, const char *name, int ot) :
	Fl_Button(x, y, w, h, name), objType(ot) {}

void Cell::setCallback(Scene *sc)
{
	callback(callback_cell, sc);
}

void Cell::callback_cell(Fl_Widget *w, void *u)
{
	((Cell *)w)->click(w, u);
}

/* EmptyCell */

EmptyCell::EmptyCell(int x, int y, int w, int h, const char *name) :
	Cell(x, y, w, h, name, OBJ_EMPTY) {}

void EmptyCell::click(Fl_Widget *w, void *u)
{
	std::cout << "I'm EmptyCell\n";
}

/* RoundObj */

Array<int> RoundObj::takenLocations = Array<int>();

RoundObj::RoundObj(int x, int y, int w, int h, const char *name, short obj) :
	Cell(x, y, w, h, name, obj), nextLocation(-1), newDirection(-1) {}

void RoundObj::chooseDirection(int index, int n)
{
	short row = index / n,
		  column = index % n,
		  newDirection = std::rand() % 8;
	switch(newDirection) {
		case TOP_LEFT:
		case LEFT:
		case BOTTOM_LEFT:
			--column;
			break;
		case TOP_RIGHT:
		case RIGHT:
		case BOTTOM_RIGHT:
			++column;
			break;
	}
	switch(newDirection) {
		case TOP_LEFT:
		case TOP:
		case TOP_RIGHT:
			++row;
			break;
		case BOTTOM_LEFT:
		case BOTTOM:
		case BOTTOM_RIGHT:
			--row;
			break;
	}
	if (column < 0 || column >= n || row < 0 || row >= n) {
		row = index / n;
		column = index % n;
	}
	nextLocation = row * n + column;
	takenLocations.insertAtEnd(nextLocation);
}
