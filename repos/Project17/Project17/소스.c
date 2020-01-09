#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
�Է�/����Լ�(�Է� ���� ����)
�����Ҵ�
*/

typedef struct pen {
	float thick;//����
	char color[20];//����
	char company[20];//������
	struct pen* next;
}pen;
pen*head, *tail;

void init();
void input();
void output();
void main() {
	int num;
	init();
	while (1) {
		system("cls");
		printf("1.�Է� 2.��� 3.����\n");
		printf("[  ����  ]: ");

		scanf("%d", &num);
		switch (num) {
		case 1:
			input();
			break;
		case 2:
			output();
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}
void init() {
	head = (pen*)malloc(sizeof(pen));
	head->thick = 0.0;
	head->next = NULL;
	tail = head;
}
void input() {
	pen*new;
	new = head->next;
	printf("����: ");
	scanf("%f", &new->thick);
	printf("��ũ ����: ");
	scanf("%s", new->color);
	getchar();
	printf("������: ");
	scanf("%s", new->company);
	getchar();
	new = new->next;
	tail = new;
}
void output() {
	int i = 1;
	pen*scan;
	scan = head->next;
	while (scan != NULL) {
		printf("<<  %d��° ��  >>\n", i);
		printf("����: %f", scan->thick);
		printf("��ũ ����: %s", scan->color);
		printf("������: %s", scan->company);
		scan = scan->next;
		i++;
	}
}