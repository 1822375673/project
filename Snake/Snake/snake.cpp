
#include "Snake.h"
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
 
Snake::Snake(int x, int y, int dir)
{
	head = new Body(x, y);
	head->setNext(new Body(x,y-10));
	this->dir = dir;
	foodX = -1;
	foodY = -1;
}
 
void Snake::start()
{
	update();
	int ch = 0;
 
	createFood(); // 初始食物
	while (1)
	{
		if (_kbhit())
		{
			ch = _getch();     // 一个方向键要用两个getch才能获取完
			if (ch == 0xe0)   //如果高位相等
			{
				ch = _getch(); //那么再获取一个
				switch (ch)
				{
				case  0x004b: if (dir != RIGHT) dir = LEFT; break; // 设置蛇的移动方向
				case  0x004d: if (dir != LEFT) dir = RIGHT; break;
				case  0x0048: if (dir != DOWN) dir = UP;  break;
				case  0x0050: if (dir != UP)   dir = DOWN; break;
				}
			}
			//move();
		}
		move();
		if (isTouchFood())
		{
			eatFoodAddBody();  //长身体
			createFood(); // 产生新的食物
		}
		Sleep(100);
	}
}
 
void Snake::setDir(int dir)
{
	this->dir = dir;
}
 
void Snake::update()
{
	Body *p = head;
	do
	{
		p->update();
		p = p->getNext();
	} while (p != NULL);
}
 
 
void Snake::move()
{
	Body *p = head;
	Body *newTail = NULL;
 
	//找到蛇靠近尾部的那个节点
	while (p->getNext()->getNext()!= NULL)
	{
		p = p->getNext();
	}
	newTail = p;
	p = p->getNext();
	newTail->setNext(NULL);//将新节点的下一个节点置空
 
	p->setStat(p->OFF); // 将原尾巴擦掉
	p->update();
   
	p->setX(head->getX());
	p->setY(head->getY());
	p->setNext(head->getNext());
 
	head->setNext(p);
	//更新蛇的头部
	switch (dir)
	{
	case LEFT:  head->moveLeft();   break;
	case UP:    head->moveUp();     break;
	case DOWN:  head->moveDown();   break;
	case RIGHT:  head->moveRight(); break;
	}
 
	if (isGameOver())
	{
		LOGFONT f;
		gettextstyle(&f);                     // 获取当前字体设置
		f.lfHeight = 48;                      // 设?米痔甯叨任? 48
		_tcscpy_s(f.lfFaceName, _T("方正舒体"));    // 设置字体为(高版本 VC 推荐使用 _tcscpy_s 函数)
		f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
		settextstyle(&f);                     // 设置字体样式
		outtextxy(100, 200, _T("蛇撞死了 Game Over"));
		Sleep(5000);
		exit(0);
	}
	head->update();    // 重绘新的头
}
 
void Snake::getFoodLocation(int &x, int &y)
{
	Body * p = NULL;
	int mapy = 0;
	int mapx = 0;
	srand(time(NULL)); // 设置随机数种子
 
	while (1)
	{
		x = (rand() % (WIDTH - 10)) / 10 *10;  // 在指定的范围内产生随机数（屏幕范围内）并取10的倍数
		y = (rand() % (HEIGHT - 10))/ 10 * 10;
 
		p = head;
		while (p != NULL)                                     //是否是身体
		{
			if (p->getX() == x && p->getY() == y)
			{
				p = head;
				break;
			}
			p = p->getNext();
		}
		for (int i = 0; i < 48; i++  ) // 是否是墙
		{
			mapy = i * 10;
			for (int j = 0; j < 64; j++)
			{
				if (map[i][j] == '1')
				{
					mapx = j * 10;
					if (x == mapx && y == mapy)
					{
						p = head;
						break;
					}
				}
			}
			if (p == head)
			{
				break;
			}
		}
		if (p == NULL)   //遍历之后，满足食物坐标不是身体坐标的条件，则返回，否则生成新的事物坐标
		{
			return;
		}
	}
}
 
void Snake::createFood()
{
	//得到事物坐标
	getFoodLocation(foodX, foodY);
 
	setfillcolor(YELLOW);// 设置填充颜色
	setlinecolor(GREEN);// 设置划线颜色
	fillrectangle(foodX, foodY, foodX + 10, foodY + 10);
}
 
 
bool Snake::isTouchFood()  //判断是否碰到事物
{
	Body *p = head;
 
	if (p->getX() == foodX && p->getY() == foodY)
	{
		return true; // 如果碰到食物
	}
	return false;
}
 
void Snake::eatFoodAddBody() 
{
	Body *p = head;
 
	//在身体的后面加一个身体,实际上坐标和原尾巴坐标一致，这样就会使蛇在下一次移动长长一节
 
	while ( p->getNext() != NULL)//找到尾巴
	{
		p = p->getNext();
	}
 
	Body *newBody = new Body(p->getX(), p->getY());
 
	p->setNext(newBody);
	newBody->setNext(NULL);
}
 
 
bool Snake::isGameOver()
{
	Body *p = head;
	Body *q = p ->getNext();
 
	int x;
	int y;
 
	while (q != NULL)
	{
		x = p->getX();
		y = p->getY();
		if (x == q->getX() && y == q->getY()) // 头碰到了自己的身体 die
		{
			return true;
		}
		if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)  // 头撞向边界， 并且头都跑出去了
		{
			return true;
		}
		if (isTouchMap())  //碰到了地图
		{
			return true;
		}
 
		q = q->getNext();
	}
	return false;
}
 
void Snake::initMap()
{
	FILE *fp = NULL;
	int x = 0;
	int y = 0;
	fopen_s(&fp, "Map/map1.txt", "r ");   // 只读方式打开文件
	if (fp == NULL)
	{
		printf("地图文件打开失败\n");
		return;
	}
	else
	{
		printf("地图文件打开成功， 文件编号：%d\n", fp);
	}
 
	//fread(map, 1, 64*48, fp);
	for (int i = 0; i < 48; i++)
	{
		for (int j = 0; j < 65; j++)
		{
			map[i][j]=fgetc(fp);
		}
	}
	//根据地图文件生成地图
	setfillcolor(BROWN);
	setlinecolor(BLACK);
	for (int i = 0; i < 48; i++)
	{
		y = i*10; 
		for (int j = 0; j < 64; j++)
		{
			//printf("%c", map[i][j]);
			if (map[i][j] == '1')
			{
				x = j*10; 
				fillrectangle(x, y, x + 10, y + 10);
			}
		}
	}
	fclose(fp);
}
 
bool Snake::isTouchMap()
{
	Body *p = head;
	int px = p->getX();
	int py = p->getY();
	int mapx = 0;
	int mapy = 0;
 
	for (int i = 0; i < 48; i++)
	{
		mapy = i * 10;
		for (int j = 0; j < 64; j++)
		{
			if (map[i][j] == '1')
			{
				mapx = j * 10;
				if (px == mapx && py == mapy)
				{
					return true;
				}
			}
		}
	}
	return false;
}
