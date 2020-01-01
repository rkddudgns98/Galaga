#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Console.h"

#define MAX 30

struct ST_ENEMY {	//적 구조체
	int x = 0;
	int y = 0;
	bool bActive = false;
};

int main() {

	int width = 30, length = 30;	//콘솔 사이즈

	int x = width - 2, y = length - 2;	//처음 비행기좌표

	int bullet = 0, bx = 0, by = 0;	//총알의 좌표

	ST_ENEMY stEnemy[MAX];

	srand(time(NULL));
	
	SetConsoleSize(width, length);	//콘솔창 사이즈 조절

	while (1) {
		Clear();	//잔상 지우기

		for (int i = 0; i < MAX; i++) {	//적 수 늘리기
			if (!stEnemy[i].bActive) {
				stEnemy[i].x = (rand() % (width / 2)) * 2;	//적 위치 랜덤생성
				stEnemy[i].y = 0;
				stEnemy[i].bActive = true;
				break;
			}
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {	//왼쪽방향키
			x--;
			if (x < 0) x = 0;
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {	//오른쪽방향키
			x++;
			if (x > width - 2) x = width - 2;
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000) {	//위쪽방향키
			y--;
			if (y < 0) y = 0;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {	//아래쪽방향키
			y++;
			if (y > length - 2) y = length - 2;
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

		for (int i = 0; i < MAX; i++) {
			if (stEnemy[i].bActive) {	//적기
				GotoXY(stEnemy[i].x, stEnemy[i].y);
				printf("■");
				stEnemy[i].y++;
				if (stEnemy[i].y > length - 2) stEnemy[i].bActive = false;
			}
		}

		GotoXY(x, y);	//커서이동
		printf("▲");	//비행기 출력

		Sleep(50);	//텀
	}

	system("pause");
	return 0;
}

