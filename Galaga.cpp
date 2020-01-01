#include <stdio.h>
#include <stdlib.h>

#include "Console.h"

int main() {

	int x = 14, y = 28;	//처음 비행기좌표
	int bullet = 0, bx = 0, by = 0;	//총알의 좌표
	
	SetConsoleSize(30, 30);	//콘솔창 사이즈 조절

	while (1) {

		Clear();	//잔상 지우기

		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {	//왼쪽방향키
			x--;
			if (x < 0) x = 0;
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {	//오른쪽방향키
			x++;
			if (x > 28) x = 28;
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000) {	//위쪽방향키
			y--;
			if (y < 0) y = 0;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {	//아래쪽방향키
			y++;
			if (y > 28) y = 28;
		}

		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {	//스페이스바
			if (!bullet) {	//총알이 없을때
				bx = x;		//총알의 x좌표
				by = y - 1;	//총알의 y좌표
				bullet = true;
			}
		}

		if (bullet) {	//총알쏘기
			GotoXY(bx, by);	//커서이동
			printf("＊");	//총알쏘기
			by--;	//총알 이동
			if (by < 0) bullet = false;	//화면을 벗어났을때 총알지우기
		}

		GotoXY(x, y);	//커서이동
		printf("▲");	//비행기 출력

		Sleep(50);	//텀
	}

	system("pause");
	return 0;
}

