#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct member {
	int num; //ȸ����ȣ
	char ID[20];
	char PW[20];
	struct mem *next;
}mem;
mem*head = NULL, *tail = NULL;
mem*move = NULL;
int count = 1;
char tmp_id[20], tmp_pw[20];

mem*choose(mem*pass);
mem*Login(mem*pass);
mem*Entry();
void main() {
	head = (mem*)malloc(count * sizeof(mem));
	head->num = 0;
	head->next = NULL;
	tail = head;
	mem*pass = head;
	if (choose(pass) == pass) {
		pass = choose(pass);
		printf("%s�� ȯ���մϴ�!\n\n", pass->ID);
	}
	else {
		return;
	}
}
mem*choose(mem*pass) {
	int num;
	printf("1. �α��� \n2. ȸ������\n");
	scanf("%d", &num);
	while (1) {
		if (num == 1) {
			if (Login(pass) == head) return head;
			else {
				pass = Login(pass); return pass;
			}
		}
		else if (num == 2) {
			pass = Entry();
			return pass;
		}
		else {
			printf("�߸� �Է�\n");
			system("pause");
			return head;
		}
		system("cls");
	}
}
mem*Entry() {
	FILE*f = fopen("c:/textgame/entry.txt", "w"); //w�´��� ��

	mem*new = (mem*)malloc(sizeof(mem));
	new->num = tail->num + 1;
	printf("ID: ");
	scanf("%s", new->ID);
	printf("PW: ");
	scanf("%s", new->PW);
	new->next = NULL;
	tail->next = new;
	tail = new;

	fprintf(f, "%d %s %s \n\n", new->num, new->ID, new->PW);
	fclose(f);

	return new;
}