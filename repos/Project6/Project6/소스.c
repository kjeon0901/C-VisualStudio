#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct member {
	char name[10];
	char ID[11];
	char PW[21];
}mem;

int count = 1;
char choose(mem*list);
char Login(mem*list);
char* Entry(mem*list);
int Login_Check(char * a, char* b, mem**list_a, mem**list_b);
//int Menu();
char tmp_id[11], tmp_pw[15];


void main() {
	mem*list;
	list = (mem*)malloc(count * sizeof(mem));

	//몬스터, 아이템 각각 불러오기 함수(불러오는 건 메모장에 몬스터/아이템 이름, 공격력, 방어력 직접 써서 파일로 저장해둔 걸 불러오기)
	//로그인
	tmp_id[11] = choose(list);
	printf("%s님 환영합니다! \n\n", tmp_id[11]);
	//메뉴 실행
}

char choose(mem*list) {
	int num;

	printf("1. 로그인 \n2. 회원가입");
	scanf("%d", &num);
	while (1) {
		if (num == 1) {
			tmp_id[11] = Login(list);
			return tmp_id[11];
		}
		else if (num == 2) {
			strcpy(tmp_id, Entry(list));// 문자열을 문자열에 대입하는데, 앞에서부터 차례대로
			return tmp_id[11];
		}
		else {
			printf("잘못 입력했습니다.");
			system("pause");
		}
		system("cls");
	}
}
char Login(mem*list) {

	char myID[] = "kiwi";
	char myPW[] = "kiwi1234!";

	printf("아이디: ");
	gets(list->ID);
	printf("비밀번호: ");
	gets(list->PW);

	switch (Login_Check(myID, myPW, *list->ID, *list->PW)) {
	case 1:
		return tmp_id[11];
	case 2:
		printf("ID 또는 PW를 잘못 입력하였거나 회원 등록이 되지 않았습니다. \n");
		choose(list); //맞게 한건가?
	}
}
char* Entry(mem*list) { //char맞게 한건가? //틀렸음. char*여야 함. 


	FILE *entry;

	printf("이름: ");
	gets(list->name);
	printf("\n아이디: ");
	gets(list->ID);
	printf("\n비밀번호: ");
	gets(list->PW);

	entry = fopen("c:/testgame/entry.txt", "w");
	fprintf(entry, "%s %s %s\n", list->name, list->ID, list->PW);
	fclose(entry);

	return list->ID;
}
int Login_Check(char * a, char* b, mem**list_a, mem**list_b) { //
	if ((a == (*list_a)->ID) && (b == (*list_b)->PW)) //배열에 저장된 문자열끼리 비교해야 하는데 배열주소(char a)랑 mem**list_a(*list_a)를 비교했음. 
		return 1;
	return 2;
}