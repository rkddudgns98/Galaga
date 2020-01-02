#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Console.h"

#define MAX 10

int main() {

	int width = 30, length = 30;	//�ܼ� ������

	int x = width - 2, y = length - 2;	//ó�� �������ǥ

	int bullet = 0, bx = 0, by = 0;	//�Ѿ��� ��ǥ

	int enemy_x[MAX] = { 0 };
	int enemy_y[MAX] = { 0 };	//���� ��ǥ
	bool enemy[MAX] = { false };

	srand(time(NULL));
	
	SetConsoleSize(width, length);	//�ܼ�â ������ ����

	while (1) {
		Clear();	//�ܻ� �����

		for (int i = 0; i < MAX; i++) {
			if (!enemy[i]) {
				enemy_x[i] = (rand() % (width / 2)) * 2;
				enemy_y[i] = 0;
				enemy[i] = true;
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
			if (enemy[i]) {	//����
				GotoXY(enemy_x[i], enemy_y[i]);
				printf("��");
				enemy_y[i]++;
				if (enemy_y[i] > length - 2) enemy[i] = false;
			}
		}

		GotoXY(x, y);	//Ŀ���̵�
		printf("��");	//����� ���

		Sleep(50);	//��
	}

	system("pause");
	return 0;
}

