#include "classes.h"
#include <cassert>

// #define NDEBUG

/* Definitions of Classes functions */

/* Cell */

Array<SellInfo> Cell::field;

Cell::Cell(int x, int y, int w, int h, short ot) :
	Fl_Button(x, y, w, h, ""), objType(ot), btnParams{x, y, w, h} {}

void Cell::setCallback(Scene *sc)
{
	callback(callback_cell, sc);
}

void Cell::callback_cell(Fl_Widget *w, void *u)
{
	((Cell *)w)->click(w, u);
}

void Cell::fillField(std::shared_ptr<Cell> ptr_to_me)
{
	field.insertAtEnd(ptr_to_me);
}

void Cell::boomBubblePretenders(int n)
{
	for (int sellIndex = 0; sellIndex < field.getLength(); ++sellIndex) {
		if (field[sellIndex].pretendList.getLength() <= 1)
			continue;
		int pretIndex = 0;
		while (pretIndex < field[sellIndex].pretendList.getLength()) {
			if (field[sellIndex].pretendList[pretIndex]->objType != OBJ_BUBBLE) {
				++pretIndex;
				continue;
			}
			std::shared_ptr<Cell> bubble =
				field[sellIndex].pretendList[pretIndex];
			int bubblesCurrentIndex = bubble->getCurrentIndex(sellIndex, n);
			field[bubblesCurrentIndex].owner =
				std::make_shared<EmptyCell>(bubble->btnParams);
			field[sellIndex].pretendList.remove(pretIndex);
		}
	}
}

void Cell::moveObjects(int n)
{
	int sellIndex = 0;
	while (sellIndex < field.getLength()) {
		if (field[sellIndex].owner->objType != OBJ_EMPTY ||
				field[sellIndex].pretendList.getLength() != 1) {
			++sellIndex;
			continue;
		}
		std::shared_ptr<Cell> obj =
			field[sellIndex].pretendList[0];
		int objCurrentIndex = obj->getCurrentIndex(sellIndex, n);
		field[objCurrentIndex].owner =
			std::make_shared<EmptyCell>(obj->btnParams);
		field[sellIndex].owner = obj;
		field[sellIndex].pretendList.erase();
		sellIndex = 0;
	}
}

/* EmptyCell */

EmptyCell::EmptyCell(int x, int y, int w, int h) :
	Cell(x, y, w, h, OBJ_EMPTY) {}

EmptyCell::EmptyCell(int btnParams[4]) :
	Cell(btnParams[0], btnParams[1], btnParams[2], btnParams[3], OBJ_EMPTY) {}

void EmptyCell::click(Fl_Widget *w, void *u)
{
	std::cout << "I'm EmptyCell\n";
}

/* RoundObj */

RoundObj::RoundObj(int x, int y, int w, int h, short obj) :
	Cell(x, y, w, h, obj), direction(-1) {}

/*
RoundObj::RoundObj(int btnParams[4], short obj) :
	Cell(btnParams[0], btnParams[1], btnParams[2], btnParams[3], obj), 
	direction(-1) {}
*/

int RoundObj::getCurrentIndex(int newIndex, int n) const
{
	short row = newIndex / n, column = newIndex % n;
	switch(direction) {
		case TOP_LEFT:
		case LEFT:
		case BOTTOM_LEFT:
			++column;
			break;
		case TOP_RIGHT:
		case RIGHT:
		case BOTTOM_RIGHT:
			--column;
			break;
	}
	switch(direction) {
		case TOP_LEFT:
		case TOP:
		case TOP_RIGHT:
			--row;
			break;
		case BOTTOM_LEFT:
		case BOTTOM:
		case BOTTOM_RIGHT:
			++row;
			break;
	}
	assert(row >= 0 && column > 0 && "getCurrentIndex computed wrong index!");
	return row * n + column;
}

void RoundObj::chooseLocation(int index, int n, std::shared_ptr<Cell> ptr_to_me)
{
	direction = std::rand() % 8;
	short row = index / n, column = index % n;

	switch(direction) {
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
	switch(direction) {
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
	int nextLocation = row * n + column;
	if (nextLocation == index)
		return;
	assert(nextLocation >= 0 && "Bad location set!");
	field[nextLocation].pretendList.insertAtEnd(ptr_to_me);
	std::cout << "New pretend attached to " << nextLocation << std::endl;
}

/* Bubble */

Bubble::Bubble(int x, int y, int w, int h) :
	RoundObj(x, y, w, h, OBJ_BUBBLE) {}

void Bubble::click(Fl_Widget *w, void *u)
{
	std::cout << "This is Bubble\n";
}
