#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Console.h"

#define MAX 40
#define WIDTH 50
#define LENGTH 50

int SCORE = 0;

struct ST_OBJECT {	//�� ����ü
	int x = 0;
	int y = 0;
	bool bActive = false;
};

ST_OBJECT g_stEnemy[MAX];
ST_OBJECT g_stPlayer;

void Init() {
	g_stPlayer.x = WIDTH - 2, g_stPlayer.y = LENGTH - 2;	//ó�� �������ǥ
	g_stPlayer.bActive = true;	//��� on
	srand(time(NULL));
	SetConsoleSize(WIDTH, LENGTH);	//�ܼ�â ������ ����
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

int EnemyProcess() {
	int count = 0;
	for (int i = 0; i < MAX; i++) {
		if (g_stEnemy[i].bActive) {	//����
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

void Update() {
	if (g_stPlayer.bActive) {
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

int main() {

	Init();	//initialize

	int state = 0;	//���ӻ��� on off

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

	system("pause");
	return 0;
}

