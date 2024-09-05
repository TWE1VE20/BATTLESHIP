#pragma once
#include <stdio.h>
#ifndef SHIP_GAME_BOARD_H
#define SHIP_GAME_BOARD_H
void reset(int *board) {
	int i, j;
	for (i = 0; i<15; i++) {
		for (j = 0; j<15; j++) {
			board[i * 15 + j] = 0;
		}
	}
}

int setCheck(int *board, int x, int y, int rotate, int size) {
	int i;

	if (rotate == 0)
	{
		for (i = 0; i < size; i++)
		{
			if (board[(y * 15) + (x + i)] == 3)
				return (1);
		}
	}else
	{
		for (i = 0; i < size; i++)
		{
			if (board[((y + i) * 15) + x] == 3)
				return (1);
		}
	}
	return(0);
}

void setBoard(int *board, int x, int y, int rotate, int size, int conform) {
	int i, j;
	for (i = 0; i<15; i++) {
		for (j = 0; j<15; j++) {
			if (i == y && j == x && board[i * 15 + j] != 3)
			{
				printf("¡á");
				continue;
			}
			if (i == y && j == x && board[i * 15 + j] == 3)
			{
				printf("¢Ì");
				continue;
			}
			if (board[i * 15 + j] == 3)
			{
				printf("¢É");
			}
			if (board[i * 15 + j] == 0)
				printf("¡à");
		}
		printf("\n");
	}
	if (conform == 1)
		printf("Do you want to confirm this placement?");
	if (conform != 1)
		printf("SHIP SIZE: %d", size);
}

int isHit(int *xaxis, int *yaxis, int x, int y)
{
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < (5 - i); j++) {
			if (x == xaxis[i * 5 + j] && y == yaxis[i * 5 + j])
			{
				return(1);
			}
		}
	}
	return(0);
}

int xHit(int *xaxis,int *yaxis, int x, int y)
{
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < (5 - i); j++) {
			if (x == xaxis[i * 5 + j] && y == yaxis[i * 5 + j])
			{
				return(j);
			}
		}
	}
}

int yHit(int *yaxis,int *xaxis,int x, int y)
{
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < (5 - i); j++) {
			if (x == xaxis[i * 5 + j] && y == yaxis[i * 5 + j])
			{
				return(i);
			}
		}
	}
}


void printBoard(int *board, int x, int y) {
	int i, j;
	for (i = 0; i<15; i++) {
		for (j = 0; j<15; j++) {
			if (i == y && j == x && board[i * 15 + j] == 0)
			{
				printf("¡á");
				continue;
			}
			if (i == y && j == x && board[i * 15 + j] == 2)
			{
				printf("¢Ì");
				continue;
			}
			if (i == y && j == x && board[i * 15 + j] == 1)
			{
				printf("¡Ü");
				continue;
			}
			if (board[i * 15 + j] == 0)
			{
				printf("¡à");
				continue;
			}
			if (board[i * 15 + j] == 1)
			{
				printf("¡Û");
				continue;
			}
			if (board[i * 15 + j] == 2)
			{
				printf("¢É");
				continue;
			}
		}
		printf("\n");
	}
}

int isSank(int *Ship_Dest, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		if (Ship_Dest[(5 - size) * 5 + i] != 1)
			return(0);
	}
	return(1);
}

int ShipNum(int *shipSank)
{
	int i;
	int shipnum = 4;
	for (i = 0; i < 4; i++)
	{
		if (shipSank[i] == 1)
			shipnum -= 1;
	}
	return (shipnum);
}

int ammoNum(int *shipSank)
{
	int i;
	int ammonum = 5;
	for (i = 0; i < 4; i++)
	{
		if (shipSank[i] == 1 && i == 1)
			ammonum -= 2;
		if (shipSank[i] == 1 && i != 1)	//i = 1 is battleship
			ammonum -= 1;
	}
	return (ammonum);
}

void winner(int p_num)
{
	printf("PLAYER %d PIONEERED THE SEA\n",p_num);
}
#endif // SHIP_GAME_BOARD_H
