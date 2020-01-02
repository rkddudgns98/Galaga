#include <stdio.h>
#include <stdlib.h>

#include "Console.h"

int main() {

	int x = 14, y = 28;	//ó�� �������ǥ
	int bullet = 0, bx = 0, by = 0;	//�Ѿ��� ��ǥ
	
	SetConsoleSize(30, 30);	//�ܼ�â ������ ����

	while (1) {

		Clear();	//�ܻ� �����

		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {	//���ʹ���Ű
			x--;
			if (x < 0) x = 0;
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {	//�����ʹ���Ű
			x++;
			if (x > 28) x = 28;
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000) {	//���ʹ���Ű
			y--;
			if (y < 0) y = 0;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {	//�Ʒ��ʹ���Ű
			y++;
			if (y > 28) y = 28;
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

		GotoXY(x, y);	//Ŀ���̵�
		printf("��");	//����� ���

		Sleep(50);	//��
	}

	system("pause");
	return 0;
}

