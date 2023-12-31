#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define BLACK_C 0
#define WHITE_C 1
#define NON 6
#define RAD 10

void begining(int board[][16]);
void chessboard(void);
void _printf(int board[][16]);
void fuzhi(int board[][16]);
int win_lose(int board[][16],int num);
void developer_statement(int board[][16]);
int is_full(int board[][16]);