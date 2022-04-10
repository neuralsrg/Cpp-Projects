#ifndef CLASSES_H_SENTRY
#define CLASSES_H_SENTRY

#include "constants.h"
#include "array.h"
#include <iostream>
#include <cmath>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Radio_Round_Button.H>
#include <FL/Fl_JPEG_Image.H>

class Cell;
class RoundObj;
class Scene;

class SellInfo
{
public:

	Array<int> pretendList;

	SellInfo() : pretendList() {}
	SellInfo(int l) : pretendList(l) {}
	~SellInfo() { pretendList.erase(); }
};

class Cell : public Fl_Button
{
protected:

	Cell(int, int, int, int, short);
	virtual void click(Fl_Widget *, void *) = 0;

public:

	void setCallback(Scene *);

	static void callback_cell(Fl_Widget *w, void *u);
	static Array<SellInfo> field;

	static void boomBubblePretenders(int, Scene *);
	static void moveObjects(int, Scene *);
	static void destroyBubblesLeft(int, Scene *);
	//moveObjects again
	static void balloonTrials(int, Scene *, int = 3);

	static void move(Scene *);

	virtual ~Cell() {}
};

void winError();

class EmptyCell : public Cell
{
protected:

	void click(Fl_Widget *, void *) override;

public:
	
	EmptyCell(int, int, int, int);
	virtual ~EmptyCell() {}
};

class RoundObj : public Cell
{
protected:

	RoundObj(int, int, int, int, short);

public:

	static Fl_JPEG_Image* resizeObj(Fl_JPEG_Image *, int, int);
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

class Balloon : public RoundObj
{
protected:
	
	void click(Fl_Widget *, void *) override;

public:
	
	Balloon(int, int, int, int);
	virtual ~Balloon() {}
};

class TripleBtn
{
public:

	Array<std::shared_ptr<Cell>> btns;
	short direction;

	TripleBtn(int, int, float, Scene *);

	int getIndex(int, int) const;
	void chooseLocation(int, int);

	void switchBtn(short);
	short getVisible();
	~TripleBtn() { btns.erase(); }
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
	Fl_Button *nextStepBtn;

public:

	Array<std::shared_ptr<TripleBtn>> cells;

	Scene(int, float);
	static void nsCallback(Fl_Widget *, void *);
	int run() const { return Fl::run(); }
	virtual	~Scene();
};

#endif
