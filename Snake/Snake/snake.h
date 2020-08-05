#ifndef __SANKE_H_
#define __SNAKE_H_
#include "body.h"
 
#ifndef _SCREEN_SIZE_
#define _SCREEN_SIZE_
#define WIDTH 640
#define HEIGHT 480
#endif
 
class Snake
{
	Body *head;
	int dir;
	int foodX;
	int foodY;
	enum Direction{UP, DOWN, LEFT, RIGHT};
	char map[48][65];  //ע���ͼ�ļ���һ�����з�
public:
	Snake(int x = 100, int y =  50, int dir = DOWN);
	void update();
	void setDir(int dir);
	void move();
	void start();
	void getFoodLocation(int &x, int &y);
	void createFood();
	bool isTouchFood();    //�ж��Ƿ���������
	void eatFoodAddBody(); // ��ʳ�ﳤ����
	bool isGameOver();
	void initMap();
	bool isTouchMap();
};
#endif
