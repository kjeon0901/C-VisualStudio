#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <math.h>

/*
오류 생긴 곳 표시해뒀어요 한번 봐주세요ㅠㅠ
*/

typedef struct member {
	char ID[20];
	char PW[20];
	//비밀메모 비밀번호 추가
	struct mem*next;
}mem;
mem*head = NULL, *tail = NULL, *pass = NULL;

void Init();
int Main_Menu();//로그인, 회원가입, 종료 선택
int Login();//ID, PW 입력
int Login_Check(char*tmp_id, char*tmp_pw);//파일 읽어서 입력한 ID, PW와 일치하면 pass에 담기
int Entry();//회원가입, 같은 아이디 있으면 뒤로가기

void Init() {
	head = (mem*)malloc(sizeof(mem));
	head->next = NULL;
	tail = head;
}
void main() {
	Init();
	int num;
	num = Main_Menu();
	if (num == 0) {//종료 선택했을 때만
		return;
	}
	printf("%s님 환영합니다!\n\n", pass->ID);

}
int Main_Menu() {
	while (1) {
		int num;
		printf("1.로그인 \n2.회원가입 \n3.종료 \n선택: ");
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
		printf("등록된 회원정보가 없습니다\n회원가입하세요\n");
		system("pause");
		return 0;
	}
	while (!feof(fc)) {//while문에서 오류가 생겼어요
		fscanf(fc, "%s %s\n", move->ID, move->PW);
		if (!strcmp(move->ID, tmp_id) && !strcmp(move->PW, tmp_pw)) {
			strcpy(pass->ID, move->ID);
			strcpy(pass->PW, move->PW);
			return 1;
		}
		move = move->next;
	}
	printf("ID 또는 PW가 존재하지 않습니다\n");
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
		while (!feof(fc)) {//Entry도 여기부터 오류예요 Login이랑 같은 오류인 거 같아요..
			fscanf(fc, "%s %s\n", move->ID, move->PW);
			move = move->next;
		}
		while (!feof(fc)) {
			if (!strcmp(move->ID, new->ID)) {
				printf("동일한 ID가 있습니다. \n");
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