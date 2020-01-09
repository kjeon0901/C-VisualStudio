#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
입력/출력함수(입력 제한 없음)
동적할당
*/

typedef struct pen {
	float thick;//굵기
	char color[20];//색상
	char company[20];//제조사
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
		printf("1.입력 2.출력 3.종료\n");
		printf("[  선택  ]: ");

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
	printf("굵기: ");
	scanf("%f", &new->thick);
	printf("잉크 색상: ");
	scanf("%s", new->color);
	getchar();
	printf("제조사: ");
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
		printf("<<  %d번째 펜  >>\n", i);
		printf("굵기: %f", scan->thick);
		printf("잉크 색상: %s", scan->color);
		printf("제조사: %s", scan->company);
		scan = scan->next;
		i++;
	}
}