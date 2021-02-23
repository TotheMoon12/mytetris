#pragma once
#include "block.h"

#define BOARD_COL_LENGTH 14
#define BOARD_ROW_LENGTH 21

enum EBoardState
{
	BLANK,
	BLOCK,
	WALL
};

void DrawBoard(int board[BOARD_ROW_LENGTH][BOARD_COL_LENGTH], HANDLE screenBuffer[2], int screenBufferIndex);
int CheckCrush(Block block, int board[BOARD_ROW_LENGTH][BOARD_COL_LENGTH]);