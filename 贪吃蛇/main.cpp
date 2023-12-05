#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<mmsystem.h>//�����ļ�
#pragma comment(lib,"winmm.lib")//�����ļ�
/*֪ʶ�㣺�ṹ�塢ѭ����easyx������*/
//������1������һ�����ڣ�ͼ�δ���
//�ߵĽṹ
#define SNAKE_NUM 500//�ߵ�������
//ö���嶨���ߵķ���
enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
struct Snake
{
	int size;//�ߵĽ���
	int dir;//����
	int speed;//�ٶ�
	POINT coor[500];//����
}snake;
struct Food
{
	int x;
	int y;
	int r;//ʳ��İ뾶
	bool flag;//ʳ���Ƿ񱻳���
	DWORD color;//ʳ�����ɫ
}food;
//���ݵĳ�ʼ��
void GameInit()
{
	//��ʼ��graphͼ�δ��ڣ�SHOWCONSOLE��ʾ����̨
	initgraph(640, 480, SHOWCONSOLE);//���ڳ�640����480
	//������������ӣ�GetTickCount();��ȡϵͳ���������ڵĺ�����
	srand(GetTickCount());
	//��ʼ����
	snake.size = 3;
	snake.speed = 10;
	snake.dir = RIGHT;
	for (int i = 0; i < snake.size; i++)
	{
		snake.coor[i].x = 40 - i * 10;
		snake.coor[i].y = 40;
	}
	//��ʼ��ʳ�rand()���������������һ����׼�⺯��
//���û���������ʳ��ĺ�����ʳ��ÿ�β�����λ�ö��ǹ̶���
//����ʳ����Ҫ��ͷ�ļ�Ϊ#include<stdilib.h>
//һ���ʱ����Ϊ���ӣ���Ϊʱ���ڲ��ϱ仵
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.r = rand() % 10 + 5;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.flag = true;
}
//�����߼�ʳ���봰��
void GameDraw()
{
	BeginBatchDraw();
	setbkcolor(RGB(28, 115, 119));//���ñ�����ɫ
	cleardevice();//�Ա�����ɫ����Ӵ�
	float h = rand() % 180;
	setfillcolor(HSVtoRGB(h, 0.9, 0.8));//�����߼�ʳ�����ɫΪ����ɫ
	for (int i = 0; i < snake.size; i++)//������
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	 setlinecolor(RGB(0, 0, 0));
	 line(0, 0, 640, 0);
	 line(0, 0, 0, 480);
	 line(0, 480, 640, 480);
	 line(640, 0, 640, 480);
	if (food.flag)//����ʳ��
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
	case UP://�������ϵ��ٶ�
		snake.coor[0].y -= snake.speed;
		break;
	case DOWN://�������µ��ٶ�
		snake.coor[0].y += snake.speed;
		break;
	case LEFT://����������ٶ�
		snake.coor[0].x -= snake.speed;
		break;
	case RIGHT://�������ҵ��ٶ�
		snake.coor[0].x += snake.speed;
		break;
	}
}
//ͨ�������ı��ߵķ���
void keyControl()
{//_kbhit()Ϊ�жϰ����Ƿ���ڵĺ���������з����棬���򷵻ؼ�
	if (_kbhit())
		switch (_getch())//�������Ҽ�ֵΪ72 80 75 77
		{
		case 'w'://����Ӧ�����������������ƶ�
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
		case' '://����ո�����ͣ�������ѭ��
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
				setbkmode(TRANSPARENT);//����Ϊ͸������
				settextcolor(RGB(255, 0, 0));//����������ɫ
				settextstyle(80, 0, _T("����"));
				outtextxy(240, 220, _T("��Ϸʧ��"));
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
			setbkmode(TRANSPARENT);//����Ϊ͸������
			settextcolor(RGB(255, 0, 0));//����������ɫ
			settextstyle(80, 0, _T("����"));
			outtextxy(240, 220, _T("��Ϸʧ��"));
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