#define _CRT_SECURE_NO_wARNINGS
#include <Stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

typedef struct stack {
	int index;
	int num;
	struct st*pre;
	struct st*next;
}st;

st*head = NULL;
st*tail = NULL;
void input();
void push();
void pop();
void pop_();
void main() {
	int i = 0;
	head = (st*)malloc(sizeof(st));
	head->next = NULL;
	head->pre = NULL;
	head->index = 0;
	tail = head;
	printf("1. �����߰� 2. ���ÿ� ������ �Է� 3. �������κ��� ������ ��� 4. ������ ������ �״�� �ΰ� ������ ���\n");
	scanf("%d", &i);
	switch (i) {
	case 1:input(); break;
	case 2:push(); break;
	case 3:pop(); break;
	case 4:pop_(); break;
	}
}
void input() {
	st*input;
	input = (st*)malloc(sizeof(st));
	tail->next = input;
	input->pre = tail;
	input->index = tail->index + 1;
	printf("�Է�: ");
	scanf("%d", &input->num);
	tail = input;
}
void push() {
	st*move;
	move = (st*)malloc(sizeof(st));
	move = head->next;
	while (move->num != 0) {
		move = move->next;
	}//���� move->num=0�� ����
	if (move->next = NULL) {
		printf("���� ���� ��!\n");
		return;
	}
	printf("�Է�: ");
	scanf("%d", &move->num);
}
void pop() {
	st*move;
	move = (st*)malloc(sizeof(st));
	move = tail;
	if (head->next->num == 0) {
		printf("������ �����\n");
		return;
	}
	while (move->num!=0) {
			move->num = 0;
		move = move->pre;
	}
}
void pup_() {

}