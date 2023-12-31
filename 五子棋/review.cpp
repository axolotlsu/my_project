#define _CRT_SECURE_NO_WARNINGS

#include <graphics.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "pvp.h"
#include "basic.h"
#include "pve.h"
#include "review.h"

//����Ծֹ���
void save(Chess_move chess_move[225], int cnt, int mode_who)
{
	int i;
	char fullPath[50];
	char directory[] = "historical_records/";
	char file_name[30];
	if (InputBox(file_name, 30, "��Ϊ���ζԾָ���Ӣ������", "������Ծ���", "(�뱣����׺).txt", NULL, NULL, false) == true)
	{
		strcpy(fullPath, directory);
		strcat(fullPath, file_name);
		FILE* file = fopen(fullPath, "w");
		if (file == NULL)							//������ʾ
		{
			HWND warning = GetHWnd();
			MessageBox(warning, "�����Ծּ�¼�ļ�ʧ��", "��ʾ", MB_OKCANCEL);
		//	continue;
		}
		else
		{
			//��¼pve�������ɫ��pvp����
			fprintf(file, "%d\n", mode_who);
			
			//����¼������˳���������
			for (i = 0; i < cnt ; i++)
			{
				fprintf(file, "%d %d %d\n", chess_move[i].x, chess_move[i].y, chess_move[i].color);
			}
			fclose(file);
		}
	}
}

//�Ƚ��ļ��޸�ʱ��(�����µ���)
int compare_time(const struct dirent** file1, const struct dirent** file2) 
{
	struct stat info1, info2;
	stat((*file1)->d_name, &info1);
	stat((*file2)->d_name, &info2);
	return info1.st_mtime < info2.st_mtime;
}

//��������(�طŰ�)
void chessboard_in_review(int mode_who)
{
	int n = 0;
	cleardevice();
//	/*
	IMAGE cover;
	loadimage(&cover, "./���̵�ͼ.jpg", 850, 650);
	putimage(0, 0, &cover);
//	*/
	
	
	setfillcolor(RGB(248, 208, 123));
	setlinecolor(BLACK);
	fillrectangle(30, 30, 490, 490);
	for (n = 0; n < 15; n++)
	{
		line(50 + 30 * n, 50, 50 + 30 * n, 470);
		line(50, 50 + 30 * n, 470, 50 + 30 * n);
	}
	settextstyle(40, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	fillrectangle(520, 100, 720, 150);
	char button1[] = "��һ��";
	outtextxy(520 + (200 - textwidth(button1)) / 2, 100 + (50 - textheight(button1)) / 2, button1);
	fillrectangle(520, 180, 720, 230);
	char button2[] = "��һ��";
	outtextxy(520 + (200 - textwidth(button2)) / 2, 180 + (50 - textheight(button2)) / 2, button2);
	fillrectangle(520, 260, 720, 310);
	char button3[] = "�����վ�";
	outtextxy(520 + (200 - textwidth(button3)) / 2, 260 + (50 - textheight(button3)) / 2, button3);
	fillrectangle(520, 340, 720, 390);
	char button4[] = "������ҳ";
	outtextxy(520 + (200 - textwidth(button4)) / 2, 340 + (50 - textheight(button4)) / 2, button4);

	settextstyle(30, 0, "����");
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(248, 208, 123));
	setlinecolor(BLACK);
	fillrectangle(160, 510, 360, 560);
	settextcolor(RED);
	if (mode_who == NON)
	{
		char c[] = "PVP�Ծ�";
		outtextxy(160 + (200 - textwidth(c)) / 2, 510 + (50 - textheight(c)) / 2, c);
	}
	else if (mode_who == BLACK_C)
	{
		char c[] = "PVE ���ִ��";
		outtextxy(160 + (200 - textwidth(c)) / 2, 510 + (50 - textheight(c)) / 2, c);
	}
	else if (mode_who == WHITE_C)
	{
		char c[] = "PVE ���ִ��";
		outtextxy(160 + (200 - textwidth(c)) / 2, 510 + (50 - textheight(c)) / 2, c);
	}
}

//����(�طŰ�)
void putchess_in_review(int board[][16], int mode_who)
{
	chessboard_in_review(mode_who);
	int i, j;
	for (i = 1; i <= 15; i++)
	{
		for (j = 1; j <= 15; j++)
		{
			if (board[i][j] != NON)
			{
				setfillcolor((board[i][j] == BLACK_C) ? BLACK : WHITE);
				solidcircle(i * 30 + 20, j * 30 + 20, RAD);
			}
		}
	}
}

//��ʷ��¼����
void review(int board[][16])
{
	cleardevice();
	IMAGE cover2;
	loadimage(&cover2, "./����3.jpg", 850, 650);
	putimage(0, 0, &cover2);
	setfillcolor(RGB(232, 176, 179));
	setlinecolor(RGB(103, 14, 21));
	fillroundrect(325, 80, 525, 140, 10, 10);
	fillroundrect(245, 155, 605, 195, 5, 5);


	settextstyle(45, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(RGB(37, 89, 139));
	char title[] = "��ʷ��¼";
	outtextxy(325 + (200 - textwidth(title)) / 2, 80 + (60 - textheight(title)) / 2, title);
	settextstyle(19, 0, "����");
	char hint1[] = "�����ʾ������";
	char hint2[] = "�������ֶ�����(���ļ����в�ѯ����)";
	outtextxy(245 + (360 - textwidth(hint1)) / 2, 155 + (20 - textheight(hint1)) / 2, hint1);
	outtextxy(245 + (360 - textwidth(hint2)) / 2, 175 + (20 - textheight(hint2)) / 2, hint2);
	settextstyle(40, 0, "����");
	char botton1[] = "������ҳ";
	outtextxy(410 + (120 - textwidth(botton1)) / 2, 520 + (60 - textheight(botton1)) / 2, botton1);
	settextstyle(30, 0, "����");
	char botton2[] = "�ֶ�����";
	outtextxy(650 + (80 - textwidth(botton2)) / 2, 400 + (40 - textheight(botton2)) / 2, botton2);
	struct dirent** namelist;
	int n;
	int i = 0, j = 0;
	n = scandir("./historical_records", &namelist, NULL, compare_time);			//scandir��ȡĿ¼������compare_time����
	if (n < 0)
	{
		HWND warning = GetHWnd();
		MessageBox(warning, "�޷��򿪶Ծ��ļ��������ļ��Ƿ���", "��ʾ", MB_OKCANCEL);
	}
	settextstyle(30, 0, "����");
	setfillcolor(RGB(232, 176, 179));
	setlinecolor(RGB(103, 14, 21));
	
	for (i=0; n-1-i > 1 && i < 5; i++)
	{
		fillroundrect(285, 210 + 55 * i, 555, 250 + 55 * i, 8, 8);
		outtextxy(285 + (270 - textwidth(namelist[n-1-i]->d_name)) / 2, (210 + 55 * i) + (40 - textheight(namelist[n-1-i]->d_name)) / 2, namelist[n-1-i]->d_name);
	}
	
	char fullPath[50];
	char directory[] = "historical_records/";
	strcpy(fullPath, directory);
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				//������ҳ
				if (msg.x >= 410 && msg.x <= 530 && msg.y >= 520 && msg.y <= 580)
				{
					begining(board);
				}
				//ѡ����ʾ���ĶԾ�
				if (i > 0 && msg.x >= 285 && msg.x <= 555 && msg.y >= 210 && msg.y <= 250)
				{
					strcat(fullPath, namelist[n - 1]->d_name);
					break;
				}
				if (i > 1 && msg.x >= 285 && msg.x <= 555 && msg.y >= 265 && msg.y <= 305)
				{
					strcat(fullPath, namelist[n - 2]->d_name);
					break;
				}
				if (i > 2 && msg.x >= 285 && msg.x <= 555 && msg.y >= 320 && msg.y <= 360)
				{
					strcat(fullPath, namelist[n - 3]->d_name);
					break;
				}
				if (i > 3 && msg.x >= 285 && msg.x <= 555 && msg.y >= 375 && msg.y <= 415)
				{
					strcat(fullPath, namelist[n - 4]->d_name);
					break;
				}
				if (i > 4 && msg.x >= 285 && msg.x <= 555 && msg.y >= 430 && msg.y <= 470)
				{
					strcat(fullPath, namelist[n - 5]->d_name);
					break;
				}
				//�ֶ�����Ծ�
				if (msg.x >= 650 && msg.x <= 730 && msg.y >= 400 && msg.y <= 440)
				{
					if (i > 4)
					{
						char file_name[30];
						if (InputBox(file_name, 30, "���ֶ�������Ҫ�طŵĶԾ�����", "������Ծ���", "(�뱣����׺).txt", NULL, NULL, false) == true)
						{
							strcat(fullPath, file_name);
							break;
						}
					}
					else
					{
						HWND warning = GetHWnd();
						MessageBox(warning, "�Ծ���ȫ��ʾ�������ֶ�����", "��ʾ", MB_OKCANCEL);
					}
				}
			}
		}
	}
	
	
	Chess_move chess_move[225] = { 0 };
	FILE* file = fopen(fullPath, "r");
	
	int mode_who = 10;
	fscanf(file, "%d", &mode_who);
	chessboard_in_review(mode_who);

	int row, col, color;
	for(i = 0; fscanf(file, "%d %d %d", &row, &col, &color) == 3 && i < 225; i++)
	{
		chess_move[i].x = row;
		chess_move[i].y = col;
		chess_move[i].color = color;
	}
	int count = 0;
	
	//BeginBatchDraw();
	while (1)
	{
		BeginBatchDraw();
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				if (msg.x >= 520 && msg.x <= 720 && msg.y >= 100 && msg.y <= 150 && count != 0)		//��һ��
				{
					board[chess_move[count - 1].x][chess_move[count - 1].y] = NON;
					count--;
					putchess_in_review(board, mode_who);
				}
				else if (msg.x >= 520 && msg.x <= 720 && msg.y >= 180 && msg.y <= 230 && count != i )		//��һ��
				{
					board[chess_move[count].x][chess_move[count].y] = chess_move[count].color;
					count++;
					putchess_in_review(board, mode_who);
				}
				else if (msg.x >= 520 && msg.x <= 720 && msg.y >= 260 && msg.y <= 310)		//�����վ�
				{
					fuzhi(board);
					for (count = 0; count < i; count++)
					{
						board[chess_move[count].x][chess_move[count].y] = chess_move[count].color;
					}
					putchess_in_review(board, mode_who);
				}
				else if (msg.x >= 520 && msg.x <= 720 && msg.y >= 340 && msg.y <= 390)		//������ҳ
				{
					FlushBatchDraw();
					EndBatchDraw();
					fuzhi(board);
					begining(board);
				}
			}
		}
		FlushBatchDraw(); 
		EndBatchDraw();
	}
}