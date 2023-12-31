#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <stdio.h>
#include "pvp.h"
#include "basic.h"
#include "pve.h"
#include "review.h"

Chess_move chess_move2[225] = { 0 };

void PVE_MODE(int board[][16])
{
	//ѡ��ִ��ִ��
	int player_color,envir_color;
	cleardevice();
	IMAGE cover1;
	loadimage(&cover1, "./����3.jpg", 850, 650);
	putimage(0, 0, &cover1);
	setfillcolor(RGB(232, 176, 179));
	solidroundrect(380, 280, 500, 320, 10, 10);
	solidroundrect(380, 340, 500, 380, 10, 10);
	solidroundrect(380, 400, 500, 440, 10, 10);
	settextstyle(30, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(RGB(37, 89, 139));
	char button1[] = "ѡ��ڰ�";
	outtextxy(380 + (120 - textwidth(button1)) / 2, 280 + (40 - textheight(button1)) / 2, button1);
	char button2[] = "ִ��";
	outtextxy(380 + (120 - textwidth(button2)) / 2, 340 + (40 - textheight(button2)) / 2, button2);
	char button3[] = "ִ��";
	outtextxy(380 + (120 - textwidth(button3)) / 2, 400 + (40 - textheight(button3)) / 2, button3);
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{				
				if (msg.x >= 380 && msg.x <= 500 && msg.y >= 340 && msg.y <= 380)
				{
					player_color = BLACK_C;
					envir_color = WHITE_C;
					break;
				}
				else if (msg.x >= 380 && msg.x <= 500 && msg.y >= 400 && msg.y <= 440)
				{
					player_color = WHITE_C;
					envir_color = BLACK_C;
					break;
				}
			}
		}
	}

	//ѡ���Ѷ�
	int level;
	int choose_tan = 0;
	cleardevice();
	IMAGE cover2;
	loadimage(&cover2, "./����3.jpg", 850, 650);
	putimage(0, 0, &cover2);
	setfillcolor(RGB(232, 176, 179));
	solidroundrect(380, 280, 500, 320, 10, 10);
	solidroundrect(380, 340, 500, 380, 10, 10);
	solidroundrect(380, 400, 500, 440, 10, 10);
	settextstyle(30, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(RGB(37, 89, 139));
	char button4[] = "̰̰";
	outtextxy(380 + (120 - textwidth(button4)) / 2, 280 + (40 - textheight(button4)) / 2, button4);
	char button5[] = "�е�";
	outtextxy(380 + (120 - textwidth(button5)) / 2, 340 + (40 - textheight(button5)) / 2, button5);
	char button6[] = "����";
	outtextxy(380 + (120 - textwidth(button6)) / 2, 400 + (40 - textheight(button6)) / 2, button6);
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				if (msg.x >= 380 && msg.x <= 500 && msg.y >= 280 && msg.y <= 320)
				{
					choose_tan = 1;
					break;
				}
				else if (msg.x >= 380 && msg.x <= 500 && msg.y >= 340 && msg.y <= 380)
				{
					level = middle;
					break;
				}
				else if (msg.x >= 380 && msg.x <= 500 && msg.y >= 400 && msg.y <= 440)
				{
					level = high;
					break;
				}
			}
		}
	}

	chessboard();
	int ret = 2;
	int cnt = 0;//�����Ӵ���
	int i = 0;//���ڼ�¼�úڰ�˭����
	int x, y;
	while (ret == 2)
	{
		//�ж��Ƿ�ƽ��
		if (is_full(board))
		{
			break;
		}
		
		//_printf(board) ;
		ret = win_lose(board,5);
		
		//�����£����ѡ��ִ�ף�����ִ�ڣ�
		if (player_color == WHITE_C && ret==2)
		{
			if (choose_tan)
			{
				E_putchess_tan(board, player_color, envir_color, cnt);
			}
			else
			{
				E_putchess(board,WHITE_C,BLACK_C,level,cnt);
			}	
			cnt++;
		}
		
		ret = win_lose(board, 5);

		while (ret==2)
		{
			if (MouseHit())
			{			
				MOUSEMSG msg = GetMouseMsg();
				if (msg.uMsg == WM_LBUTTONDOWN)
				{
					//�������¿�ʼ����
					if (msg.x >= 520 && msg.x <= 720 && msg.y >= 100 && msg.y <= 150)
					{
						fuzhi(board);
						PVE_MODE(board);
					}
					//���з�����ҳ����
					if (msg.x >= 520 && msg.x <= 720 && msg.y >= 180 && msg.y <= 230)
					{
						fuzhi(board);
						begining(board);
					}

					//����				
					x = (msg.x - 10) / 30;
					y = (msg.y - 10) / 30;					
					
					if (x == 8 && y == 8 && cnt == 0 && choose_tan != 1)
					{
						HWND warning = GetHWnd();
						MessageBox(warning, "AI�������㿪������Ԫ��������������", "��ʾ", MB_OKCANCEL);
						continue;
					}
					
					if (x >= 1 && x <= 15 && y >= 1 && y <= 15)
					{
						if (board[x][y] == NON)
						{
							//printf("��(%d,%d)\n",x,y);
							putchess(board, cnt, player_color, x, y,chess_move2);
							cnt++;
							break;
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
		

		ret = win_lose(board, 5);

		//������(���ѡ��ִ�ڣ�����ִ��)
		if (player_color == BLACK_C && ret == 2)
		{
			if (choose_tan)
			{
				E_putchess_tan(board, player_color, envir_color, cnt);
			}
			else
			{
				E_putchess(board, BLACK_C, WHITE_C, level, cnt);
			}
			cnt++;
		}
		
	}
	settextstyle(30, 0, "����");
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(248, 208, 123));
	setlinecolor(BLACK);
	fillrectangle(160, 510, 360, 560);
	if (ret == 0)
	{
		settextcolor(BLACK);
		char c[] = "�����ʤ";
		outtextxy(160 + (200 - textwidth(c)) / 2, 510 + (50 - textheight(c)) / 2, c);
	}
	else if(ret == 1)
	{
		settextcolor(WHITE);
		char c[] = "�����ʤ";
		outtextxy(160 + (200 - textwidth(c)) / 2, 510 + (50 - textheight(c)) / 2, c);
	}

	//_printf(board);
	//��ĩ���¿�ʼ,������ҳ������Ծֹ���
	settextstyle(40, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	fillrectangle(520, 260, 720, 310);
	char button7[] = "���汾��";
	outtextxy(520 + (200 - textwidth(button7)) / 2, 260 + (50 - textheight(button7)) / 2, button7);
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
					PVE_MODE(board);
				}
				if (msg.x >= 520 && msg.x <= 720 && msg.y >= 180 && msg.y <= 230)
				{
					fuzhi(board);
					begining(board);
				}
				
				if (msg.x >= 520 && msg.x <= 720 && msg.y >= 260 && msg.y <= 310)
				{
					save(chess_move2, cnt, player_color);
				}				
				

			}
		}

	}
}


//̰���ҳ�ʮ������ֵ�㣬�ڸ÷�Χ�����������������ṹ�������洢
typedef struct {
	int score;
	int x;
	int y;
}ass_chess;

ass_chess ass_list[225] = { 0 };
ass_chess ass_10max[20][10] = { 0 };

//��̰���ҳ�10���÷���ߵĵ㣬���ڽ�һ������
void ass_rank(int board[][16],int my_color,int opponent_color,int num,int envir_color)
{
	int i, j;
	int count = 0;
	//ass_list[225] = { 0 };
	for (i = 0; i < 225; i++)
	{
		ass_list[i] = { 0 };
	}

	for (i = 1; i <= 15; i++)
	{
		for (j = 1; j <= 15; j++)
		{
			if (board[i][j] == NON)
			{
				board[i][j] = my_color;
				ass_list[count].x = i;
				ass_list[count].y = j;
				ass_list[count].score = assess(board, my_color, opponent_color, i, j, envir_color);
				count++;
				board[i][j] = NON;
			}
		}
	}

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j  < 224-i; j++)
		{
			if (ass_list[j].score > ass_list[j + 1].score)
			{
				ass_chess t = ass_list[j];
				ass_list[j] = ass_list[j + 1];
				ass_list[j + 1] = t;
			}
		}
	}

	for (i = 0; i < 10; i++)
	{
		ass_10max[num][i] = ass_list[224 - i];
		
		//������ģ��
		//printf("(%d,%d) ", ass_10max[i].x,ass_10max[i].y);
		//if (i == 9)
		//	printf("\n");

	}

}

//�������Ӻ����������ã�
int evaluate(int board[][16], int my_color, int opponent_color, int envir_color)				
{
	int i, j;
	int score = 0;
	int score_player = 0;
	int score_envir = 0;
	for (i = 1; i <= 15; i++)
	{
		for (j = 1; j <= 15; j++)
		{
			/*
			//��ȡPlayer����߷�
			if (board[i][j] == my_color && small_assess(board,my_color,opponent_color,i,j,envir_color)>max_player)
			{
				max_player = small_assess(board, my_color, opponent_color, i, j,envir_color);
			}
			//��ȡenvir����߷�
			if (board[i][j] == opponent_color && small_assess(board, opponent_color, my_color, i, j,envir_color) > max_envir)
			{
				max_envir = small_assess(board, opponent_color, my_color, i, j,envir_color);
			}			
			*/

			
	//		/*
			if (board[i][j] == my_color)
			{
				score_player += small_assess(board, my_color, opponent_color, i, j, envir_color);
			}
			if (board[i][j] == opponent_color)
			{
				score_envir += small_assess(board, opponent_color, my_color, i, j, envir_color);
			}			
	//		*/

		}
	}
	score = score_envir - score_player;
	return score;
}


//����С�����㷨&���¼�֦�㷨
int bestchess(int board[][16], int P_or_E, int depth, int player_color, int envir_color ,int alpha, int beta,int num)
{
	int i;
	int val=0;
	//ass_chess ass_10max[10] = { 0 };
	//����Ƿ�ﵽ���orȡʤ
	
//	/*
	if (win_lose(board, 5) == envir_color)
	{
		return 2 * evaluate(board, player_color, envir_color, envir_color);
	}
//	*/
	
	if (depth == 0 || win_lose(board, 5) != 2)
	{
		return evaluate(board, player_color, envir_color,envir_color);
	}
	//ass_rank(board, player_color, envir_color,cnt);
	
	if (P_or_E == envir)
	{
		int max_val = -9999999;
		ass_rank(board, player_color, envir_color, num, envir_color);
		for (i = 0; i < 10; i++)
		{
			
				if (board[ass_10max[num][i].x][ass_10max[num][i].y] == NON)
				{
					//���������²�ģ����һ��������ô��
					board[ass_10max[num][i].x][ass_10max[num][i].y] = envir_color;
					val = bestchess(board, player, depth - 1, player_color, envir_color,alpha,beta,num+1);		
					board[ass_10max[num][i].x][ass_10max[num][i].y] = NON;												
					
					if (val > max_val)
					{
						max_val = val;
					}
					if (val > alpha)
					{
						alpha = val;
					}
					//���¼�֦
					if (alpha >= beta)
					{
						break;
					}
				}
			
		}
		return max_val;
	}

	else if (P_or_E == player)
	{
		int min_val = 9999999;
		ass_rank(board, envir_color, player_color, num, envir_color);
		for (i = 0; i < 10; i++)
		{
				if (board[ass_10max[num][i].x][ass_10max[num][i].y] == NON)
				{
					//���������²�ģ����һ��������ô��
					board[ass_10max[num][i].x][ass_10max[num][i].y] = player_color;
					val = bestchess(board, envir, depth - 1, player_color, envir_color,alpha,beta,num+1);
					board[ass_10max[num][i].x][ass_10max[num][i].y] = NON;
					if (val < min_val)
					{
						min_val = val;
					}
					if (val < beta)
					{
						beta = val;
					}
					//���¼�֦
					if (alpha >= beta)
					{
						break;
					}
				}
			
		}
		return min_val;
	}
		
	else		//������
	{
		return -1;
	}
}


//����ִ��(����������)
void E_putchess(int board[][16],int player_color,int envir_color,int level,int cnt)
{
	int best_x, best_y = -1;
	int max_val = -9999999;
	int i;
	int val=0;
	int num = 0;
	
	ass_rank(board, player_color, envir_color, num, envir_color);

	//����ɸѡ����10����
	for (i = 0; i <10; i++)
	{
			if (board[ass_10max[num][i].x][ass_10max[num][i].y] == NON)
			{
				board[ass_10max[num][i].x][ass_10max[num][i].y] = envir_color;
				//ģ���������
				val = bestchess(board, player, level, player_color, envir_color, -999999, 999999, num + 1);
				board[ass_10max[num][i].x][ass_10max[num][i].y] = NON;
			}
			if (val > max_val)
			{
				max_val = val;
				best_x = ass_10max[num][i].x;
				best_y = ass_10max[num][i].y;
			}
	}
	putchess(board, cnt, envir_color, best_x, best_y,chess_move2);
	//printf("(%d,%d)\n", best_x, best_y);

}




//�ж������Ƿ��ڽ���
int isValid(int i, int j)
{
	return i >= 1 && i < 16 && j >= 1 && j < 16;
}


//�����������ӵ��Ӻ���
int small_assess(int board[][16], int my_color, int opponent_color, int i, int j, int envir_color)
{
	int direction[8][2] = {
	{-1, -1}, //����
	{-1, 0}, //��
	{-1, 1}, //����
	{0, -1}, //��
	{0, 1}, //��
	{1, -1}, //����
	{1, 0}, //��
	{1, 1} //����
	};
	
	//����1/4���̵�λ������
	int weight[16][16] = {
	{100, -5, 10, 5, 5, 10, -5, 100},
	{-5, -45, 1, 1, 1, 1, -45, -5},
	{10, 1, 3, 2, 2, 3, 1, 10},
	{5, 1, 2, 1, 1, 2, 1, 5},
	{5, 1, 2, 1, 1, 2, 1, 5},
	{10, 1, 3, 2, 2, 3, 1, 10},
	{-5, -45, 1, 1, 1, 1, -45, -5},
	{100, -5, 10, 5, 5, 10, -5, 100}
	};
	
	int score= 0;
	if (my_color == envir_color)
	{
		score += 10;
	}
	score += weight[i < 8 ? i : 16 - i][j < 8 ? j : 16 - j];
	for (int k = 0; k < 8; k++) { //�����˸�����
		int count = 1; //������
		int empty = 0; //��λ��
		int block = 0; //��ס��
		int x = i + direction[k][0]; //���ŷ����ƶ�
		int y = j + direction[k][1];
		while (isValid(x, y) && board[x][y] == my_color) { //������Լ������ӣ���������һ
			count++;
			x += direction[k][0];
			y += direction[k][1];
		}
		if (isValid(x, y) && board[x][y] == NON) { //����ǿ�λ����λ����һ
			empty++;
		}
		else { //����Ƕ��ֵ����ӻ��߳��磬��ס����һ
			block++;
		}
		x = i - direction[k][0]; //�����ƶ�
		y = j - direction[k][1];
		while (isValid(x, y) && board[x][y] == my_color) { //������Լ������ӣ���������һ
			count++;
			x -= direction[k][0];
			y -= direction[k][1];
		}
		if (isValid(x, y) && board[x][y] == NON) { //����ǿ�λ����λ����һ
			empty++;
		}
		else { //����Ƕ��ֵ����ӻ��߳��磬��ס����һ
			block++;
		}
		//��������������λ���Ͷ�ס���ж����Σ�������
		if (count == 5) { //����
			score += FIVE;
		}
		else if (count == 4) { //����
			if (empty == 2) { //����
				score += HUO_FOUR;
			}
			else if (empty == 1) { //����
				score += CHONG_FOUR;
			}
		}
		else if (count == 3) { //����
			if (empty == 2) { //����
				if (block == 0) { //˫����
					score += HUO_THREE * 2;
				}
				else { //������
					score += HUO_THREE;
				}
			}
			else if (empty == 1) { //����
				score += MIAN_THREE;
			}
		}
		else if (count == 2) { //����
			if (empty == 2) { //���
				score += HUO_TWO;
			}
			else if (empty == 1) { //�߶�
				score += MIAN_TWO;
			}
		}
		else if (count == 1)
		{
			score += ONE;
		}
	}
	return score;
}


//�������Ӻ���(����&̰����)
int assess(int board[][16], int player_color, int envir_color, int i, int j, int envir_color1)
{
	int score = small_assess(board, player_color, envir_color, i, j, envir_color) + small_assess(board, envir_color, player_color, i, j, envir_color);
	return score;
}


//����ִ�壨̰�İ棩
void E_putchess_tan(int board[][16], int player_color, int envir_color, int cnt)
{
	int max_score = -1;
	int best_x = -1, best_y = -1;
	int i, j;
	
	for (i = 1; i <= 15; i++)
	{
		for (j = 1; j <= 15; j++)
		{
			if (board[i][j] == NON)
			{
				board[i][j] = envir_color;
				if (assess(board, player_color, envir_color,i,j, envir_color) > max_score)
				{
					max_score = assess(board, player_color, envir_color,i,j, envir_color);
					best_x = i;
					best_y = j;
				}
				board[i][j] = NON;
			}
		}
	}
	
	putchess(board, cnt, envir_color, best_x, best_y,chess_move2);
	//_printf(board);
}