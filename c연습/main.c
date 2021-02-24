#include <conio.h>
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
	int key;
	int board[BOARD_ROW_LENGTH][BOARD_COL_LENGTH] = { 0, };
	int curBlockState;
	int screenBufferIndex = 0;
	Block block;
	COORD coor = { 0 , 0 };
	DWORD dw;
	HANDLE screenBuffer[2];
	clock_t start, end;
	
	screenBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	screenBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	srand(time(NULL));

	initalizeBlock(&block);

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

	DrawBoard(board, screenBuffer, screenBufferIndex);
	DrawBlock(block, screenBuffer, screenBufferIndex);
	SetConsoleActiveScreenBuffer(screenBuffer[screenBufferIndex]);
	screenBufferIndex = (screenBufferIndex + 1) % 2;
	start = clock();

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

						updateBoard(board, &block);

						if (CheckGameState(board) == 1)
						{
							goto gameEnd;
						}

						initalizeBlock(&block);						
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

							updateBoard(board, &block);

							if (CheckGameState(board) == 1)
							{
								goto gameEnd;
							}

							initalizeBlock(&block);
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

		end = clock();
		
		if (end - start >= 1000)
		{
			++block.pos.Y;
			if (CheckCrush(block, board) == 1)
			{
				--block.pos.Y;

				updateBoard(board, &block);

				if (CheckGameState(board) == 1)
				{
					goto gameEnd;
				}

				initalizeBlock(&block);
			}

			DrawBoard(board, screenBuffer, screenBufferIndex);
			DrawBlock(block, screenBuffer, screenBufferIndex);

			SetConsoleActiveScreenBuffer(screenBuffer[screenBufferIndex]);
			screenBufferIndex = (screenBufferIndex + 1) % 2;

			/* 다음 화면버퍼 내용을 지워두기 */
			FillConsoleOutputCharacter(screenBuffer[screenBufferIndex], ' ', 100 * 100, coor, &dw);
			start = clock();
		}
	}

gameEnd:
	screenBufferIndex = (screenBufferIndex + 1) % 2;
	WriteFile(screenBuffer[screenBufferIndex], "Game End", strlen("Game End"), &dw, NULL);
	SetConsoleActiveScreenBuffer(screenBuffer[screenBufferIndex]);
	Sleep(2000);

	CloseHandle(screenBuffer[0]);
	CloseHandle(screenBuffer[1]);

	return 0;
}