#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "supportingconsole.h"
#include "ship_game_board.h"
//#define DEBUG

HANDLE wHnd;    // Handle to write to the console.
HANDLE rHnd;    // Handle to read from the console.

int main(int argc, char* argv[]) {
	int x = 0;
	int y = 0;
	int rotate = 0;	//1: 세로 0: 가로
	int i, j;
	int board1[15][15];	//board of first player 0:nothig, 1:player 2:ship destroyed 3;ship placed
	int board2[15][15]; //board of second player 0:nothig, 1:player 2:ship destroyed 3;ship placed
	int conform1 = 0;	//bool: first player ship ready
	int conform2 = 0;	//bool: second player ship ready 
	int print1 = 0;
	int print2 = 0;
	int win = 0;

	//Ships: Aircraft carrier(5), Battleship(4), Cruiser(3), Destroyer(2)

	//board 1 ships
	int ship1_placed = 0;
	int Ship1_x[4][5];		//x-axis of first player's ship
	int Ship1_y[4][5];		//y-axis of first player's ship
	int Ship1_Dest[4][5];	//Destroyed spot of first player's ship
	int Ship1_Sanked[4];	//Sanked or not of first player's ship
	int remaing_ammo1;
	char string1[50] = "";

	//board 2 ships
	int ship2_placed = 0;
	int Ship2_x[4][5];		//x-axis of second player's ship
	int Ship2_y[4][5];		//y-axis of second player's ship
	int Ship2_Dest[4][5];	//Destroyed spot of second player's ship
	int Ship2_Sanked[4];	//Sanked or not of second player's ship
	int remaing_ammo2;
	char string2[50] = "";

	reset(board1[0]);
	reset(board2[0]);

	// Set up the handles for reading/writing:
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	// Change the window title:
	//SetConsoleTitle();
	// Set up the required window size:    
	SMALL_RECT windowSize = { 0, 0, 1000, 1000 };
	SetConsoleWindowInfo(wHnd, 1, &windowSize);
	// Change the console window size:        
	// Create a COORD to hold the buffer size:    
	COORD bufferSize = { 100, 100 };
	SetConsoleScreenBufferSize(wHnd, bufferSize);

	//placing first player ships
	system("cls");
	printf("First Player");
	Sleep(1000);
	printBoard(board1[0], x, y);
	ship1_placed = 0;
	while (1) {
		if (IsKeyPressed(VK_UP))
		{
			if (y > 0)
				y--;
		}
		if (IsKeyPressed(VK_DOWN))
		{
			if (rotate == 1)
			{
				if (y < (10 + ship1_placed))
					y++;
			}
			else
			{
				if (y < 14)
					y++;
			}
		}
		if (IsKeyPressed(VK_LEFT))
		{
			if (x > 0)
				x--;
		}
		if (IsKeyPressed(VK_RIGHT))
		{
			if (rotate == 0)
			{
				if (x < (10 + ship1_placed))
					x++;
			}
			else {
				if (x < 14)
					x++;
			}
		}
		if (IsKeyPressed(0x58))			//x key
		{
			if (rotate == 1)
			{
				if (y < (10 + ship1_placed))
					rotate = 0;
			}
			else
			{
				if (x < (10 + ship1_placed))
					rotate = 1;
			}
		}
		if (IsKeyPressed(0x5A))			//z key
		{
			if (ship1_placed == 4)
				ship1_placed += 1;
			if (ship1_placed < 4)
			{
				if (setCheck(board1[0], x, y, rotate, (5 - ship1_placed)) == 0)
				{
					if (rotate == 0)
					{
						for (i = 0; i < (5 - ship1_placed); i++)
						{
							board1[y][x + i] = 3;
							Ship1_y[ship1_placed][i] = y;
							Ship1_x[ship1_placed][i] = (x + i);
						}
					}
					else
					{
						for (i = 0; i < (5 - ship1_placed); i++)
						{
							board1[(y + i)][x] = 3;
							Ship1_y[ship1_placed][i] = (y + i);
							Ship1_x[ship1_placed][i] = x;
						}
					}
					ship1_placed += 1;
				}
			}
			if (ship1_placed == 4)
			{
				conform1 = 1;
			}
		}
		if (IsKeyPressed(0x43))			//c key
		{
			if (ship1_placed != 0)
			{
				ship1_placed -= 1;
				for (i = 0; i < (5 - ship1_placed); i++)
				{
					board1[Ship1_y[ship1_placed][i]][Ship1_x[ship1_placed][i]] = 0;
					Ship1_x[ship1_placed][i] = 0;
					Ship1_y[ship1_placed][i] = 0;
				}
				conform1 = 0;
			}
		}
		system("cls");
		if (ship1_placed == 5)
			break;
		printf("PLAYER1\n");
		if (rotate == 0)
			printf("SHIP DIRECTION: HORIZONTAL\n");
		if (rotate == 1)
			printf("SHIP DIRECTION: VERTICAL\n");
		setBoard(board1[0], x, y, rotate, (5 - ship1_placed), conform1);
		Sleep(50);
	}

	system("cls");
	printf("Second Player");
	Sleep(1000);
	x = 0;
	y = 0;
	rotate == 0;

	//placing second player ships
	printBoard(board2[0], x, y);
	ship2_placed = 0;
	while (1) {
		if (IsKeyPressed(VK_UP))
		{
			if (y > 0)
				y--;
		}
		if (IsKeyPressed(VK_DOWN))
		{
			if (rotate == 1)
			{
				if (y < (10 + ship2_placed))
					y++;
			}
			else
			{
				if (y < 14)
					y++;
			}
		}
		if (IsKeyPressed(VK_LEFT))
		{
			if (x > 0)
				x--;
		}
		if (IsKeyPressed(VK_RIGHT))
		{
			if (rotate == 0)
			{
				if (x < (10 + ship2_placed))
					x++;
			}
			else {
				if (x < 14)
					x++;
			}
		}
		if (IsKeyPressed(0x58))			//x key
		{
			if (rotate == 1)
			{
				if (y < (10 + ship2_placed))
					rotate = 0;
			}
			else
			{
				if (x < (10 + ship2_placed))
					rotate = 1;
			}
		}
		if (IsKeyPressed(0x5A))			//z key
		{
			if (ship2_placed == 4)
				ship2_placed += 1;
			if (ship2_placed < 4)
			{
				if (setCheck(board2[0], x, y, rotate, (5 - ship2_placed)) == 0)
				{
					if (rotate == 0)
					{
						for (i = 0; i < (5 - ship2_placed); i++)
						{
							board2[y][x + i] = 3;
							Ship2_x[ship2_placed][i] = (x + i);
							Ship2_y[ship2_placed][i] = y;
						}
					}
					else
					{
						for (i = 0; i < (5 - ship2_placed); i++)
						{
							board2[(y + i)][x] = 3;
							Ship2_x[ship2_placed][i] = x;
							Ship2_y[ship2_placed][i] = (y + i);
						}
					}
					ship2_placed += 1;
					if (ship2_placed == 4)
					{
						conform2 = 1;
					}
				}
			}
		}
		if (IsKeyPressed(0x43))			//c key
		{
			if (ship2_placed != 0)
			{
				ship2_placed -= 1;
				for (i = 0; i < (5 - ship2_placed); i++)
				{
					board2[Ship2_y[ship2_placed][i]][Ship2_x[ship2_placed][i]] = 0;
					Ship2_x[ship2_placed][i] = 0;
					Ship2_y[ship2_placed][i] = 0;
				}
				conform2 = 0;
			}
		}
		system("cls");
		if (ship2_placed == 5)
			break;
		printf("PLAYER2\n");
		if (rotate == 0)
			printf("SHIP DIRECTION: HORIZONTAL\n");
		if (rotate == 1)
			printf("SHIP DIRECTION: VERTICAL\n");
		setBoard(board2[0], x, y, rotate, 5 - ship2_placed, conform2);
		Sleep(50);
	}

	system("cls");
	printf("GAME START");
	Sleep(1000);
	x = 0;
	y = 0;
	reset(board1[0]);
	reset(board2[0]);

	//finding ships

	while (1) {
		system("cls");
		printf("First Player Turn");
		Sleep(1000);

		x = 0;
		y = 0;
		remaing_ammo1 = ammoNum(Ship1_Sanked);
		// destroy second player's ship
		while (remaing_ammo1 > 0) {
			if (IsKeyPressed(VK_UP))
			{
				if (y > 0)
					y--;
			}
			if (IsKeyPressed(VK_DOWN))
			{
				if (y < 14)
					y++;
			}
			if (IsKeyPressed(VK_LEFT))
			{
				if (x > 0)
					x--;
			}
			if (IsKeyPressed(VK_RIGHT))
			{
				if (x < 14)
					x++;
			}
			if (IsKeyPressed(0x5A))
			{
				print1 = 0;
				if (isHit(Ship2_x[0], Ship2_y[0], x, y) == 1 && board2[y][x] != 2)
				{
					board2[y][x] = 2;
					Ship2_Dest[yHit(Ship2_y[0], Ship2_x[0], x, y)][xHit(Ship2_x[0], Ship2_y[0], x, y)] = 1;
					remaing_ammo1 -= 1;
					for (i = 5; i >= 2; i--)
					{
						if (isSank(Ship2_Dest[0], i) == 1 && Ship2_Sanked[5 - i] != 1)
						{
							Ship2_Sanked[5 - i] = 1;
							if (i == 5)
								strcpy(string1, "You destroyed enemy Aircraft carrier");
							if (i == 4)
								strcpy(string1, "You destroyed enemy Battleship");
							if (i == 3)
								strcpy(string1, "You destroyed enemy Cruiser");
							if (i == 2)
								strcpy(string1, "You destroyed enemy Destroyer");
							print1 = 1;
						}
					}
				}
				if (board2[y][x] == 0)
				{
					board2[y][x] = 1;
					strcpy(string1, "Nothing hit");
					print1 = 1;
					remaing_ammo1 -= 1;
				}
			}
			system("cls");
			printf("PLAYER 1 TURN\n");
			printf("REMAING SHELL: %d\n", remaing_ammo1);
			printf("x:%d y:%d\n", x, y);
			printBoard(board2[0], x, y);
#ifdef DEBUG
			for (i = 0; i < 4; i++)
			{
				for (j = 0; j < (5 - i); j++)
				{
					printf("x%d: %d y%d: %d dest: %d\n", j, Ship2_x[i][j], i, Ship2_y[i][j], Ship2_Dest[i][j]);
				}
				printf("%dsank: %d\n", i + 1, Ship2_Sanked[i]);
			}
#endif DEBUG
			if (print1 == 1)
				printf("%s\n", string1);
			if (ShipNum(Ship2_Sanked) == 0)
			{
				win = 1;
				break;
			}
			Sleep(50);
		}
		Sleep(2000);
		if (win > 0)
			break;

		system("cls");
		printf("Second Player Turn");
		Sleep(1000);

		x = 0;
		y = 0;
		remaing_ammo2 = ammoNum(Ship2_Sanked);
		// destroy second player's ship
		while (remaing_ammo2 > 0) {
			if (IsKeyPressed(VK_UP))
			{
				if (y > 0)
					y--;
			}
			if (IsKeyPressed(VK_DOWN))
			{
				if (y < 14)
					y++;
			}
			if (IsKeyPressed(VK_LEFT))
			{
				if (x > 0)
					x--;
			}
			if (IsKeyPressed(VK_RIGHT))
			{
				if (x < 14)
					x++;
			}
			if (IsKeyPressed(0x5A))
			{
				print2 = 0;
				if (isHit(Ship1_x[0], Ship1_y[0], x, y) == 1 && board1[y][x] != 2)
				{
					board1[y][x] = 2;
					Ship1_Dest[yHit(Ship1_y[0], Ship1_x[0], x, y)][xHit(Ship1_x[0], Ship1_y[0], x, y)] = 1;
					remaing_ammo2 -= 1;
					for (i = 5; i >= 2; i--)
					{
						if (isSank(Ship1_Dest[0], i) == 1 && Ship1_Sanked[5 - i] != 1)
						{
							Ship1_Sanked[5 - i] = 1;
							if (i == 5)
								strcpy(string2, "You destroyed enemy Aircraft carrier");
							if (i == 4)
								strcpy(string2, "You destroyed enemy Battleship");
							if (i == 3)
								strcpy(string2, "You destroyed enemy Cruiser");
							if (i == 2)
								strcpy(string2, "You destroyed enemy Destroyer");
							print1 = 2;
						}
					}
				}
				if (board1[y][x] == 0)
				{
					board1[y][x] = 1;
					strcpy(string2, "Nothing hit");
					print2 = 1;
					remaing_ammo2 -= 1;
				}
			}
			system("cls");
			printf("PLAYER 2 TURN\n");
			printf("REMAING SHELL: %d\n", remaing_ammo2);
			printf("x:%d y:%d\n", x, y);
			printBoard(board1[0], x, y);
#ifdef DEBUG
			for (i = 0; i < 4; i++)
			{
				for (j = 0; j < (5 - i); j++)
				{
					printf("x%d: %d y%d: %d dest: %d\n", j, Ship1_x[i][j], i, Ship1_y[i][j], Ship1_Dest[i][j]);
				}
				printf("%dsank: %d\n", i + 1, Ship1_Sanked[i]);
			}
#endif DEBUG
			if (print2 == 1)
				printf("%s\n", string2);
			if (ShipNum(Ship1_Sanked) == 0)
			{
				win = 2;
				break;
			}
			Sleep(50);
		}
		Sleep(2000);
		if (win > 0)
			break;
	}
	Sleep(2000);

	system("cls");

	winner(win);

	return(0);
}