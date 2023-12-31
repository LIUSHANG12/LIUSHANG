#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<mmsystem.h>//音乐文件
#pragma comment(lib,"winmm.lib")//音乐文件
/*知识点：结构体、循环、easyx。数组*/
//做界面1，创建一个窗口，图形窗口
//蛇的结构
#define SNAKE_NUM 500//蛇的最大节数
//枚举体定义蛇的方向
enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
struct Snake
{
	int size;//蛇的节数
	int dir;//方向
	int speed;//速度
	POINT coor[500];//坐标
}snake;
struct Food
{
	int x;
	int y;
	int r;//食物的半径
	bool flag;//食物是否被吃了
	DWORD color;//食物的颜色
}food;
//数据的初始化
void GameInit()
{
	//初始化graph图形窗口，SHOWCONSOLE显示控制台
	initgraph(640, 480, SHOWCONSOLE);//窗口长640，宽480
	//设置随机数种子，GetTickCount();获取系统开机到现在的毫秒数
	srand(GetTickCount());
	//初始化蛇
	snake.size = 3;
	snake.speed = 10;
	snake.dir = RIGHT;
	for (int i = 0; i < snake.size; i++)
	{
		snake.coor[i].x = 40 - i * 10;
		snake.coor[i].y = 40;
	}
	//初始化食物，rand()是随机生成整数的一个标准库函数
//如果没有随机生成食物的函数，食物每次产生的位置都是固定的
//设置食物需要的头文件为#include<stdilib.h>
//一般把时间作为种子，因为时间在不断变坏
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.r = rand() % 10 + 5;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.flag = true;
}
//绘制蛇及食物与窗口
void GameDraw()
{
	BeginBatchDraw();
	setbkcolor(RGB(28, 115, 119));//设置背景颜色
	cleardevice();//以背景颜色清空视窗
	float h = rand() % 180;
	setfillcolor(HSVtoRGB(h, 0.9, 0.8));//设置蛇及食物的颜色为渐变色
	for (int i = 0; i < snake.size; i++)//绘制蛇
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	 setlinecolor(RGB(0, 0, 0));
	 line(0, 0, 640, 0);
	 line(0, 0, 0, 480);
	 line(0, 480, 640, 480);
	 line(640, 0, 640, 480);
	if (food.flag)//绘制食物
	{
		solidcircle(food.x,food.y,food.r);
	}
	EndBatchDraw();
}
void snakeMove()
{
	for (int i = snake.size - 1; i > 0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	switch (snake.dir)
	{
	case UP://给蛇向上的速度
		snake.coor[0].y -= snake.speed;
		break;
	case DOWN://给蛇向下的速度
		snake.coor[0].y += snake.speed;
		break;
	case LEFT://给蛇向左的速度
		snake.coor[0].x -= snake.speed;
		break;
	case RIGHT://给蛇向右的速度
		snake.coor[0].x += snake.speed;
		break;
	}
}
//通过按键改变蛇的方向
void keyControl()
{//_kbhit()为判断按键是否存在的函数，如果有返回真，否则返回假
	if (_kbhit())
		switch (_getch())//上下左右键值为72 80 75 77
		{
		case 'w'://按相应按键即可上下左右移动
		case'W':
		case 72:
			if (snake.dir != DOWN)
			{
				snake.dir = UP;
			}
			break;
		case 's':
		case'S':
		case 80:
			if (snake.dir != UP)
			{
				snake.dir = DOWN;
			}
			break;
		case 'a':
		case'A':
		case 75:
			if (snake.dir != RIGHT)
			{
				snake.dir = LEFT;
			}
			break;
		case'd':
		case'D':
		case 77:
			if (snake.dir != LEFT)
			{
				snake.dir = RIGHT;
			}
			break;
		case' '://输入空格在暂停与继续的循环
			while (1)
			{
				if(_getch()==' ')
				return;
			}
			break;
		}
}

void lfover()
{
	for (int i = 1; i <=snake.size; i++)
	{
		if (snake.coor[0].x >=snake.coor[i].x - 5 && snake.coor[0].x<= snake.coor[i].x + 5
			&& snake.coor[0].y>= snake.coor[i].y - 5&& snake.coor[0].y <=snake.coor[i].y + 5)
		{
			while (1)
			{
				setbkmode(TRANSPARENT);//文字为透明字体
				settextcolor(RGB(255, 0, 0));//设置文字颜色
				settextstyle(80, 0, _T("宋体"));
				outtextxy(240, 220, _T("游戏失败"));
			}
		}
	}
}
void snakecw()
{
	if (snake.coor[0].x < 0 || snake.coor[0].x >=640 ||
		snake.coor[0].y < 0
	|| snake.coor[0].y >=480)
	{
		while (1)
		{
			setbkmode(TRANSPARENT);//文字为透明字体
			settextcolor(RGB(255, 0, 0));//设置文字颜色
			settextstyle(80, 0, _T("宋体"));
			outtextxy(240, 220, _T("游戏失败"));
		}
	}

}
void eatfood()
{
	if (snake.coor[0].x >= food.x - food.r && snake.coor[0].x <= food.x + food.r
		&& snake.coor[0].y >= food.y - food.r && snake.coor[0].y <= food.y + food.r)
	{
		food.flag = false;
		snake.size++;
	}
	if (!food.flag)
	{
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.r = rand() % 10 + 5;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.flag = true;
	}
}
int main()
{
	 GameInit();
	while (1)
	{
		 GameDraw();
		 snakeMove();
		 keyControl();
		 eatfood();
		 lfover();
		 snakecw();
		Sleep(50);
	}
	return 0;
}