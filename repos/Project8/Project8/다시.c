#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct member {
	int num; //회원번호
	char ID[20];
	char PW[20];
	struct mem *next;
}mem;

mem*head=NULL, *tail=NULL;
mem*move = NULL; 
int count = 1;
char tmp_id[20], tmp_pw[20];

mem*choose(mem*pass);
mem* Login(mem*pass);
mem*Entry();
//mem* Login_Check(mem*tmp);

void main() {
	head = (mem*)malloc(count * sizeof(mem));
	head->num = 0;
	head->next = NULL;
	tail = head;
	mem*pass=head;
	if (choose(head, pass) == pass) {
		pass = choose(head, pass);
		printf("%s님 환영합니다!\n\n", pass->ID);
		//메뉴 실행
	}
	else {
		return;
	}
}
mem*choose(mem*pass) {
	int num;
	printf("1. 로그인 \n2. 회원가입\n");
	scanf("%d", &num);
	while (1) {
		if (num == 1) { //로그인
			if (Login(pass) == head) {
				return head;
			}
			else {
				pass = Login(pass);
				return pass;
			}
		}
		else if (num == 2) { //회원가입
			pass = Entry();
			return pass;
		}
		else {
			printf("잘못 입력했습니다.\n");
			system("pause");
			return head;
		}
		system("cls");
	}	
}
/*
mem* Login(mem*pass) {
	mem*tmp=NULL;//얘를 바꿔줘야할것같은데
	tmp = (mem*)malloc(sizeof(mem));

	printf("ID: ");
	scanf("%s", tmp->ID);
	printf("PW: ");
	scanf("%s", tmp->PW);
	if (Login_Check(tmp) == head) { //일치할 경우에만 pass로 받음
		printf("회원정보가 없습니다\n");
		system("pause");
		system("cls");
		return head;
	}
	else {
		pass = move;
		return pass;
	}
}
*/
mem*Entry() {
	FILE*entry = fopen("c:/textgame/entry.txt", "w");
	
	mem*new = (mem*)malloc(sizeof(mem));
	new->num = tail->num + 1;
	printf("ID: ");
	scanf("%s", new->ID);
	printf("PW: ");
	scanf("%s", new->PW);
	new->next = NULL;
	tail->next = new;
	tail = new;

	fprintf(entry, "%d %s %s\n\n", new->num, new->ID, new->PW);
	fclose(entry);

	return new;
}
/*
mem* Login_Check(mem*tmp) { //내가 입력한 ID, PW랑 일치하는 게 있는지 확인
	move = head; //앞에서부터 끝까지 훑어야 하므로 head로 초기화
	while (move->next != NULL) { //확신x
		if ((strcmp(move->ID, tmp->ID)==0)&&(strcmp(move->PW, tmp->PW) == 0)) { //확신x
			return move;
		}
		move = move->next;
	}
	printf("잘못 입력하였거나 회원 정보가 없습니다\n");
	return  head;
}
*/