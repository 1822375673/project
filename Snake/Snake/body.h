
#ifndef __BODY_H_
#define __BODY_H_

#include <graphics.h>
#include <conio.h>
#include <stdio.h>
 
class Body
{
	int x;
	int y;
	int width;
	COLORREF color;
	int stat;
	Body *next;
public:
	enum Statu{ON, OFF};
public:
	Body(int x = 0, int y = 0, int width = 10, COLORREF color = WHITE, Body *next = NULL, int stat = ON);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	void setColor(COLORREF color);
	COLORREF getColor();
	void setNext(Body *next);
	Body *getNext();
	void setStat(int stat);
	int getStat();
	void update();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
};
#endif
