#include "index.h"
#include "Book_Mng.h"
#include "Book_Struct.h"
#include "Book_Rent.h"
#include "Menu.h"
/*
�޴�			����޴�
1. ���� �뿩    1. -> 1) ��ü ���
2) �뿩 ���� ����
2. ���� �ݳ�
3. ���� ����     3. -> 1) ���� ���
4. ����				   2) ���� ����
3) ���� ���
-> ���� ����ü�� �޴��� �°� �����
-> ó�� ���� �Ҷ� ������� �ҷ�����
-> �����  �����ϰ� ���� �ǰ� �����
*/

void main() {
	Init();
	while (1) {
		switch (Main_Menu()) {
		case 1:
			Sub_Menu(1); break;
		case 2:
			Return_Book(); break;
		case 3:
			Sub_Menu(3); break;
		case 4:
			Save_Book();
			return;
		}
		system("cls");
	}
}