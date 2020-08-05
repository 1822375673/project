
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
 
	createFood(); // ��ʼʳ��
	while (1)
	{
		if (_kbhit())
		{
			ch = _getch();     // һ�������Ҫ������getch���ܻ�ȡ��
			if (ch == 0xe0)   //�����λ���
			{
				ch = _getch(); //��ô�ٻ�ȡһ��
				switch (ch)
				{
				case  0x004b: if (dir != RIGHT) dir = LEFT; break; // �����ߵ��ƶ�����
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
			eatFoodAddBody();  //������
			createFood(); // �����µ�ʳ��
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
 
	//�ҵ��߿���β�����Ǹ��ڵ�
	while (p->getNext()->getNext()!= NULL)
	{
		p = p->getNext();
	}
	newTail = p;
	p = p->getNext();
	newTail->setNext(NULL);//���½ڵ����һ���ڵ��ÿ�
 
	p->setStat(p->OFF); // ��ԭβ�Ͳ���
	p->update();
   
	p->setX(head->getX());
	p->setY(head->getY());
	p->setNext(head->getNext());
 
	head->setNext(p);
	//�����ߵ�ͷ��
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
		gettextstyle(&f);                     // ��ȡ��ǰ��������
		f.lfHeight = 48;                      // ��?�����߶��? 48
		_tcscpy_s(f.lfFaceName, _T("��������"));    // ��������Ϊ(�߰汾 VC �Ƽ�ʹ�� _tcscpy_s ����)
		f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
		settextstyle(&f);                     // ����������ʽ
		outtextxy(100, 200, _T("��ײ���� Game Over"));
		Sleep(5000);
		exit(0);
	}
	head->update();    // �ػ��µ�ͷ
}
 
void Snake::getFoodLocation(int &x, int &y)
{
	Body * p = NULL;
	int mapy = 0;
	int mapx = 0;
	srand(time(NULL)); // �������������
 
	while (1)
	{
		x = (rand() % (WIDTH - 10)) / 10 *10;  // ��ָ���ķ�Χ�ڲ������������Ļ��Χ�ڣ���ȡ10�ı���
		y = (rand() % (HEIGHT - 10))/ 10 * 10;
 
		p = head;
		while (p != NULL)                                     //�Ƿ�������
		{
			if (p->getX() == x && p->getY() == y)
			{
				p = head;
				break;
			}
			p = p->getNext();
		}
		for (int i = 0; i < 48; i++  ) // �Ƿ���ǽ
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
		if (p == NULL)   //����֮������ʳ�����겻������������������򷵻أ����������µ���������
		{
			return;
		}
	}
}
 
void Snake::createFood()
{
	//�õ���������
	getFoodLocation(foodX, foodY);
 
	setfillcolor(YELLOW);// ���������ɫ
	setlinecolor(GREEN);// ���û�����ɫ
	fillrectangle(foodX, foodY, foodX + 10, foodY + 10);
}
 
 
bool Snake::isTouchFood()  //�ж��Ƿ���������
{
	Body *p = head;
 
	if (p->getX() == foodX && p->getY() == foodY)
	{
		return true; // �������ʳ��
	}
	return false;
}
 
void Snake::eatFoodAddBody() 
{
	Body *p = head;
 
	//������ĺ����һ������,ʵ���������ԭβ������һ�£������ͻ�ʹ������һ���ƶ�����һ��
 
	while ( p->getNext() != NULL)//�ҵ�β��
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
		if (x == q->getX() && y == q->getY()) // ͷ�������Լ������� die
		{
			return true;
		}
		if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)  // ͷײ��߽磬 ����ͷ���ܳ�ȥ��
		{
			return true;
		}
		if (isTouchMap())  //�����˵�ͼ
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
	fopen_s(&fp, "Map/map1.txt", "r ");   // ֻ����ʽ���ļ�
	if (fp == NULL)
	{
		printf("��ͼ�ļ���ʧ��\n");
		return;
	}
	else
	{
		printf("��ͼ�ļ��򿪳ɹ��� �ļ���ţ�%d\n", fp);
	}
 
	//fread(map, 1, 64*48, fp);
	for (int i = 0; i < 48; i++)
	{
		for (int j = 0; j < 65; j++)
		{
			map[i][j]=fgetc(fp);
		}
	}
	//���ݵ�ͼ�ļ����ɵ�ͼ
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
