#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

typedef struct Schedule {
	int year;
	int month;
	int day;
	int pw;
	char title[30];
	char memo[100];
	struct Schedule *next;
}sc;

char tmp_id[20], tmp_pw[20];

int Main_Menu();
int Login();
int Id_Load(char* put_id, char* put_pw);
int Entry();
void main() {
	int num;
	num = Main_Menu();
	if (num == 0) {//���� �������� ���� 
		return;
	}
	printf("%s�� ȯ���մϴ�!\n\n", tmp_id);

}
int Main_Menu() {
	while (1) {
		int num;
		system("cls");
		printf("1.�α��� \n2.ȸ������ \n3.���� \n����: ");
		scanf("%d", &num);
		getchar();
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
			break;
		case 3:return 0;
		default:break;
		}
	}
}
int Login() {
	int re = 0;
	char put_id[20], put_pw[20];

	while (re == 0) {

		printf("\t<LOGIN> \n\n");
		printf("���̵� : ");
		gets(put_id);
		printf("��й�ȣ : ");
		gets(put_pw);

		re = Id_Load(put_id, put_pw);
		if (re == 1) {
			return 1;
		}
		else if (re == 2) {
			return 0;
		}
	}
}

int Id_Load(char* put_id, char* put_pw) {
	FILE *p;
	int num = 0;
	char id_check[10], pw_check[10], yn;

	p = fopen("c:/diary/member.txt", "r");

	while (!feof(p)) {
		fscanf(p, "%s %s\n", id_check, pw_check);
		if (!strcmp(put_id, id_check) && !strcmp(put_pw, pw_check)) {
			printf("�α���");
			Sleep(500);
			printf(".");
			Sleep(500);
			printf(".");
			Sleep(500);
			printf(".");
			Sleep(500);
			printf("����!\n");
			system("pause");
			strcpy(tmp_id, put_id);
			strcpy(tmp_pw, put_pw);
			fclose(p);//
			return 1;
		}
	}
	fclose(p);//
	printf("��ġ�����ʴ� id, pw �Դϴ�.\n");
	printf("���Է��Ͻðڽ��ϱ�?(y/n)\n");
	printf("�Է� :");
	while (1) {
		scanf("%c", &yn);
		getchar();//
		if (yn == 'Y' || yn == 'y') {
			return 0;
		}
		else if (yn == 'N' || yn == 'n') {
			return 2;
		}
	}
}

int Entry() {
	FILE *p;
	char put_id[20], put_pw[20];
	char id_find[20], pw_find[20];
	char yn;

	printf("\t<ȸ������>\n");
	printf("���̵� : ");
	gets(put_id);
	printf("��й�ȣ : ");
	gets(put_pw);
	printf("========================\n");
	printf("���̵� : %s\n", put_id);
	printf("��й�ȣ : %s\n", put_pw);
	printf("�Է��Ͻ� ���� �½��ϱ�?\n");
	printf("(y/n) : ");
	while (1) {
		scanf("%c", &yn);
		getchar();
		if (yn == 'N' || yn == 'n') {
			return 0;
		}
		else if (yn == 'Y' || yn == 'y') {
			p = fopen("c:/diary/member.txt", "r");
			if (p != NULL) {
				while (!feof(p)) {
					fscanf(p, "%s %s\n", id_find, pw_find);
					if (!strcmp(id_find, put_id)) {
						printf("������ ID�� �ֽ��ϴ�. \n");
						fclose(p);
						return 0;
					}
				}
				p = fopen("c:/diary/member.txt", "a");
			}
			else {
				p = fopen("c:/diary/member.txt", "w");
			}
			fprintf(p, "%s %s\n", put_id, put_pw);
			strcpy(tmp_id, put_id);
			strcpy(tmp_pw, put_pw);
			printf("ȸ�������� �Ϸ�Ǿ����ϴ�.\n");
			printf("���Ե� ���̵�� �α��� ���ּ���.");
			system("pause");
			fclose(p);
			return 1;
		}
	}
}