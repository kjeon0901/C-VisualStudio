#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
<�ؽ�Ʈ rpg Game>
1.ĳ���� �����
2.���� ����
3.������ (����, ��, ����)
���丮�� �˾Ƽ� ������(��: 2��-������, ������, ����ȯ, ������)
*/
typedef struct items { //item[100]�� ��Ƶ� ��. ���⼭ item[100]�� ���� ����
	char item_name[30]; //�������̸�
	int item_kind; //����������
	int attack; //������ ���ݷ�
	int ac; //���� ����
	int HP_, MP_; //������ �����, ���� ä���ִ� ��
}items;
typedef struct character {	//����ü�����
	char name[20]; //ĳ�����̸�
	int level; //����
	char job[10]; //����
	int str, dex, int_; //��, ��ø, ����
	int HP, MP; //�����, ����(������)
	char skill[10][50]; //��ų 10���� 50��?
	struct items * item[100]; //������
}ct;

void User_Make(); //ĳ���͸����
void Item_Make(); //�����۸����
void Game_(); //���ӽ���
void Save(); //�������� 
void Load(); //���Ӻҷ����� 
void Id_Load();
void Login(); //�α���
int Menu(); //�޴�

char ID[11];
ct *Name; //ĳ���� ����ü(�����Ҵ�� ��) �ּ� �����ϴ� �������Լ�
		  //����,������ ����Ʈ ����� ����ü �����͹迭 �����(���Ͽ��� �ϳ��ϳ� �о�ö����� �����͹迭 ���پ� �÷��� ������)

void main() {
	//����, ������ ���� �ҷ����� �Լ�(�ҷ����� �� �޸��忡 ����/������ �̸�, ���ݷ�, ���� ���� �Ἥ ���Ϸ� �����ص� �� �ҷ�����)
	//�α���
	Login();
	printf("kiwi�� ȯ���մϴ�! \n\n");
	//�޴� ����
	while (1) {
		switch (Menu()) {
		case 1://�� ����
			   //ĳ���Ͱ� ���ٸ� ĳ���� ���� �Լ��� ĳ���� ����� ->�ٷ� ���Ϸ� �����ؾ���
			   //ĳ���Ͱ� ������ ���� ĳ���� ����� ���� ���� ������ ����
			break;
		case 2:
			break;
		case 3:
			break;
		}
	}
}
int Menu() {
	int num;
	//����->�޴� �̻ڰ� �ٹ̱�(�̴�ΰ� �̻ڸ� �̴��)
	printf("1. New Game\n");
	printf("2. Continue Game\n");
	printf("3. Save Game\n");
	printf("4. Load Game\n");
	printf("5. Exit\n");
	printf("����: ");
	scanf("%d", &num);
	return num;
}

void Login() {
	char tmp_id[11], tmp_pw[15];
	printf("���̵�: ");
	gets(tmp_id);
	printf("��й�ȣ: ");
	gets(tmp_pw);

	Id_Load(tmp_id, tmp_pw);
	//���̵� ��й�ȣ üũ�� �Ŀ� �α��εǵ���
	//�α��� �Ŀ� ĳ���� �ҷ�����(����ü ��翡 �°�), ���� ĳ���� ���ٸ� �׳� �α��θ� �ϱ�
	//ĳ���� ����ü�� ����(�����Ҵ�)

}

void Id_Load(char*tmp_id, char*tmp_pw) {       //�迭�̴ϱ� �ޱ⸦ �����ͷ� �޾ƾ� ��
											   //���̵�-��й�ȣ ������ �°� �Է��ߴ��� üũ
											   //����� ���Ϸκ��� �о Ȯ���ϱ�
											   //���̵� ������ ������ֱ�
}