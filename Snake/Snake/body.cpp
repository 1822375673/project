#include "body.h"
 
Body::Body(int x, int y, int width, COLORREF color, Body *next, int stat)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->color = color;
	this->next = next;
	this->stat = stat;
}
 
void Body::setX(int x)
{
	this->x = x;
}
void Body::setY(int y)
{
	this->y = y;
}
int Body::getX()
{
	return x;
}
int Body::getY()
{
	return y;
}
void Body::setColor(COLORREF color)
{
	this->color = color;
}
COLORREF Body::getColor()
{
	return color;
}
void Body::setNext(Body *next)
{
	this->next = next;
}
Body* Body::getNext()
{
	return next;
}
void Body::setStat(int stat)
{
	this->stat = stat;
}
int Body::getStat()
{
	return stat;
}
 
void Body::update()
{
	if (stat == ON)
	{
		setfillcolor(WHITE);
		setlinecolor(RED);
	}
	else
	{
		setfillcolor(BLACK);
		setlinecolor(BLACK);
	}
	fillrectangle(x, y, x+ width, y + width);
}
void Body::moveLeft()
{
	x -= 10;
}
void Body::moveRight()
{
	x += 10;
}
 
void Body::moveUp()
{
 
	y -= 10;
}
void Body::moveDown()
{
	y += 10;
}