#pragma once

//��¼����˳����������飬�Ա�������ʷ��¼
typedef struct {
	int x;
	int y;
	int color;
} Chess_move;

void PVP_MODE(int board[][16]);
void putchess(int board[][16], int cnt, int i, int x, int y,Chess_move chess_move[225]);
