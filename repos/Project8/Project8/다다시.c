#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/*
문제점1. 파일에 새로운 아이디가 입력될 때마다 
					num값이 계속 증가해야 하는데, 계속 1임.
문제점2. 어쨌든 회원가입해서 파일에 정보를 저장시킨 뒤에 그 아이디로 로그인을 하면 
					"환영합니다"가 떠야 하는데 계속 "회원정보가 없거나 잘못 입력"이라고 뜸
문제점3. choose함수의 while문이 2번까지만 실행됨
*/

typedef struct member {
	int num; //회원번호
	char ID[20];
	char PW[20];
	struct mem *next;
}mem;
mem*head = NULL, *tail = NULL;
char tmp_id[20], tmp_pw[20];

mem*choose(mem*pass);
mem*Login(mem*pass);
mem*Entry();
mem*Login_Check(mem*tmp);
void main() {

	mem*pass = NULL;
		pass = choose(pass); //로그인 회원가입 선택함수, 확인된 아이디 구조체 돌려줌
		printf("%s님 환영합니다!\n\n", pass->ID);

}
mem*choose(mem*pass) {
	head = (mem*)malloc(sizeof(mem));//전역변수head에 공간할당 후 초기화
	head->num = 0;
	head->next = NULL;
	tail = head;
	int num;

	while (1) {
	printf("1. 로그인 \n2. 회원가입\n");
	scanf("%d", &num);
		if (num == 1) {
			if (Login(pass)->ID == pass->ID) {
				pass = Login(pass); return pass;
			}
		}
		else if (num == 2) {
				pass = Entry();

				return pass;
		}
		else {
				printf("잘못 입력\n");
				system("pause");	
		}
		system("cls");
	}
}
mem*Login(mem*pass) {
	mem*tmp = NULL;
	tmp = (mem*)malloc(sizeof(mem));

	printf("ID: ");
	scanf("%s", tmp->ID);
	printf("PW: ");
	scanf("%s", tmp->PW);

	tmp = Login_Check(tmp);
	return tmp;
}
mem*Entry() { 
FILE*f = fopen("c:/textgame/entry.txt", "a+b"); 

	mem*new = (mem*)malloc(sizeof(mem));
	new->num = tail->num+1;
	printf("ID: ");
	scanf("%s", new->ID);
	printf("PW: ");
	scanf("%s", new->PW);
	new->next = NULL;	
	fprintf(f, "%d %s %s \r\n", new->num, new->ID, new->PW);
	fclose(f);

	if (head == NULL) {
		head = new;
		tail = head;
		return tail;
	}
	else { 
		tail->next = new;
		tail = new;
		return tail;
	}
	free(new);//return 뒤에 써도 되나?
}
mem*Login_Check(mem*tmp) {
	mem*move = head;;
	while(move!=tail->next){
		if (strcmp(move->ID, tmp->ID) == 0 && strcmp(move->PW, tmp->PW) == 0) {
			return move;
		}
		move = move->next;
	} 
	printf("회원정보가 없거나 잘못 입력\n");
	system("pause");
	system("cls");
}