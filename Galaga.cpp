#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Console.h"

#define MAX 30

struct ST_ENEMY {	//�� ����ü
	int x = 0;
	int y = 0;
	bool bActive = false;
};

int main() {

	int width = 30, length = 30;	//�ܼ� ������

	int x = width - 2, y = length - 2;	//ó�� �������ǥ

	int bullet = 0, bx = 0, by = 0;	//�Ѿ��� ��ǥ

	ST_ENEMY stEnemy[MAX];

	srand(time(NULL));
	
	SetConsoleSize(width, length);	//�ܼ�â ������ ����

	while (1) {
		Clear();	//�ܻ� �����

		for (int i = 0; i < MAX; i++) {	//�� �� �ø���
			if (!stEnemy[i].bActive) {
				stEnemy[i].x = (rand() % (width / 2)) * 2;	//�� ��ġ ��������
				stEnemy[i].y = 0;
				stEnemy[i].bActive = true;
				break;
			}
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {	//���ʹ���Ű
			x--;
			if (x < 0) x = 0;
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {	//�����ʹ���Ű
			x++;
			if (x > width - 2) x = width - 2;
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000) {	//���ʹ���Ű
			y--;
			if (y < 0) y = 0;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {	//�Ʒ��ʹ���Ű
			y++;
			if (y > length - 2) y = length - 2;
		}

		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {	//�����̽���
			if (!bullet) {	//�Ѿ��� ������
				bx = x;		//�Ѿ��� x��ǥ
				by = y - 1;	//�Ѿ��� y��ǥ
				bullet = true;
			}
		}

		if (bullet) {	//�Ѿ˽��
			GotoXY(bx, by);	//Ŀ���̵�
			printf("��");	//�Ѿ˽��
			by--;	//�Ѿ� �̵�
			if (by < 0) bullet = false;	//ȭ���� ������� �Ѿ������
		}

		for (int i = 0; i < MAX; i++) {
			if (stEnemy[i].bActive) {	//����
				GotoXY(stEnemy[i].x, stEnemy[i].y);
				printf("��");
				stEnemy[i].y++;
				if (stEnemy[i].y > length - 2) stEnemy[i].bActive = false;
			}
		}

		GotoXY(x, y);	//Ŀ���̵�
		printf("��");	//����� ���

		Sleep(50);	//��
	}

	system("pause");
	return 0;
}

