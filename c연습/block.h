#pragma once
#include <stdio.h>
#include <Windows.h>
#define BLOCK_NUM 7
#define ROTATION_NUM 4
#define POINT_NUM 4

typedef struct Block
{
	COORD pos;
	int state;
	int type;
}Block;

void DrawBlock(Block block, HANDLE screenBuffer[2], int screenBufferIndex);
extern const int rotationInfo[BLOCK_NUM][ROTATION_NUM][POINT_NUM][2];