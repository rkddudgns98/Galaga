#include <stdio.h>
#include <stdlib.h>

#include "Console.h"

int main() {

	int x = 14, y = 28;
	
	SetConsoleSize(30, 30);

	while (1) {

		Clear();

		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			x--;
			if (x < 0) x = 0;
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			x++;
			if (x > 28) x = 28;
		}

		GotoXY(x, y);
		printf("бу");

		Sleep(50);
	}

	system("pause");
	return 0;
}

