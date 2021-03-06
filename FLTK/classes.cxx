#include "classes.h"
#include <cassert>

#define NDEBUG

/* Definitions of Classes functions */

/* Cell */

Array<SellInfo> Cell::field;

Cell::Cell(int x, int y, int w, int h, short ot) :
	Fl_Button(x, y, w, h) {}

void Cell::setCallback(Scene *sc)
{
	callback(callback_cell, sc);
}

void Cell::callback_cell(Fl_Widget *w, void *u)
{
	((Cell *)w)->click(w, u);
}

void Cell::boomBubblePretenders(int n, Scene *sc)
{
	for (int cellIndex = 0; cellIndex < field.getLength(); ++cellIndex) {
		if (field[cellIndex].pretendList.getLength() <= 1)
			continue;
		int pretIndex = 0;
		while (pretIndex < field[cellIndex].pretendList.getLength()) {
			int pret = field[cellIndex].pretendList[pretIndex];
			if (sc->cells[pret]->getVisible() != OBJ_BUBBLE) {
				++pretIndex;
				continue;
			}
			sc->cells[pret]->switchBtn(OBJ_EMPTY);
			field[cellIndex].pretendList.remove(pretIndex);
		}
	}
}

void Cell::moveObjects(int n, Scene *sc)
{
	int cellIndex = 0;
	while (cellIndex < field.getLength()) {
		if (sc->cells[cellIndex]->getVisible() != OBJ_EMPTY ||
				field[cellIndex].pretendList.getLength() != 1) {
			++cellIndex;
			continue;
		}
		int pret = field[cellIndex].pretendList[0];
		short pretType = sc->cells[pret]->getVisible();
		sc->cells[pret]->switchBtn(OBJ_EMPTY);
		sc->cells[cellIndex]->switchBtn(pretType);
		field[cellIndex].pretendList.erase();
		cellIndex = 0;
	}
}

void Cell::destroyBubblesLeft(int n, Scene *sc)
{
	for (int cellIndex = 0; cellIndex < n; ++cellIndex) {
		if (sc->cells[cellIndex]->getVisible() == OBJ_BUBBLE
				&& field[cellIndex].pretendList.getLength() > 0) {
			int nextLocation = sc->cells[cellIndex]->getIndex(cellIndex, n);
			if (nextLocation != cellIndex)
				field[nextLocation].pretendList.erase();
			sc->cells[cellIndex]->switchBtn(OBJ_EMPTY);
			int pret = field[cellIndex].pretendList[0];
			if (sc->cells[pret]->getVisible() == OBJ_BUBBLE) {
				sc->cells[pret]->switchBtn(OBJ_EMPTY);
				field[cellIndex].pretendList.erase();
			}
		} else if (field[cellIndex].pretendList.getLength() != 1)
			continue;
		if (sc->cells[cellIndex]->getVisible() != OBJ_EMPTY &&
				sc->cells[field[cellIndex].pretendList[0]]->getVisible()
				== OBJ_BUBBLE) {
			sc->cells[field[cellIndex].pretendList[0]]->switchBtn(OBJ_EMPTY);
			field[cellIndex].pretendList.erase();
		}
	}
}

void Cell::balloonTrials(int n, Scene *sc, int trials)
{
	for (int trial = 0; trial < trials; ++trial) {
		Array<Array<int>> tmp(n);
		for (int cellIndex = 0; cellIndex < n; ++cellIndex) {
			if ((sc->cells[cellIndex]->getVisible() == OBJ_BALLOON &&
					field[cellIndex].pretendList.getLength() > 0) || 
					(sc->cells[cellIndex]->getVisible() == OBJ_EMPTY && 
					field[cellIndex].pretendList.getLength() > 0)) {
				while (field[cellIndex].pretendList.getLength()) {
					int pret = field[cellIndex].pretendList[0];
					field[cellIndex].pretendList.remove(0);
					short curDir = sc->cells[pret]->direction;
					short newDir = curDir == TOP_LEFT ? BOTTOM_RIGHT : 
								   curDir == TOP ? BOTTOM :
								   curDir == TOP_RIGHT ? BOTTOM_LEFT : 
								   curDir == RIGHT ? LEFT : 
								   curDir == BOTTOM_RIGHT ? TOP_LEFT : 
								   curDir == BOTTOM ? TOP : 
								   curDir == BOTTOM_LEFT ? TOP_RIGHT : 
								   curDir == LEFT ? RIGHT : -1;
					assert(newDir >= 0 && "Wrong NewDir");
					sc->cells[pret]->direction = newDir;
					int nextLocation = sc->cells[pret]->getIndex(pret, n);
					if (nextLocation != pret && nextLocation != cellIndex)
						tmp[nextLocation].insertAtEnd(pret);
				}
			}
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < tmp[i].getLength(); ++j)
				field[i].pretendList.insertAtEnd(tmp[i][j]);
			tmp[i].erase();
		}
		tmp.erase();
		destroyBubblesLeft(n, sc);
		moveObjects(n, sc);
	}
}

void Cell::move(Scene *sc)
{
	int n = sc->cells.getLength();
	for (int cellIndex = 0; cellIndex < n; ++cellIndex)
		sc->cells[cellIndex]->chooseLocation(cellIndex, n);
	boomBubblePretenders(n, sc);
	moveObjects(n, sc);
	destroyBubblesLeft(n, sc);
	moveObjects(n, sc);
	balloonTrials(n, sc, 3);
	for (int i = 0; i < field.getLength(); ++i)
		field[i].pretendList.erase();
}

void winError()
{
	Fl_Window *ew = new Fl_Window(200, 200, "Error!");
	ew->begin();
	Fl_Box *b = new Fl_Box(0, 0, 200, 200);
	b->label("Error!");
	b->labelfont(FL_BOLD);
	ew->end();
	ew->show();
}

/* EmptyCell */

EmptyCell::EmptyCell(int x, int y, int w, int h) :
	Cell(x, y, w, h, OBJ_EMPTY)
{
	color(CLR_BTN_EMPTY);
	color2(CLR2_BTN_EMPTY);
}

void EmptyCell::click(Fl_Widget *w, void *u)
{
	Scene *su = (Scene *) u;
	int index = 0;
	while (su->cells[index]->btns[OBJ_EMPTY].get() != w)
		++index;
	short state = su->getState();
	switch (state) {
		case -1:
			return;
		case CTRL_CREATE_BUBBLE:
			su->cells[index]->switchBtn(OBJ_BUBBLE);
			return;
		case CTRL_CREATE_BALLOON:
			su->cells[index]->switchBtn(OBJ_BALLOON);
			Fl::redraw();
			su->cells[index]->btns[OBJ_BALLOON]->redraw();
			return;
		case CTRL_DESTROY_BUBBLE:
		case CTRL_DESTROY_BALLOON:
			winError();
			return;
	}
	assert(!"EmptyCell click handler got strange state from radio button!");
}

/* RoundObj */

RoundObj::RoundObj(int x, int y, int w, int h, short obj) :
	Cell(x, y, w, h, obj) {}

Fl_JPEG_Image* RoundObj::resizeObj(Fl_JPEG_Image *img, int button_w, int button_h)
{
	if (img->w() > button_w || img->h() > button_h) {
		Fl_Image *temp;
		if (img->w() > img->h()) {
			temp = img->copy(button_w, button_h * img->h() / img->w());
		} else {
			temp = img->copy(button_w * img->w() / img->h(), button_h);
		}
		delete img;
		img = (Fl_JPEG_Image *) temp;
	}
	return img;
}	

/* Bubble */

Bubble::Bubble(int x, int y, int w, int h) :
	RoundObj(x, y, w, h, OBJ_BUBBLE)
{
	Fl_JPEG_Image *img = new Fl_JPEG_Image("./images/bubble.jpg");
	if (!img) {
		return; 
	}
	img = RoundObj::resizeObj(img, w, h);
	box(FL_FLAT_BOX);
	color(CLR_BTN_EMPTY);
	image(img);
}

void Bubble::click(Fl_Widget *w, void *u)
{
	Scene *su = (Scene *) u;
	int index = 0;
	while (su->cells[index]->btns[OBJ_BUBBLE].get() != w)
		++index;
	short state = su->getState();
	switch (state) {
		case -1:
			return;
		case CTRL_DESTROY_BUBBLE:
			su->cells[index]->switchBtn(OBJ_EMPTY);
			return;
		case CTRL_DESTROY_BALLOON:
		case CTRL_CREATE_BUBBLE:
		case CTRL_CREATE_BALLOON:
			winError();
			return;
	}
	assert(!"EmptyCell click handler got strange state from radio button!");
}

/* Balloon */

Balloon::Balloon(int x, int y, int w, int h) :
	RoundObj(x, y, w, h, OBJ_BALLOON)
{
	Fl_JPEG_Image *img = new Fl_JPEG_Image("./images/balloon.jpg");
	if (!img) {
		return; 
	}
	img = RoundObj::resizeObj(img, w, h);
	box(FL_FLAT_BOX);
	color(CLR_BTN_EMPTY);
	image(img);
}

void Balloon::click(Fl_Widget *w, void *u)
{
	Scene *su = (Scene *) u;
	int index = 0;
	while (su->cells[index]->btns[OBJ_BALLOON].get() != w)
		++index;
	short state = su->getState();
	switch (state) {
		case -1:
			return;
		case CTRL_DESTROY_BALLOON:
			su->cells[index]->switchBtn(OBJ_EMPTY);
			return;
		case CTRL_DESTROY_BUBBLE:
		case CTRL_CREATE_BUBBLE:
		case CTRL_CREATE_BALLOON:
			winError();
			return;
	}
	assert(!"EmptyCell click handler got strange state from radio button!");
}

/* TripleBtn */

TripleBtn::TripleBtn(int x, int y, float k, Scene *sc) : btns(3)
{
	btns[OBJ_EMPTY] = std::make_shared<EmptyCell>(x, y, k * S_BUTTON_W, k * S_BUTTON_H);
	btns[OBJ_BUBBLE] = std::make_shared<Bubble>(x, y, k * S_BUTTON_W, k * S_BUTTON_H);
	btns[OBJ_BALLOON] = std::make_shared<Balloon>(x, y, k * S_BUTTON_W, k * S_BUTTON_H);

	for (int i = 0; i < btns.getLength(); ++i) {
		btns[i]->box(FL_FLAT_BOX);
		btns[i]->setCallback(sc);
		if (i != OBJ_EMPTY)
			btns[i]->hide();
	}
}

int TripleBtn::getIndex(int index, int n) const
{
	n = (int)sqrt(n);
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
	assert(row >= 0 && column >= 0 && "getCurrentIndex computed wrong index!");
	return row * n + column;
}

void TripleBtn::chooseLocation(int index, int n)
{
	if (getVisible() == OBJ_EMPTY)
		return;
	direction = std::rand() % 8;
	int nextLocation = getIndex(index, n);
	if (nextLocation == index)
		return;
	assert(nextLocation >= 0 && "Bad location set!");
	Cell::field[nextLocation].pretendList.insertAtEnd(index);
}

void TripleBtn::switchBtn(short btn)
{
	for (int i = 0; i < btns.getLength(); ++i) {
		btns[i]->hide();
	}
	btns[btn]->set_visible();
}

short TripleBtn::getVisible()
{
	for (int i = 0; i < btns.getLength(); ++i) {
		if (btns[i]->visible_r())
			return i;
	}
	assert(false && "No active button!");
	return -1;
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

Scene::Scene(int n, float k) :
	Fl_Window(3 * S_STRIDE + k * n * S_BUTTON_W + k * RB_W,
			2 * S_STRIDE + k * n * S_BUTTON_H, "Bubbles & Balloons"),
	Controls(),
	cells(n * n)
{
	Cell::field.reallocate(n * n);
	begin();

	Fl_JPEG_Image *img = new Fl_JPEG_Image("./images/logo.jpg");
	icon(img);

	color(FL_GRAY);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cells[i * n + j] = std::make_shared<TripleBtn>(S_STRIDE + k * j * S_BUTTON_W,
					S_STRIDE + k * i * S_BUTTON_H, k, this);
		}
	}
	int x = 2 * S_STRIDE + k * n * S_BUTTON_W, y = S_STRIDE; 
	for (int i = 0; i < 4; ++i) {
		rb[i] = new Fl_Radio_Round_Button(x, y, k * RB_W, k * n * S_BUTTON_H / 5,
				RB_NAMES[i]);
		rb[i]->labelsize(rb[i]->labelsize() * k);
		y += k * n * S_BUTTON_H / 5;
	}
	nextStepBtn = new Fl_Button(x, y, k * RB_W, k * n * S_BUTTON_H / 5, "@>>");
	nextStepBtn->labelsize(nextStepBtn->labelsize() * k);
	nextStepBtn->color(FL_GREEN);
	nextStepBtn->labelfont(FL_BOLD);
	nextStepBtn->callback(nsCallback, this);
	end();
	show();
}

void Scene::nsCallback(Fl_Widget *w, void *u)
{
	Cell::move((Scene *) u);
}

Scene::~Scene()
{
	cells.erase();
}
