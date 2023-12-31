#pragma once

typedef struct {
    char* filename;
    time_t mtime;
} FileEntry;

void save(Chess_move chess_move[225], int cnt, int mode_who);
void review(int board[][16]);
int compare_time(const struct dirent** file1, const struct dirent** file2);
void chessboard_in_review(int mode_who);
void putchess_in_review(int board[][16], int mode_who);