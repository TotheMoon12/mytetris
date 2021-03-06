#pragma once
#include "block.h"
#include "board.h"

void DrawBoard(int board[BOARD_ROW_LENGTH][BOARD_COL_LENGTH], HANDLE screenBuffer[2], int screenBufferIndex)
{
	size_t i, j;
	COORD pos;
	DWORD dw;
	OutputDebugStringA("drawboard\n");

	pos.X = 0;
	pos.Y = 0;

	SetConsoleCursorPosition(screenBuffer[screenBufferIndex], pos);

	for (i = 0; i < BOARD_ROW_LENGTH; ++i)
	{
		for (j = 0; j < BOARD_COL_LENGTH; ++j)
		{
			if (board[i][j] == BLOCK)
			{
				WriteFile(screenBuffer[screenBufferIndex], "��", strlen("��"), &dw, NULL);
			}
			else if (board[i][j] == WALL)
			{
				WriteFile(screenBuffer[screenBufferIndex], "��", strlen("��"), &dw, NULL);
			}
			else
			{
				WriteFile(screenBuffer[screenBufferIndex], "  ", strlen("  "), &dw, NULL);
			}
		}

		WriteFile(screenBuffer[screenBufferIndex], "\n", strlen("\n"), &dw, NULL);
	}
}

int CheckCrush(Block block, int board[BOARD_ROW_LENGTH][BOARD_COL_LENGTH])
{
	size_t i;
	COORD pos = block.pos;
	int x, y;

	for (i = 0; i < 4; ++i)
	{
		x = (pos.X + rotationInfo[block.type][block.state][i][0]) / 2;
		y = (pos.Y + rotationInfo[block.type][block.state][i][1]);
		if (x < 1 || x >= BOARD_COL_LENGTH || y >= BOARD_ROW_LENGTH)
		{
			return 1;
		}
		else
		{
			if (y >= 0 && (board[y][x] == WALL || board[y][x] == BLOCK || board[y][x] == WALL || board[y][x] == BLOCK))
			{
				return 1;
			}
		}
	}

	return 0;
}

void updateBoard(int board[BOARD_ROW_LENGTH][BOARD_COL_LENGTH], Block* block)
{
	int i, j;
	int x, y;
	int deletingFirstLine;
	int deletingLineNum;
	int checking;

	for (i = 0; i < 4; ++i)
	{
		x = (block->pos.X + rotationInfo[block->type][block->state][i][0]) / 2;
		y = block->pos.Y + rotationInfo[block->type][block->state][i][1];
		board[y][x] = BLOCK;
	}

	deletingFirstLine = -1;
	deletingLineNum = 0;

	for (i = BOARD_ROW_LENGTH - 2; i >= 0; --i)
	{
		checking = 1;

		for (j = BOARD_COL_LENGTH - 3; j >= 2; --j)
		{
			if (board[i][j] == BLANK)
			{
				checking = 0;
				break;
			}
		}

		if (checking == 1)
		{
			if (deletingFirstLine == -1)
			{
				deletingFirstLine = i;
			}

			++deletingLineNum;
		}
	}
	if (deletingLineNum > 0)
	{
		for (i = deletingFirstLine - deletingLineNum; i >= 0; --i)
		{
			for (j = 2; j < BOARD_COL_LENGTH - 2; ++j)
			{
				board[i + deletingLineNum][j] = board[i][j];
			}
		}
	}
}

int CheckGameState(int board[BOARD_ROW_LENGTH][BOARD_COL_LENGTH])
{
	size_t i;

	for (i = 0; i < BOARD_COL_LENGTH; ++i)
	{
		if (board[0][i] == BLOCK)
		{
			return 1;
		}
	}

	return 0;
}