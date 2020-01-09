#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <math.h>

/*
���� ���� �� ǥ���ص׾�� �ѹ� ���ּ���Ф�
*/

typedef struct member {
	char ID[20];
	char PW[20];
	//��и޸� ��й�ȣ �߰�
	struct mem*next;
}mem;
mem*head = NULL, *tail = NULL, *pass = NULL;

void Init();
int Main_Menu();//�α���, ȸ������, ���� ����
int Login();//ID, PW �Է�
int Login_Check(char*tmp_id, char*tmp_pw);//���� �о �Է��� ID, PW�� ��ġ�ϸ� pass�� ���
int Entry();//ȸ������, ���� ���̵� ������ �ڷΰ���

void Init() {
	head = (mem*)malloc(sizeof(mem));
	head->next = NULL;
	tail = head;
}
void main() {
	Init();
	int num;
	num = Main_Menu();
	if (num == 0) {//���� �������� ����
		return;
	}
	printf("%s�� ȯ���մϴ�!\n\n", pass->ID);

}
int Main_Menu() {
	while (1) {
		int num;
		printf("1.�α��� \n2.ȸ������ \n3.���� \n����: ");
		scanf("%d", &num);
		switch (num) {
		case 1:
			if (Login()) {
				return 1;
			}
			break;
		case 2:
			if (Entry()) {
				return 1;
			}
		case 3:return 0;
		default:break;
		}
		system("cls");
	}
}
int Login() {
	char tmp_id[20], tmp_pw[20];
	getchar();
	printf("ID: ");
	scanf("%s", tmp_id);
	getchar();
	printf("PW: ");
	scanf("%s", tmp_pw);
	return Login_Check(tmp_id, tmp_pw);
}
int Login_Check(char*tmp_id, char*tmp_pw) {
	mem*move = head->next;
	FILE*fc;
	fc = fopen("c:/test/diary/mem.txt", "r");
	if (fc == NULL) {
		printf("��ϵ� ȸ�������� �����ϴ�\nȸ�������ϼ���\n");
		system("pause");
		return 0;
	}
	while (!feof(fc)) {//while������ ������ ������
		fscanf(fc, "%s %s\n", move->ID, move->PW);
		if (!strcmp(move->ID, tmp_id) && !strcmp(move->PW, tmp_pw)) {
			strcpy(pass->ID, move->ID);
			strcpy(pass->PW, move->PW);
			return 1;
		}
		move = move->next;
	}
	printf("ID �Ǵ� PW�� �������� �ʽ��ϴ�\n");
	system("pause");
	return 0;
	fclose(fc);
}
int Entry() {
	mem*new = head;
	mem*move = head->next;
	mem*check_id = head->next;
	FILE *fc;
	fc = fopen("c:/test/diary/mem.txt", "r");
	printf("ID: ");
	scanf("%s", new->ID);
	printf("PW: ");
	scanf("%s", new->PW);
	if (fc != NULL) {
		while (!feof(fc)) {//Entry�� ������� �������� Login�̶� ���� ������ �� ���ƿ�..
			fscanf(fc, "%s %s\n", move->ID, move->PW);
			move = move->next;
		}
		while (!feof(fc)) {
			if (!strcmp(move->ID, new->ID)) {
				printf("������ ID�� �ֽ��ϴ�. \n");
				fclose(fc);
				return 0;
			}
		}
		fc = fopen("c:/test/diary/mem.txt", "a");
	}
	else
		fc = fopen("c:/test/diary/mem.txt", "w");

	tail->next = new;
	fprintf(fc, "%s %s\n", new->ID, new->PW);
	tail = new;

	fclose(fc);
	strcpy(pass->ID, new->ID);
	strcpy(pass->PW, new->PW);
	return 1;
}