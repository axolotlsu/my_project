#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <stdio.h>
#include "pvp.h"
#include "basic.h"
#include "pve.h"
#include "review.h"



//PVP mode
void PVP_MODE(int board[][16])
{
	int cnt = 0;//�����Ӵ���
	int i = 0;//���ڼ�¼�úڰ�˭����
	int x, y;
	int ret = 2;
	Chess_move chess_move1[225] = { 0 };

	chessboard();
	//����׶�
	while (ret == 2)
	{
		ret = win_lose(board,5);
		if (is_full(board))
		{
			break;
		}
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				//�������¿�ʼ����
				if (msg.x >= 520 && msg.x <= 720 && msg.y >= 100 && msg.y <= 150)
				{
					fuzhi(board);
					PVP_MODE(board);
				}
				//���з�����ҳ����
				if (msg.x >= 520 && msg.x <= 720 && msg.y >= 180 && msg.y <= 230)
				{
					fuzhi(board);
					begining(board);
				}
				
				//�������ӹ���
				x = (msg.x - 10) / 30;
				y = (msg.y - 10) / 30;
				if (x >= 1 && x <= 15 && y >= 1 && y <= 15)
				{
					if (board[x][y] == NON)
					{
						putchess(board, cnt, i, x, y,chess_move1);
						cnt++;
						i = cnt % 2;
					}
					else
					{
						HWND warning = GetHWnd();
						MessageBox(warning, "�����ظ�����", "��ʾ", MB_OKCANCEL);
					}
				}
			}
		}

	}
	settextstyle(30, 0, "����");
	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);
	setfillcolor(RGB(248, 208, 123));
	fillrectangle(160, 510, 360, 560);
	if (ret == 0)
	{
		settextcolor(BLACK);
		char c[] = "�����ʤ";
		outtextxy(160 + (200 - textwidth(c)) / 2, 510 + (50 - textheight(c)) / 2, c);
	}
	else
	{
		settextcolor(WHITE);
		char c[] = "�����ʤ";
		outtextxy(160 + (200 - textwidth(c)) / 2, 510 + (50 - textheight(c)) / 2, c);
	}
	//���������¿�ʼ�򷵻���ҳ�򱣴�Ծֹ���
	settextstyle(40, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	fillrectangle(520, 260, 720, 310);
	char button3[] = "���汾��";
	outtextxy(520 + (200 - textwidth(button3)) / 2, 260 + (50 - textheight(button3)) / 2, button3);
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				if (msg.x >= 520 && msg.x <= 720 && msg.y >= 100 && msg.y <= 150)
				{
					fuzhi(board);
					PVP_MODE(board);
				}
				if (msg.x >= 520 && msg.x <= 720 && msg.y >= 180 && msg.y <= 230)
				{
					fuzhi(board);
					begining(board);
				}
				if (msg.x >= 520 && msg.x <= 720 && msg.y >= 260 && msg.y <= 310)
				{
					save(chess_move1, cnt, NON);
				}
			}
		}
		
	}
}

//����
void putchess(int board[][16], int cnt, int i, int x, int y,Chess_move chess_move[225])
{
	//��¼����
	chess_move[cnt].x = x;
	chess_move[cnt].y = y;
	chess_move[cnt].color = i;
	
	//����
	settextstyle(30, 0, "����");
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(248, 208, 123));
	setlinecolor(BLACK);
	fillrectangle(160, 510, 360, 560);
	if (i == BLACK_C)
	{
		board[x][y] = BLACK_C;
		x = x * 30 + 20;
		y = y * 30 + 20;
		setfillcolor(BLACK);
		solidcircle(x, y, RAD);
		settextcolor(WHITE);
		char c[] = "���������";
		outtextxy(160 + (200 - textwidth(c)) / 2, 510 + (50 - textheight(c)) / 2, c);
	}
	if (i == WHITE_C)
	{
		board[x][y] = WHITE_C;
		x = x * 30 + 20;
		y = y * 30 + 20;
		setfillcolor(WHITE);
		solidcircle(x, y, RAD);
		settextcolor(BLACK);
		char c[] = "���������";
		outtextxy(160 + (200 - textwidth(c)) / 2, 510 + (50 - textheight(c)) / 2, c);
	}
	
	//������������
	if (cnt > 0)
	{
		setfillcolor(chess_move[cnt - 1].color == WHITE_C ? WHITE : BLACK);
		solidcircle(chess_move[cnt-1].x * 30 + 20, chess_move[cnt-1].y * 30 + 20, RAD);
		setlinecolor(i == WHITE_C ? BLACK : WHITE);
		circle(x, y, 5);
	}
	
	
	//_printf(board);
}
