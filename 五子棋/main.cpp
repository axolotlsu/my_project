#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#define _CRT_SECURE_NO_WARNINGS

#include <graphics.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "pvp.h"
#include "basic.h"
#include "pve.h"
#include "review.h"



//��ʼ����
void begining(int board[][16])
{
	//�����ʼ��
	cleardevice();
	IMAGE cover;
	loadimage(&cover, "./����3.jpg", 850, 650);
	putimage(0, 0, &cover);
	setfillcolor(RGB(232, 176, 179));
	//solidroundrect(45, 55, 180, 120, 20, 20);
	solidroundrect(380, 280, 500, 320, 10, 10);
	solidroundrect(380, 340, 500, 380, 10, 10);
	solidroundrect(380, 400, 500, 440, 10, 10);
	solidroundrect(700, 610, 820, 640, 5, 5);
	
	settextstyle(60, 0, "��Բ");
	setbkmode(TRANSPARENT);
	settextcolor(RGB(235, 176, 182));
	char title[] = "������";
	outtextxy(45 + (135 - textwidth(title)) / 2, 55 + (65 - textheight(title)) / 2, title);

	settextstyle(30, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(RGB(37, 89, 139));
	char button1[] = "PVP";
	outtextxy(380 + (120 - textwidth(button1)) / 2, 280 + (40 - textheight(button1)) / 2, button1);
	char button2[] = "PVE";
	outtextxy(380 + (120 - textwidth(button2)) / 2, 340 + (40 - textheight(button2)) / 2, button2);
	char button3[] = "��ʷ��¼";
	outtextxy(380 + (120 - textwidth(button3)) / 2, 400 + (40 - textheight(button3)) / 2, button3);
	
	settextstyle(28, 0, "��������");
	char statement[] = "��������";
	outtextxy(700 + (120 - textwidth(statement)) / 2, 610 + (30 - textheight(statement)) / 2, statement);

	//�㰴ť
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				if (msg.x >= 380 && msg.x <= 500 && msg.y >= 280 && msg.y <= 320)
				{					
					PVP_MODE(board);
				}
				else if (msg.x >= 380 && msg.x <= 500 && msg.y >= 340 && msg.y <= 380)
				{					
					PVE_MODE(board);
					
				}
				else if (msg.x >= 380 && msg.x <= 500 && msg.y >= 400 && msg.y <= 440)
				{
					review(board);
				}
				else if (msg.x >= 700 && msg.x <= 820 && msg.y >= 610 && msg.y <= 640)
				{
					developer_statement(board);
				}
			}
		}
	}
}

//������������
void developer_statement(int board[][16])
{
	cleardevice();
	IMAGE cover;
	loadimage(&cover, "./��ͼ2.jpg", 850, 650);
	putimage(0, 0, &cover);
	setfillcolor(RGB(235, 176, 182));
	solidroundrect(640, 420, 800, 470, 10, 10);
	settextstyle(45, 0, "��������");
	setbkmode(TRANSPARENT);
	char button[] = "������ҳ";
	settextcolor(RGB(37, 89, 139));
	outtextxy(640 + (160 - textwidth(button)) / 2, 420 + (50 - textheight(button)) / 2, button);
	settextcolor(RGB(235, 176, 182));
	char title[] = "��������";
	outtextxy(40 + (250 - textwidth(title)) / 2, 40 + (50 - textheight(title)) / 2, title);
	

	FILE* file;
	char str[100];
	file = fopen("developer_statement.txt", "r");
	if (file == NULL)
	{
		HWND warning = GetHWnd();
		MessageBox(warning, "����������ʾʧ�ܣ������ļ��Ƿ�����", "��ʾ", MB_OKCANCEL);
		begining(board);
	}
	settextstyle(30, 0, "����");
	for(int i = 0; fscanf(file, "%99s", str) == 1; i++)		
	{ 
		outtextxy(30, 100 + 40 * i, str);
	}
	fclose(file); 
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				if (msg.x >= 640 && msg.x <= 800 && msg.y >= 420 && msg.y <= 470)
				{
					begining(board);
				}
			}
		}
	}
}

//��������
void chessboard(void)
{
	int n = 0;
	cleardevice();
	IMAGE cover;
	loadimage(&cover, "./���̵�ͼ.jpg", 850, 650);
	putimage(0, 0, &cover);
	setfillcolor(RGB(248, 208, 123));
	setlinecolor(BLACK);
	fillrectangle(30, 30, 490, 490);
	for (n = 0; n < 15; n++) 
	{
		line(50+30 * n, 50, 50 + 30 * n, 470);
		line(50, 50 + 30 * n, 470, 50 + 30 * n);
	}
	settextstyle(40, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	fillrectangle(520, 100, 720, 150);
	char button1[] = "���¿�ʼ";
	outtextxy(520 + (200 - textwidth(button1)) / 2, 100 + (50 - textheight(button1)) / 2, button1);
	fillrectangle(520, 180, 720, 230);
	char button2[] = "������ҳ";
	outtextxy(520 + (200 - textwidth(button2)) / 2, 180 + (50 - textheight(button2)) / 2, button2);
}

//ʤ���ж�
int win_lose(int board[][16],int num)
{
	int i, j, n;
	//����
	for (i = 1; i <= 15; i++)
	{
		for (j = 1; j <= 16-num; j++)
		{
			int sum = 0;
			if (board[i][j] != NON)
			{
				for (n = 0; n <= num-1; n++)
				{
					sum += board[i][j + n];
				}
				if (sum == 0)
				{
					return 0;
				}
				else if (sum == num)
				{
					return 1;
				}
			}
		}
	}
	//����
	for (i = 1; i <= 15; i++)
	{
		for (j = 1; j <= 16-num; j++)
		{
			int sum = 0;
			if (board[j][i] != NON)
			{
				for (n = 0; n <= num-1; n++)
				{
					sum += board[j+n][i];
				}
				if (sum == 0)
				{
					return 0;
				}
				else if (sum == num)
				{
					return 1;
				}
			}
		}
	}
	//��Խ�
	for (i = 1; i <= 16-num; i++)
	{
		for (j = 1; j <= 16-num; j++)
		{
			int sum = 0;
			if (board[i][j] != NON)
			{
				for (n = 0; n <= num-1; n++)
				{
					sum += board[i + n][j + n];
				}
				if (sum == 0)
				{
					return 0;
				}
				else if (sum == num)
				{
					return 1;
				}
			}
		}
	}
	//�ҶԽ�
	for (i = 1; i <= 16-num; i++)
	{
		for (j = num; j <= 15; j++)
		{
			int sum = 0;
			if (board[i][j] != NON)
			{
				for (n = 0; n <= num-1; n++)
				{
					sum += board[i + n][j - n];
				}
				if (sum == 0)
				{
					return 0;
				}
				else if (sum == num)
				{
					return 1;
				}
			}
		}
	}

	return 2;
}

int is_full(int board[][16])
{
	int count = 1;
	for (int i = 1; i <= 15; i++)
	{
		for (int j = 1; j <= 15; j++)
		{
			if (board[i][j] == NON)
			{
				count = 0;
			}
		}
	}
	return count;
}

//�۲���������Ĳ����ú���
void _printf(int board[][16])
{
	int i = 0, j = 0;
	for(i = 1; i < 16; i++)
	{
		for (j = 1; j < 16; j++)
		{
			printf("%d", board[j][i]);
			if (j == 15)
			{
				printf("\n");
				if (i == 15)
					printf("\n");
			}
		}

	}
}

//��ʼ������
void fuzhi(int board[][16])
{
	int i, j;
	for (i = 0; i <= 15; i++)
	{
		for (j = 0; j <= 15; j++)
		{
			board[j][i] = NON;
		}
	}
}

int main(void) 
{	
	int board[16][16] ;
	fuzhi(board);
	initgraph(850, 650, 0);
	//��ʼ����
	begining(board);
	
	return 0;
}

