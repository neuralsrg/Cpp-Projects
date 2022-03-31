#include "classes.h"
#include <cassert>

// #define NDEBUG

/* Definitions of Classes functions */

/* Cell */

Cell::Cell(int x, int y, int w, int h, short ot) :
	Fl_Button(x, y, w, h, ""), objType(ot) {}

void Cell::setCallback(Scene *sc)
{
	callback(callback_cell, sc);
}

void Cell::callback_cell(Fl_Widget *w, void *u)
{
	((Cell *)w)->click(w, u);
}

/* EmptyCell */

EmptyCell::EmptyCell(int x, int y, int w, int h) :
	Cell(x, y, w, h, OBJ_EMPTY) {}

void EmptyCell::click(Fl_Widget *w, void *u)
{
	std::cout << "I'm EmptyCell\n";
}

/* RoundObj */

Array<int> RoundObj::takenLocations = Array<int>();

RoundObj::RoundObj(int x, int y, int w, int h, short obj) :
	Cell(x, y, w, h, obj), nextLocation(-1), newDirection(-1) {}

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
	assert(nextLocation >= 0 && "Bad location set!");
	takenLocations.insertAtEnd(nextLocation);
}

void RoundObj::checkAbilityToMove(Array<RoundObj *> *arr)
{
	assert(takenLocations.count(nextLocation) > 0 && "Location not found!");
	if (takenLocations.count(nextLocation) == 1)
		return;
	arr->insertAtEnd(this);
}

void RoundObj::doneMoving() { takenLocations.erase(); }

/* Bubble */

Bubble::Bubble(int x, int y, int w, int h) :
	RoundObj(x, y, w, h, OBJ_BUBBLE) {}

void Bubble::click(Fl_Widget *w, void *u)
{
	std::cout << "This is Bubble\n";
}

short Bubble::fixIssue()
{
	return MOVING_DELETED;
}
