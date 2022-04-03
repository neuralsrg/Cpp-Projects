#include "classes.h"
#include <cassert>

// #define NDEBUG

/* Definitions of Classes functions */

/* Cell */

Array<SellInfo> Cell::field;

Cell::Cell(int x, int y, int w, int h, short ot) :
	Fl_Button(x, y, w, h), objType(ot) {}

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
	for (int cellIndex = 0; cellIndex < field.getLength(); ++cellIndex) {
		if (field[cellIndex].pretendList.getLength() <= 1)
			continue;
		int pretIndex = 0;
		while (pretIndex < field[cellIndex].pretendList.getLength()) {
			if (field[cellIndex].pretendList[pretIndex]->objType != OBJ_BUBBLE) {
				++pretIndex;
				continue;
			}
			std::shared_ptr<Cell> bubble =
				field[cellIndex].pretendList[pretIndex];
			int bubblesCurrentIndex = bubble->getIndex(cellIndex, n, false);
			field[bubblesCurrentIndex].owner =
				std::make_shared<EmptyCell>(bubble);
			field[cellIndex].pretendList.remove(pretIndex);
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
		int objCurrentIndex = obj->getIndex(cellIndex, n, false);
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
		if (field[cellIndex].owner->objType == OBJ_BUBBLE
				&& field[cellIndex].pretendList.getLength() > 0) {
			std::shared_ptr<Cell> bubble =
				field[cellIndex].owner;
			int nextLocation = bubble->getIndex(cellIndex, n, true);
			field[nextLocation].pretendList.erase();
			field[cellIndex].owner = std::make_shared<EmptyCell>(bubble);
			if (field[cellIndex].pretendList[0]->objType == OBJ_BUBBLE) {
				std::shared_ptr<Cell> bubble =
					field[cellIndex].pretendList[0];
				int currentLocation = bubble->getIndex(cellIndex, n, false);
				field[currentLocation].owner = 
					std::make_shared<EmptyCell>(bubble);
				field[cellIndex].pretendList.erase();
			}
		}
		else if (field[cellIndex].owner->objType != OBJ_EMPTY &&
				field[cellIndex].pretendList.getLength() == 1 &&
				field[cellIndex].pretendList[0]->objType == OBJ_BUBBLE) {
			std::shared_ptr<Cell> bubble =
				field[cellIndex].pretendList[0];
			int currentLocation = bubble->getIndex(cellIndex, n, false);
			field[cellIndex].pretendList.erase();
			field[currentLocation].owner = std::make_shared<EmptyCell>(bubble);
		}
	}
}

void Cell::balloonTrials(int n, int trials)
{
	for (int trial = 0; trial < trials; ++trial) {
		for (int cellIndex = 0; cellIndex < n; ++cellIndex) {
			if ((field[cellIndex].owner->objType == OBJ_BALLOON &&
					field[cellIndex].pretendList.getLength() > 0) || 
					(field[cellIndex].owner->objType == OBJ_EMPTY && 
					field[cellIndex].pretendList.getLength() > 0)) {
				while (field[cellIndex].pretendList.getLength()) {
					assert(field[cellIndex].pretendList[0]->objType == OBJ_BALLOON &&
							"Not Balloons in pretendList");
					std::shared_ptr<Cell> balloon = field[cellIndex].pretendList[0];
					int currentLocation = balloon->getIndex(cellIndex, n, false);
					field[cellIndex].pretendList.remove(0);
					short curDir = balloon->getDirection();
					short newDir = curDir == TOP_LEFT ? BOTTOM_RIGHT : 
								   curDir == TOP ? BOTTOM :
								   curDir == TOP_RIGHT ? BOTTOM_LEFT : 
								   curDir == RIGHT ? LEFT : 
								   curDir == BOTTOM_RIGHT ? TOP_LEFT : 
								   curDir == BOTTOM ? TOP : 
								   curDir == BOTTOM_LEFT ? TOP_RIGHT : 
								   curDir == LEFT ? RIGHT : -1;
					assert(newDir >= 0 && "Wrong NewDir");
					balloon->setDirection(newDir);
					int nextLocation = balloon->getIndex(currentLocation, n, true);
					field[nextLocation].pretendList.insertAtEnd(balloon);
				}
			}
		}
		destroyBubblesLeft(n);
		moveObjects(n);
	}
}

void Cell::move(Scene *sc)
{
	int n = sc->cells.getLength();
	for (int cellIndex = 0; cellIndex < n; ++cellIndex)
		sc->cells[cellIndex]->fillField(sc->cells[cellIndex]);
	for (int cellIndex = 0; cellIndex < n; ++cellIndex)
		sc->cells[cellIndex]->chooseLocation(cellIndex, n, sc->cells[cellIndex]);
	boomBubblePretenders(n);
	moveObjects(n);
	destroyBubblesLeft(n);
	moveObjects(n);
	balloonTrials(n, 3);

	for (int cellIndex = 0; cellIndex < n; ++cellIndex)
		sc->cells[cellIndex] = field[cellIndex].owner;

	while (field.getLength()) {
		field[0].pretendList.erase();
		field.remove(0);
	}
}

/* EmptyCell */

EmptyCell::EmptyCell(int x, int y, int w, int h) :
	Cell(x, y, w, h, OBJ_EMPTY)
{
	color(CLR_BTN_EMPTY);
	color2(CLR2_BTN_EMPTY);
}

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

int RoundObj::getIndex(int index, int n, bool generate) const
{
	short row = index / n, column = index % n;
	switch(direction) {
		case TOP_LEFT:
		case LEFT:
		case BOTTOM_LEFT:
			column = generate ? column - 1 : column + 1;
			break;
		case TOP_RIGHT:
		case RIGHT:
		case BOTTOM_RIGHT:
			column = generate ? column + 1 : column - 1;
			break;
	}
	switch(direction) {
		case TOP_LEFT:
		case TOP:
		case TOP_RIGHT:
			row = generate ? row + 1 : row - 1;
			break;
		case BOTTOM_LEFT:
		case BOTTOM:
		case BOTTOM_RIGHT:
			row = generate ? row - 1 : row + 1;
			break;
	}
	if (column < 0 || column >= n || row < 0 || row >= n) {
		row = index / n;
		column = index % n;
	}
	assert(row >= 0 && column >= 0 && "getCurrentIndex computed wrong index!");
	return row * n + column;
}

void RoundObj::chooseLocation(int index, int n, std::shared_ptr<Cell> ptr_to_me)
{
	direction = std::rand() % 8;
	int nextLocation = getIndex(index, n, true);
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

/* Balloon */

Balloon::Balloon(int x, int y, int w, int h) :
	RoundObj(x, y, w, h, OBJ_BALLOON) {}

void Balloon::click(Fl_Widget *w, void *u)
{
	std::cout << "This is Balloon\n";
}

/* Controls */

short Controls::getState() const
{
	for (int i = 0; i < 4; ++i)
		if (rb[i]->value())
			return i;
	return -1;
}

/* Scene */

extern const char* const RB_NAMES[4];

Scene::Scene(int n) :
	Fl_Window(3 * S_STRIDE + n * S_BUTTON_W + RB_W,
			2 * S_STRIDE + n * S_BUTTON_H, "Bubbles & Balloons"),
	Controls(),
	cells(n * n)
{
	begin();
	color(FL_GRAY);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cells[i * n + j] = std::make_shared<EmptyCell>(S_STRIDE + j * S_BUTTON_W,
					S_STRIDE + i * S_BUTTON_H, S_BUTTON_W, S_BUTTON_H);
			cells[i * n + j]->box(FL_FLAT_BOX);
			cells[i * n + j]->setCallback(this);
		}
	}
	int x = 2 * S_STRIDE + n * S_BUTTON_W, y = S_STRIDE; 
	ctrl_gr = new Fl_Group(x, y, RB_W, n * S_BUTTON_H * 4 / 5);
	ctrl_gr->color(FL_RED);
	for (int i = 0; i < 4; ++i) {
		rb[i] = new Fl_Radio_Round_Button(x, y, RB_W, n * S_BUTTON_H / 5, RB_NAMES[i]);
		y += n * S_BUTTON_H / 5;
	}
	ctrl_gr->end();
	nextStepBtn = new Fl_Button(x, y, RB_W, n * S_BUTTON_H / 5, "@>>");
	nextStepBtn->color(FL_GREEN);
	nextStepBtn->labelfont(FL_BOLD);
	end();
	show();
}

Scene::~Scene()
{
	cells.erase();
}

