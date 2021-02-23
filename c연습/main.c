#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"


enum EKeyDirection
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	SPACE = 32
};

int main(void)
{
	int i, j;
	int deletingFirstLine, deletingLineNum;
	int x, y;
	int key;
	int board[BOARD_ROW_LENGTH][BOARD_COL_LENGTH] = { 0, };
	int curBlockState;
	int checking;
	int screenBufferIndex = 0;
	Block block;
	COORD coor = { 0 , 0 };
	DWORD dw;
	HANDLE screenBuffer[2];
	
	
	screenBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	screenBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);


	srand(time(NULL));

	block.pos.X = 10;
	block.pos.Y = 0;
	block.state = 0;
	block.type = rand() % 7;

	/* Initialize Board */
	for (i = 0; i < BOARD_ROW_LENGTH; ++i)
	{
		for (j = 0; j < BOARD_COL_LENGTH; ++j)
		{
			if (j == 0 || j == 1 || j == 12 || j == 13 || i == 20)
			{
				board[i][j] = WALL;
			}
		}
	}

	while (1)
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == 224 || key == 32)
			{
				if (key != 32)
				{
					key = _getch();
				}

				switch (key)
				{
				case UP:
					curBlockState = block.state;
					block.state = (block.state + 1) % 4;
					if (CheckCrush(block, board) == 1)
					{
						block.state = curBlockState;
					}
					break;
				case DOWN:
					++block.pos.Y;
					if (CheckCrush(block, board) == 1)
					{
						--block.pos.Y;

						for (i = 0; i < 4; ++i)
						{
							x = (block.pos.X + rotationInfo[block.type][block.state][i][0]) / 2;
							y = block.pos.Y + rotationInfo[block.type][block.state][i][1];
							board[y][x] = BLOCK;
						}

						block.pos.X = 10;
						block.pos.Y = 1;
						block.state = 0;
						block.type = rand() % 7;

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
					break;
				case LEFT:
					block.pos.X -= 2;
					if (CheckCrush(block, board) == 1)
					{
						block.pos.X += 2;
					}
					break;
				case RIGHT:
					block.pos.X += 2;
					if (CheckCrush(block, board) == 1)
					{
						block.pos.X -= 2;
					}
					break;
				case SPACE:
					while (1)
					{
						++block.pos.Y;

						if (CheckCrush(block, board) == 1)
						{
							--block.pos.Y;

							for (i = 0; i < 4; ++i)
							{
								x = (block.pos.X + rotationInfo[block.type][block.state][i][0]) / 2;
								y = block.pos.Y + rotationInfo[block.type][block.state][i][1];
								board[y][x] = BLOCK;
							}

							block.pos.X = 10;
							block.pos.Y = 1;
							block.state = 0;
							block.type = rand() % 7;

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

							break;
						}
					}
					break;
				default:
					break;
				}
				
				DrawBoard(board, screenBuffer, screenBufferIndex);
				DrawBlock(block, screenBuffer, screenBufferIndex);

				SetConsoleActiveScreenBuffer(screenBuffer[screenBufferIndex]);
				screenBufferIndex = (screenBufferIndex + 1) % 2;

				/* 다음 화면버퍼 내용을 지워두기 */
				FillConsoleOutputCharacter(screenBuffer[screenBufferIndex], ' ', 100 * 100, coor, &dw); 
			}
		}
	}

	CloseHandle(screenBuffer[0]);
	CloseHandle(screenBuffer[1]);

	return 0;
}