#pragma once
#define middle 5
#define high 7
#define player 0
#define envir 1
#define FIVE 1000000 //连五
#define HUO_FOUR 90000 //活四
#define CHONG_FOUR 3000 //冲四
#define HUO_THREE 10000 //活三
#define MIAN_THREE 100 //眠三
#define HUO_TWO 100 //活二
#define MIAN_TWO 10 //眠二
#define ONE 1 //单一


void PVE_MODE(int board[][16]);
int bestchess(int board[][16], int P_or_E, int depth, int player_color, int envir_color, int alpha, int beta,int cnt);
void E_putchess(int board[][16], int player_color, int envir_color, int level, int cnt);
int isValid(int i, int j);
int small_assess(int board[][16], int my_color, int opponent_color, int i, int j, int envir_color);
int assess(int board[][16], int player_color, int envir_color,int i, int j, int envir_color1);
void E_putchess_tan(int board[][16], int player_color, int envir_color, int cnt);
int evaluate(int board[][16], int my_color, int opponent_color, int envir_color);
void ass_rank(int board[][16], int my_color, int opponent_color, int cnt, int envir_color);