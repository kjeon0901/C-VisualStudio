#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
<텍스트 rpg Game>
1.캐릭터 만들기
2.몬스터 생성
3.아이템 (무기, 방어구, 포션)
스토리는 알아서 조별로(나: 2조-전경희, 김정찬, 오주환, 윤성일)
*/
typedef struct items { //item[100]에 담아둘 것. 여기서 item[100]은 가방 역할
	char item_name[30]; //아이템이름
	int item_kind; //아이템종류
	int attack; //무기의 공격력
	int ac; //방어구의 방어력
	int HP_, MP_; //물약이 생명력, 마나 채워주는 양
}items;
typedef struct character {	//구조체만들기
	char name[20]; //캐릭터이름
	int level; //레벨
	char job[10]; //직업
	int str, dex, int_; //힘, 민첩, 지능
	int HP, MP; //생명력, 마나(에너지)
	char skill[10][50]; //스킬 10가지 50번?
	struct items * item[100]; //아이템
}ct;

void User_Make(); //캐릭터만들기
void Item_Make(); //아이템만들기
void Game_(); //게임시작
void Save(); //게임저장 
void Load(); //게임불러오기 
void Id_Load();
void Login(); //로그인
int Menu(); //메뉴

char ID[11];
ct *Name; //캐릭터 구조체(동적할당된 것) 주소 저장하는 포인터함수
		  //몬스터,아이템 리스트 담아줄 구조체 포인터배열 만들기(파일에서 하나하나 읽어올때마다 포인터배열 한줄씩 늘려서 들어가도록)

void main() {
	//몬스터, 아이템 각각 불러오기 함수(불러오는 건 메모장에 몬스터/아이템 이름, 공격력, 방어력 직접 써서 파일로 저장해둔 걸 불러오기)
	//로그인
	Login();
	printf("kiwi님 환영합니다! \n\n");
	//메뉴 실행
	while (1) {
		switch (Menu()) {
		case 1://새 게임
			   //캐릭터가 없다면 캐릭터 생성 함수로 캐릭터 만들기 ->바로 파일로 저장해야함
			   //캐릭터가 있으면 기존 캐릭터 지우고 새로 만들 것인지 묻기
			break;
		case 2:
			break;
		case 3:
			break;
		}
	}
}
int Menu() {
	int num;
	//과제->메뉴 이쁘게 꾸미기(이대로가 이쁘면 이대로)
	printf("1. New Game\n");
	printf("2. Continue Game\n");
	printf("3. Save Game\n");
	printf("4. Load Game\n");
	printf("5. Exit\n");
	printf("선택: ");
	scanf("%d", &num);
	return num;
}

void Login() {
	char tmp_id[11], tmp_pw[15];
	printf("아이디: ");
	gets(tmp_id);
	printf("비밀번호: ");
	gets(tmp_pw);

	Id_Load(tmp_id, tmp_pw);
	//아이디 비밀번호 체크된 후에 로그인되도록
	//로그인 후에 캐릭터 불러오기(구조체 모양에 맞게), 만약 캐릭터 없다면 그냥 로그인만 하기
	//캐릭터 구조체에 저장(동적할당)

}

void Id_Load(char*tmp_id, char*tmp_pw) {       //배열이니까 받기를 포인터로 받아야 함
											   //아이디-비밀번호 쌍으로 맞게 입력했는지 체크
											   //저장된 파일로부터 읽어서 확인하기
											   //아이디가 없으면 만들어주기
}