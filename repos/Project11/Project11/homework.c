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
	printf("1. 스택추가 2. 스택에 데이터 입력 3. 스택으로부터 데이터 출력 4. 나머지 데이터 그대로 두고 데이터 출력\n");
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
	printf("입력: ");
	scanf("%d", &input->num);
	tail = input;
}
void push() {
	st*move;
	move = (st*)malloc(sizeof(st));
	move = head->next;
	while (move->num != 0) {
		move = move->next;
	}//현대 move->num=0인 상태
	if (move->next = NULL) {
		printf("공간 가득 참!\n");
		return;
	}
	printf("입력: ");
	scanf("%d", &move->num);
}
void pop() {
	st*move;
	move = (st*)malloc(sizeof(st));
	move = tail;
	if (head->next->num == 0) {
		printf("스택이 비었음\n");
		return;
	}
	while (move->num!=0) {
			move->num = 0;
		move = move->pre;
	}
}
void pup_() {

}