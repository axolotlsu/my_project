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
	//选择执白执黑
	int player_color,envir_color;
	cleardevice();
	IMAGE cover1;
	loadimage(&cover1, "./封面3.jpg", 850, 650);
	putimage(0, 0, &cover1);
	setfillcolor(RGB(232, 176, 179));
	solidroundrect(380, 280, 500, 320, 10, 10);
	solidroundrect(380, 340, 500, 380, 10, 10);
	solidroundrect(380, 400, 500, 440, 10, 10);
	settextstyle(30, 0, "楷体");
	setbkmode(TRANSPARENT);
	settextcolor(RGB(37, 89, 139));
	char button1[] = "选择黑白";
	outtextxy(380 + (120 - textwidth(button1)) / 2, 280 + (40 - textheight(button1)) / 2, button1);
	char button2[] = "执黑";
	outtextxy(380 + (120 - textwidth(button2)) / 2, 340 + (40 - textheight(button2)) / 2, button2);
	char button3[] = "执白";
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

	//选择难度
	int level;
	int choose_tan = 0;
	cleardevice();
	IMAGE cover2;
	loadimage(&cover2, "./封面3.jpg", 850, 650);
	putimage(0, 0, &cover2);
	setfillcolor(RGB(232, 176, 179));
	solidroundrect(380, 280, 500, 320, 10, 10);
	solidroundrect(380, 340, 500, 380, 10, 10);
	solidroundrect(380, 400, 500, 440, 10, 10);
	settextstyle(30, 0, "楷体");
	setbkmode(TRANSPARENT);
	settextcolor(RGB(37, 89, 139));
	char button4[] = "贪贪";
	outtextxy(380 + (120 - textwidth(button4)) / 2, 280 + (40 - textheight(button4)) / 2, button4);
	char button5[] = "中等";
	outtextxy(380 + (120 - textwidth(button5)) / 2, 340 + (40 - textheight(button5)) / 2, button5);
	char button6[] = "困难";
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
	int cnt = 0;//记落子次数
	int i = 0;//用于记录该黑白谁落子
	int x, y;
	while (ret == 2)
	{
		//判断是否平局
		if (is_full(board))
		{
			break;
		}
		
		//_printf(board) ;
		ret = win_lose(board,5);
		
		//电脑下（玩家选择执白，电脑执黑）
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
					//局中重新开始功能
					if (msg.x >= 520 && msg.x <= 720 && msg.y >= 100 && msg.y <= 150)
					{
						fuzhi(board);
						PVE_MODE(board);
					}
					//局中返回首页功能
					if (msg.x >= 520 && msg.x <= 720 && msg.y >= 180 && msg.y <= 230)
					{
						fuzhi(board);
						begining(board);
					}

					//人下				
					x = (msg.x - 10) / 30;
					y = (msg.y - 10) / 30;					
					
					if (x == 8 && y == 8 && cnt == 0 && choose_tan != 1)
					{
						HWND warning = GetHWnd();
						MessageBox(warning, "AI不想让你开局下天元，请择他处落子", "提示", MB_OKCANCEL);
						continue;
					}
					
					if (x >= 1 && x <= 15 && y >= 1 && y <= 15)
					{
						if (board[x][y] == NON)
						{
							//printf("人(%d,%d)\n",x,y);
							putchess(board, cnt, player_color, x, y,chess_move2);
							cnt++;
							break;
						}
						else
						{
							HWND warning = GetHWnd();
							MessageBox(warning, "请勿重复落子", "提示", MB_OKCANCEL);
						}
					}
					
				}
			}
		}
		

		ret = win_lose(board, 5);

		//电脑下(玩家选择执黑，电脑执白)
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
	settextstyle(30, 0, "楷体");
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(248, 208, 123));
	setlinecolor(BLACK);
	fillrectangle(160, 510, 360, 560);
	if (ret == 0)
	{
		settextcolor(BLACK);
		char c[] = "黑棋获胜";
		outtextxy(160 + (200 - textwidth(c)) / 2, 510 + (50 - textheight(c)) / 2, c);
	}
	else if(ret == 1)
	{
		settextcolor(WHITE);
		char c[] = "白棋获胜";
		outtextxy(160 + (200 - textwidth(c)) / 2, 510 + (50 - textheight(c)) / 2, c);
	}

	//_printf(board);
	//局末重新开始,返回首页，保存对局功能
	settextstyle(40, 0, "楷体");
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	fillrectangle(520, 260, 720, 310);
	char button7[] = "保存本局";
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


//贪心找出十个最大价值点，在该范围内深入搜索，建立结构数组来存储
typedef struct {
	int score;
	int x;
	int y;
}ass_chess;

ass_chess ass_list[225] = { 0 };
ass_chess ass_10max[20][10] = { 0 };

//用贪心找出10个得分最高的点，便于进一步搜索
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
		
		//测试用模块
		//printf("(%d,%d) ", ass_10max[i].x,ass_10max[i].y);
		//if (i == 9)
		//	printf("\n");

	}

}

//评估棋子函数（搜索用）
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
			//获取Player的最高分
			if (board[i][j] == my_color && small_assess(board,my_color,opponent_color,i,j,envir_color)>max_player)
			{
				max_player = small_assess(board, my_color, opponent_color, i, j,envir_color);
			}
			//获取envir的最高分
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


//极大极小搜索算法&αβ剪枝算法
int bestchess(int board[][16], int P_or_E, int depth, int player_color, int envir_color ,int alpha, int beta,int num)
{
	int i;
	int val=0;
	//ass_chess ass_10max[10] = { 0 };
	//检查是否达到深度or取胜
	
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
					//假设在这下并模拟下一步对面怎么下
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
					//αβ剪枝
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
					//假设在这下并模拟下一步对面怎么下
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
					//αβ剪枝
					if (alpha >= beta)
					{
						break;
					}
				}
			
		}
		return min_val;
	}
		
	else		//错误处理
	{
		return -1;
	}
}


//电脑执棋(深入搜索版)
void E_putchess(int board[][16],int player_color,int envir_color,int level,int cnt)
{
	int best_x, best_y = -1;
	int max_val = -9999999;
	int i;
	int val=0;
	int num = 0;
	
	ass_rank(board, player_color, envir_color, num, envir_color);

	//遍历筛选出的10个点
	for (i = 0; i <10; i++)
	{
			if (board[ass_10max[num][i].x][ass_10max[num][i].y] == NON)
			{
				board[ass_10max[num][i].x][ass_10max[num][i].y] = envir_color;
				//模拟玩家落子
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




//判断棋子是否在界内
int isValid(int i, int j)
{
	return i >= 1 && i < 16 && j >= 1 && j < 16;
}


//评估单个棋子的子函数
int small_assess(int board[][16], int my_color, int opponent_color, int i, int j, int envir_color)
{
	int direction[8][2] = {
	{-1, -1}, //左上
	{-1, 0}, //上
	{-1, 1}, //右上
	{0, -1}, //左
	{0, 1}, //右
	{1, -1}, //左下
	{1, 0}, //下
	{1, 1} //右下
	};
	
	//左上1/4棋盘的位置评分
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
	for (int k = 0; k < 8; k++) { //遍历八个方向
		int count = 1; //连子数
		int empty = 0; //空位数
		int block = 0; //堵住数
		int x = i + direction[k][0]; //沿着方向移动
		int y = j + direction[k][1];
		while (isValid(x, y) && board[x][y] == my_color) { //如果是自己的棋子，连子数加一
			count++;
			x += direction[k][0];
			y += direction[k][1];
		}
		if (isValid(x, y) && board[x][y] == NON) { //如果是空位，空位数加一
			empty++;
		}
		else { //如果是对手的棋子或者出界，堵住数加一
			block++;
		}
		x = i - direction[k][0]; //反向移动
		y = j - direction[k][1];
		while (isValid(x, y) && board[x][y] == my_color) { //如果是自己的棋子，连子数加一
			count++;
			x -= direction[k][0];
			y -= direction[k][1];
		}
		if (isValid(x, y) && board[x][y] == NON) { //如果是空位，空位数加一
			empty++;
		}
		else { //如果是对手的棋子或者出界，堵住数加一
			block++;
		}
		//根据连子数、空位数和堵住数判断棋形，并给分
		if (count == 5) { //连五
			score += FIVE;
		}
		else if (count == 4) { //连四
			if (empty == 2) { //活四
				score += HUO_FOUR;
			}
			else if (empty == 1) { //冲四
				score += CHONG_FOUR;
			}
		}
		else if (count == 3) { //连三
			if (empty == 2) { //活三
				if (block == 0) { //双活三
					score += HUO_THREE * 2;
				}
				else { //单活三
					score += HUO_THREE;
				}
			}
			else if (empty == 1) { //眠三
				score += MIAN_THREE;
			}
		}
		else if (count == 2) { //连二
			if (empty == 2) { //活二
				score += HUO_TWO;
			}
			else if (empty == 1) { //眠二
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


//评估棋子函数(单个&贪心用)
int assess(int board[][16], int player_color, int envir_color, int i, int j, int envir_color1)
{
	int score = small_assess(board, player_color, envir_color, i, j, envir_color) + small_assess(board, envir_color, player_color, i, j, envir_color);
	return score;
}


//电脑执棋（贪心版）
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