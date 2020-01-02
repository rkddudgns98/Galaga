#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "Console.h"

#define MAX 30
#define WIDTH 40		//4�� ����� �ϼ���
#define LENGTH 40		
#define BACKCOLOR 0
#define OBJECTCOLOR 15

int SCORE = 0;

struct ST_OBJECT {	//�� ����ü
	int x = 0;
	int y = 0;
	bool bActive = false;
};

ST_OBJECT g_stEnemy[MAX];
ST_OBJECT g_stPlayer;

void Init() {

	SetConsoleSize(WIDTH, LENGTH);	//�ܼ�â ������ ����

	SetTitle("Galaga");	//�ܼ�â ������
	SetColor(BACKCOLOR, OBJECTCOLOR);
}

void Spawn() {
	for (int i = 0; i < MAX; i++) {	//�� �� �ø���
		if (!g_stEnemy[i].bActive) {
			g_stEnemy[i].x = (rand() % (WIDTH / 2)) * 2;	//�� ��ġ ��������
			g_stEnemy[i].y = 0;
			g_stEnemy[i].bActive = true;
			break;
		}
	}
}		//

int EnemyProcess() {
	int count = 0;
	for (int i = 0; i < MAX; i++) {
		if (g_stEnemy[i].bActive) {	//����
			SetColor(BACKCOLOR, i % 15);
			count++;
			GotoXY(g_stEnemy[i].x, g_stEnemy[i].y);
			printf("��");
			g_stEnemy[i].y++;

			if (g_stEnemy[i].y == g_stPlayer.y) {	//�浹
				if (g_stEnemy[i].x == g_stPlayer.x)	//(x,y)��ǥ ���� ��
					g_stPlayer.bActive = false;	//��� off
			}

			if (g_stEnemy[i].y > LENGTH - 2) g_stEnemy[i].bActive = false;	//���Ⱑ ����� ����
		}
	}

	return count;
}

void InputProcess() {
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {	//���ʹ���Ű
		g_stPlayer.x = g_stPlayer.x - 2;
		if (g_stPlayer.x < 0) g_stPlayer.x = 0;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {	//�����ʹ���Ű
		g_stPlayer.x = g_stPlayer.x + 2;
		if (g_stPlayer.x > WIDTH - 2) g_stPlayer.x = WIDTH - 2;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000) {	//���ʹ���Ű
		g_stPlayer.y--;
		if (g_stPlayer.y < 0) g_stPlayer.y = 0;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {	//�Ʒ��ʹ���Ű
		g_stPlayer.y++;
		if (g_stPlayer.y > LENGTH - 2) g_stPlayer.y = LENGTH - 2;
	}
}

void Update() {
	if (g_stPlayer.bActive) {
		SetColor(BACKCOLOR, OBJECTCOLOR);
		GotoXY(g_stPlayer.x, g_stPlayer.y);	//Ŀ���̵�
		printf("��");	//����� ���
	}
	else {
		GotoXY(g_stPlayer.x, g_stPlayer.y);	//Ŀ���̵�
		printf("��");	//����� ���
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
	bool bRet = false;	//���� y/n

	while (1) {
		Clear();

		GotoXY(WIDTH / 4, LENGTH / 2);
		printf("Result Menu");
		GotoXY(WIDTH / 4, LENGTH / 2 + 4);
		printf("Score: %d ", SCORE);
		GotoXY(WIDTH / 4, LENGTH / 2 + 8);
		printf("continue... Y / N");
		
		if (GetAsyncKeyState('Y') & 0x8000) {
			bRet = false;	//true�̸� ���������̴� false��ȯ
			break;
		}

		if (GetAsyncKeyState('N') & 0x8000) {
			bRet = true;	//true�̸� ���������̴� true��ȯ
			break;
		}

		Sleep(50);
	}

	return bRet;
}

void GameMain() {
	int state = 0;	//���ӻ��� on off

	SCORE = 0;

	g_stPlayer.x = WIDTH / 2, g_stPlayer.y = LENGTH - 2;	//ó�� �������ǥ

	g_stPlayer.bActive = true;	//��� on

	srand(time(NULL));

	while (1) {
		Clear();	//�ܻ� �����

		if (g_stPlayer.bActive) {	//��� on�϶�
			Spawn();	//�� ����

			InputProcess();	//�̵�Ű

		}

		state = EnemyProcess();	//�� �̵�

		Score();	//����

		Update();	//�÷��̾� ����

		Sleep(50);	//��

		if (state == 0) break;	//�׾ �� �̵��� 0�� �Ǹ� ���� ��
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

