#pragma once
#define middle 5
#define high 7
#define player 0
#define envir 1
#define FIVE 1000000 //����
#define HUO_FOUR 90000 //����
#define CHONG_FOUR 3000 //����
#define HUO_THREE 10000 //����
#define MIAN_THREE 100 //����
#define HUO_TWO 100 //���
#define MIAN_TWO 10 //�߶�
#define ONE 1 //��һ


void PVE_MODE(int board[][16]);
int bestchess(int board[][16], int P_or_E, int depth, int player_color, int envir_color, int alpha, int beta,int cnt);
void E_putchess(int board[][16], int player_color, int envir_color, int level, int cnt);
int isValid(int i, int j);
int small_assess(int board[][16], int my_color, int opponent_color, int i, int j, int envir_color);
int assess(int board[][16], int player_color, int envir_color,int i, int j, int envir_color1);
void E_putchess_tan(int board[][16], int player_color, int envir_color, int cnt);
int evaluate(int board[][16], int my_color, int opponent_color, int envir_color);
void ass_rank(int board[][16], int my_color, int opponent_color, int cnt, int envir_color);