#include <iostream>
#include <graphics.h>
#include <conio.h>
#include "stdafx.h"
#include "body.h"
#include "Snake.h"
 
#ifndef _SCREEN_SIZE_
#define _SCREEN_SIZE_
#define WIDTH 640
#define HEIGHT 480
#endif
 
using namespace std;
 
int main()
{
	initgraph(640, 480, SHOWCONSOLE);
 
	Snake snake;
	snake.initMap();
	snake.start();
	
	_getch();
	return 0;

}