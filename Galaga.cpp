#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "Console.h"

#define MAX 30
#define WIDTH 40		//4의 배수로 하세요
#define LENGTH 40		
#define BACKCOLOR 0
#define OBJECTCOLOR 15

int SCORE = 0;

struct ST_OBJECT {	//적 구조체
	int x = 0;
	int y = 0;
	bool bActive = false;
};

ST_OBJECT g_stEnemy[MAX];
ST_OBJECT g_stPlayer;

void Init() {

	SetConsoleSize(WIDTH, LENGTH);	//콘솔창 사이즈 조절

	SetTitle("Galaga");	//콘솔창 제목설정
	SetColor(BACKCOLOR, OBJECTCOLOR);
}

void Spawn() {
	for (int i = 0; i < MAX; i++) {	//적 수 늘리기
		if (!g_stEnemy[i].bActive) {
			g_stEnemy[i].x = (rand() % (WIDTH / 2)) * 2;	//적 위치 랜덤생성
			g_stEnemy[i].y = 0;
			g_stEnemy[i].bActive = true;
			break;
		}
	}
}		//

int EnemyProcess() {
	int count = 0;
	for (int i = 0; i < MAX; i++) {
		if (g_stEnemy[i].bActive) {	//적기
			SetColor(BACKCOLOR, i % 15);
			count++;
			GotoXY(g_stEnemy[i].x, g_stEnemy[i].y);
			printf("☆");
			g_stEnemy[i].y++;

			if (g_stEnemy[i].y == g_stPlayer.y) {	//충돌
				if (g_stEnemy[i].x == g_stPlayer.x)	//(x,y)좌표 같을 때
					g_stPlayer.bActive = false;	//목숨 off
			}

			if (g_stEnemy[i].y > LENGTH - 2) g_stEnemy[i].bActive = false;	//적기가 벗어나면 삭제
		}
	}

	return count;
}

void InputProcess() {
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {	//왼쪽방향키
		g_stPlayer.x = g_stPlayer.x - 2;
		if (g_stPlayer.x < 0) g_stPlayer.x = 0;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {	//오른쪽방향키
		g_stPlayer.x = g_stPlayer.x + 2;
		if (g_stPlayer.x > WIDTH - 2) g_stPlayer.x = WIDTH - 2;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000) {	//위쪽방향키
		g_stPlayer.y--;
		if (g_stPlayer.y < 0) g_stPlayer.y = 0;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {	//아래쪽방향키
		g_stPlayer.y++;
		if (g_stPlayer.y > LENGTH - 2) g_stPlayer.y = LENGTH - 2;
	}
}

void Update() {
	if (g_stPlayer.bActive) {
		SetColor(BACKCOLOR, OBJECTCOLOR);
		GotoXY(g_stPlayer.x, g_stPlayer.y);	//커서이동
		printf("▲");	//비행기 출력
	}
	else {
		GotoXY(g_stPlayer.x, g_stPlayer.y);	//커서이동
		printf("▒");	//비행기 출력
	}
}

void Score() {
	if(g_stPlayer.bActive)	SCORE++;
	GotoXY(0, 0);
	printf("SCORE: %d", SCORE);
}

void StartMenu() {
	while (_kbhit()) _getch();

	while (1) {
		Clear();
		GotoXY(WIDTH / 4, LENGTH / 3);
		printf("Galaga");
		GotoXY(WIDTH / 4, LENGTH / 2);
		printf("Press any key");
		Sleep(50);
		if (_kbhit()) break;
	}
}

bool ResultMenu() {
	bool bRet = false;	//재경기 y/n

	while (1) {
		Clear();

		GotoXY(WIDTH / 4, LENGTH / 2);
		printf("Result Menu");
		GotoXY(WIDTH / 4, LENGTH / 2 + 4);
		printf("Score: %d ", SCORE);
		GotoXY(WIDTH / 4, LENGTH / 2 + 8);
		printf("continue... Y / N");
		
		if (GetAsyncKeyState('Y') & 0x8000) {
			bRet = false;	//true이면 게임종료이니 false반환
			break;
		}

		if (GetAsyncKeyState('N') & 0x8000) {
			bRet = true;	//true이면 게임종료이니 true반환
			break;
		}

		Sleep(50);
	}

	return bRet;
}

void GameMain() {
	int state = 0;	//게임상태 on off

	SCORE = 0;

	g_stPlayer.x = WIDTH / 2, g_stPlayer.y = LENGTH - 2;	//처음 비행기좌표

	g_stPlayer.bActive = true;	//목숨 on

	srand(time(NULL));

	while (1) {
		Clear();	//잔상 지우기

		if (g_stPlayer.bActive) {	//목숨 on일때
			Spawn();	//적 생성

			InputProcess();	//이동키

		}

		state = EnemyProcess();	//적 이동

		Score();	//점수

		Update();	//플레이어 생성

		Sleep(50);	//텀

		if (state == 0) break;	//죽어서 적 이동이 0이 되면 게임 끝
	}
}

int main() {

	Init();	//initialize

	while (1) {
		StartMenu();

		GameMain();

		if (ResultMenu()) break;
	}

	system("pause");

	return 0;
}

