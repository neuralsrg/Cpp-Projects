#include "classes.h"
#include <cassert>

// #define NDEBUG

/* Definitions of Classes functions */

/* Cell */

//Array<SellInfo> Cell::field;

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

void Cell::fillField(std::shared_ptr<Cell> ptr_to_me)
{
	field.insertAtEnd(ptr_to_me);
}

void Cell::boomBubblePretenders(int n, int min_pret)
{
	for (int sellIndex = 0; sellIndex < field.getLength(); ++sellIndex) {
		if (field[sellIndex].pretendList.getLength() <= min_pret)
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
				std::make_shared<EmptyCell>(bubble);
			field[sellIndex].pretendList.remove(pretIndex);
		}
	}
}

void Cell::moveObjects(int n)
{
	int cellIndex = 0;
	while (cellIndex < field.getLength()) {
		if (field[cellIndex].owner->objType != OBJ_EMPTY ||
				field[cellIndex].pretendList.getLength() != 1) {
			++cellIndex;
			continue;
		}
		std::shared_ptr<Cell> obj =
			field[cellIndex].pretendList[0];
		int objCurrentIndex = obj->getCurrentIndex(cellIndex, n);
		field[objCurrentIndex].owner =
			std::make_shared<EmptyCell>(obj);
		field[cellIndex].owner = obj;
		field[cellIndex].pretendList.erase();
		cellIndex = 0;
	}
}

void Cell::destroyBubblesLeft(int n)
{
	for (int cellIndex = 0; cellIndex < field.getLength(); ++cellIndex) {
		// TODO Finish this..
	}
}

/* EmptyCell */

EmptyCell::EmptyCell(int x, int y, int w, int h) :
	Cell(x, y, w, h, OBJ_EMPTY) { color(CLR_BTN_EMPTY); }

EmptyCell::EmptyCell(const std::shared_ptr<Cell> &c) :
	Cell(c->x(), c->y(), c->w(), c->h(), OBJ_EMPTY) {}

void EmptyCell::click(Fl_Widget *w, void *u)
{
	std::cout << "I'm EmptyCell\n";
	int index = 0;
	while (((Scene *)u)->cells[index].get() != w)
		++index;
	std::cout << index << std::endl;
}

/* RoundObj */

RoundObj::RoundObj(int x, int y, int w, int h, short obj) :
	Cell(x, y, w, h, obj), direction(-1) {}

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

/* Scene */

Scene::Scene(int n) : Fl_Window(2 * S_STRIDE + n * S_BUTTON_W,
		2 * S_STRIDE + n * S_BUTTON_H, "Bubbles & Balloons")//, cells(n * n)
{
	begin();
	color(FL_GRAY);
	//sellsCroup = new Fl_Group(S_STRIDE, S_STRIDE, n * S_BUTTON_W, n * S_BUTTON_H);
	//sellsCroup->box(FL_FLAT_BOX);
	//sellsCroup->color(FL_CYAN);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cells[i * n + j] = std::make_shared<EmptyCell>(S_STRIDE + j * S_BUTTON_W,
					S_STRIDE + i * S_BUTTON_H, S_BUTTON_W, S_BUTTON_H);
			cells[i * n + j]->box(FL_FLAT_BOX);
			cells[i * n + j]->setCallback(this);
		}
	}
	end();
	show();
}

Scene::~Scene()
{
	cells.erase();
	//delete sellsCroup;
}

