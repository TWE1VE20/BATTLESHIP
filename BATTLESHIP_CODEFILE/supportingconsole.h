#pragma once
#include <stdio.h>
#include <windows.h>
#ifndef SUPPORTINGCONSOLE_H
#define SUPPORTINGCONSOLE_H

int IsKeyPressed(int key) {
	return(GetAsyncKeyState(key) & 0x8000) == 0x8000;
}

void GotoXY(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

#endif // SUPPORTINGCONSOLE_H
