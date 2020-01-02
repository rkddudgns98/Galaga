#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Console.h"

int main() {

	int width = 30, length = 30;

	int x = 14, y = 28;	//ó�� �������ǥ

	int bullet = 0, bx = 0, by = 0;	//�Ѿ��� ��ǥ

	int enemy_x = 0, enemy_y = 0;	//���� ��ǥ
	bool enemy = false;

	srand(time(NULL));
	
	SetConsoleSize(width, length);	//�ܼ�â ������ ����

	while (1) {

		Clear();	//�ܻ� �����

		if (!enemy) {
			enemy_x = (rand() % (width / 2)) * 2;
			enemy_y = 0;
			enemy = true;
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

		if (enemy) {	//����
			GotoXY(enemy_x, enemy_y);
			printf("��");
			enemy_y++;
			if (enemy_y > length - 2) enemy = false;
		}

		GotoXY(x, y);	//Ŀ���̵�
		printf("��");	//����� ���

		Sleep(50);	//��
	}

	system("pause");
	return 0;
}

