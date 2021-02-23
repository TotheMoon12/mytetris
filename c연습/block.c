#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "block.h"

const int rotationInfo[BLOCK_NUM][ROTATION_NUM][POINT_NUM][2] = {
	{
		/* д╟ */
		{
			{-2,0},{0,0},{0,-1},{2,0} 
		},
		{
			{-2,0}, {0,0}, {0,-1} ,{0,1}
		},
		{
			{-2,0},	{0,0},	{2,0},	{0,1}
		},
		{
			{0,-1},{0,0},{2,0},{0,1}
		}
	},
	{
		/* z */
		{
			{0,1},	{0,0},	{2,0},	{2,-1}
		},
		{
			{-2,0}, {0,0}, {0,1} ,{2,1}
		},
		{
			{-2,1},{-2,0},{0,0},{0,-1}
		},
		{
			{-2,-1},{0,-1},{0,0},{2,0}
		}
	},
	{
		/* s */
		{
			{0,-1},	{0,0},	{2,0},	{2,1}
		},
		{
			{-2,1}, {0,1}, {0,0} ,{2,0}
		},
		{
			{-2,-1},{-2,0},{0,0},{0,1}
		},
		{
			{-2,0},{0,0},{0,-1},{2,-1}
		}
	},
	{
		/* I */
		{
			{-2,0},	{0,0},	{2,0},	{4,0}
		},
		{
			{0,-1}, {0,0}, {0,1} ,{0,2}
		},
		{
			{-4,0},{-2,0},{0,0},{2,0}
		},
		{
			{0,-2},{0,-1},{0,0},{0,1}
		}
	},
	{
		/* L */
		{
			{0,-1},	{0,0},	{0,1},	{2,1}
		},
		{
			{-2,1}, {-2,0}, {0,0} ,{2,0}
		},
		{
			{-2,-1},{0,-1},{0,0},{0,1}
		},
		{
			{-2,0},{0,0},{2,0},{2,-1}
		}
	},
	{
		/* J */
		{
			{-2,1},	{0,1},	{0,0},	{0,-1}
		},
		{
			{-2,-1}, {-2,0}, {0,0} ,{2,0}
		},
		{
			{0,1},{0,0},{0,-1},{2,-1}
		},
		{
			{-2,0},{0,0},{2,0},{2,1}
		}
	},
	{
		/* д▒ */
		{
			{0,0},	{2,0},	{0,1},	{2,1}
		},
		{
			{0,0},	{2,0},	{0,1},	{2,1}
		},
		{
			{0,0},	{2,0},	{0,1},	{2,1}
		},
		{
			{0,0},	{2,0},	{0,1},	{2,1}
		}
	},

};

void DrawBlock(Block block, HANDLE screenBuffer[2], int screenBufferIndex)
{
	size_t i;
	COORD tempPos;
	DWORD dw;


	for (i = 0; i < 4; ++i)
	{
		tempPos = block.pos;
		tempPos.X += rotationInfo[block.type][block.state][i][0];
		tempPos.Y += rotationInfo[block.type][block.state][i][1];
		/*SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tempPos);
		printf("бр");*/
		if (tempPos.Y < 0)
		{
			continue;
		}
		SetConsoleCursorPosition(screenBuffer[screenBufferIndex], tempPos);
		WriteFile(screenBuffer[screenBufferIndex], "бр", strlen("бр"), &dw, NULL);
		
		char temp[100];
		char temp2[100];
		char temp3[100];
		char temp4[100];
		sprintf(temp, "%d", tempPos.X);
		sprintf(temp2, "%d", tempPos.Y);
		sprintf(temp3, "%s", "\nX : ");
		sprintf(temp4, "%s", "\nY : ");
		OutputDebugStringA(temp3);
		OutputDebugStringA(temp);
		OutputDebugStringA(temp4);
		OutputDebugStringA(temp2);
		
	}
	OutputDebugStringA("\n===================\n");
	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), block.pos);
	SetConsoleCursorPosition(screenBuffer[screenBufferIndex], block.pos);
}
