#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
텍스트 rpg game
1.캐릭터 만들기
2.몬스터 생성
3.아이템(무기,방어구,포션)
sleep함수보기
*/
typedef struct items {
	char item_name[30];//아이템이름
	int item_kind;//어아템종류
	int attack;//공격력
	int ac;//방어력
	int HP_, MP_;//포션
	int item_money;//판매시 가격
}items;
typedef struct character {
	int num;
	int exp;
	char name[20];//캐릭터이름
	int level;//레벨
	char job[10];//직업
	int str, dex, int_;//힘 민첩 지능
	int HP, MP;//체력 마나
	int Money;//골드
	char skill[10][50];//스킬
	struct items *item[100];//아이템,
}ct;

int Menu();
void User_Make(int a);//캐릭터생성
void User_Mng(int a);//캐릭터스테이터스
					 //void Item_Make();//아이템생성,텍스트에서 아이템 정보를 가져와서 저장후 사용
void Game_();//게임시작
void Save();//게임저장
void Load();//게임불러오기
void Id_Load(char *tmp_id, char *tmp_pw);
char* Login();//로그인,회원정보텍스트파일에 일치하는 정보없으면 바로 회원가입으로 진행
int Sub_Menu();//서브메뉴
int Town(int a);//마을
void Market();//상점
void Dungeon(int a);//던전

char ID[11];
ct *Name;//캐릭터 구조체 주소 저장
ct **list = NULL;//서로다른정보의 캐릭터를 만들기위해
int index = 0;

void main() {
	FILE *chf;
	int i;
	list = (ct**)malloc(sizeof(ct*));
	chf = fopen("c:/test/test/make_user.txt", "r");
	//메뉴실행
	while (1) {
		switch (Menu()) {
		case 1:
			system("cls");
			Load();
			while (1) {
				switch (Sub_Menu()) {
				case 1://마을
					system("cls");
					while (1) {
						switch (Town(0)) {
						case 1:
							//상점
							break;
						case 2:
							//이전으로
							break;
						}
						system("cls");
						break;
					}
					break;
				case 2://던전
					Dungeon(0);
					break;
				case 3://이전으로
					break;
				}
				system("cls");
				break;
			}
			break;
		case 2:
			//회원번호에 맞는 캐릭터정보의 마지막 데이터가져오기
			break;
		case 3:
			//텍스트에 캐릭터 정보 저장(누적으로 저장)
			break;
		case 4:
			//회원번호에 맞는 캐릭터정보데이터 텍스트파일에서 
			//누적된 데이터 모두가져와서 골라서 데이터가져오도록(이건 가능하면 마지막에 하자)
			break;
		case 5:
			return;
		}
		system("cls");
	}
}
int Menu() {
	int num;
	//과제 : 메뉴 꾸미기
	printf("1. New Game\n");
	printf("2. Game Continue\n");
	printf("3. Game Save\n");
	printf("4. Game Load\n");
	printf("5. Exit\n");
	printf("선택 : ");
	scanf("%d", &num);
	return num;
}
int Sub_Menu() {
	int num;
	printf("1. 마을\n");
	printf("2. 던전\n");
	printf("3. 이전으로\n");
	printf("선택 : ");
	scanf("%d", &num);
	return num;
}
char* Login() {
	char tmp_id[11], tmp_pw[15];
	printf("아이디 : ");
	gets_s(tmp_id);
	printf("비밀번호 : ");
	gets_s(tmp_pw);
	Id_Load(tmp_id, tmp_pw);
	//아이디,비밀번호 체크 후 로그인하기
	//로그인후 캐릭터불러오기(동적할당)
	//캐릭터 없으면 그냥 로그인하기
	return tmp_id;
}
void Id_Load(char *tmp_id, char *tmp_pw) {
	//아이디 비밀번호 체크
	//저장된 파일로부터 읽어서 확인하기
	//아이디가 없으면 만들기 회원가입하도록
	//회원가입할때 회원번호는 자동증가 아이디 비밀번호는 입력해서 텍스트에 저장
	char id[2][10];
	FILE *idf;
	idf = fopen("c:/test/test/id_data.txt", "r");
	fscanf(idf, "%s %s\n", id[0], id[1]);
	printf("아이디:%s  비밀번호:%s\n", id[0], id[1]);
	fclose(idf);
}
void User_Make(int b/*회원번호*/) {
	//자동증가된 회원번호를 가져와서 인덱스번호에 넣고 캐릭터 생성
	FILE *chf;
	int job_num = 0, a = 1;
	list[b] = (ct*)malloc(sizeof(ct));
	printf("=====캐릭터 생성하기=====\n");
	printf(" 캐릭터명 : ");
	scanf("%s", list[b]->name);
	printf("직업 - 1.전사 2.도적 3.궁수 4.마법사 :  ");
	scanf("%d", &job_num);
	list[b]->level = 1;
	list[b]->Money = 0;
	list[b]->num = b + 1;
	list[b]->exp = 0;
	while (a == 1) {
		if (job_num == 1) {
			strcpy(list[b]->job, "전사");
			list[b]->str = 12;
			list[b]->dex = 7;
			list[b]->int_ = 5;
			list[b]->HP = list[b]->level * 100;
			list[b]->MP = 50;
			strcpy(list[b]->skill[0], "스킬1");
			a = 0;
		}
		else if (job_num == 2) {
			strcpy(list[b]->job, "도적");
			list[b]->str = 6;
			list[b]->dex = 10;
			list[b]->int_ = 8;
			list[b]->HP = list[b]->level * 100;
			list[b]->MP = 50;
			strcpy(list[b]->skill[0], "스킬1");
			a = 0;
		}
		else if (job_num == 3) {
			strcpy(list[b]->job, "궁수");
			list[b]->str = 7;
			list[b]->dex = 10;
			list[b]->int_ = 7;
			list[b]->HP = list[b]->level * 100;
			list[b]->MP = 50;
			strcpy(list[b]->skill[0], "스킬1");
			a = 0;
		}
		else if (job_num == 4) {
			strcpy(list[b]->job, "마법사");
			list[b]->str = 5;
			list[b]->dex = 7;
			list[b]->int_ = 12;
			list[b]->HP = list[b]->level * 100;
			list[b]->MP = 50;
			strcpy(list[b]->skill[0], "스킬1");
			a = 0;
		}
		else {
			printf("잘못입력했습니다.\n");
			a = 1;
		}
	}
	chf = fopen("c:/test/test/make_user.txt", "w+");
	if (chf != NULL) {
		fprintf(chf, "%s %s %d %d %d %d %d %d %d %d %s %d\n", list[b]->job, list[b]->name, list[b]->level, list[b]->str, list[b]->dex, list[b]->int_, list[b]->HP, list[b]->MP, list[b]->Money, list[b]->exp, list[b]->skill[0], list[b]->num);
		fclose(chf);
	}
	return;
}
void User_Mng(int a/*회원번호*/) {
	//캐릭터 스테이터스창, 항시 화면표시
	//화면에 띄울때는 회원번호를 가져와서 인덱스에 넣어서 캐릭터 정보 표시
	printf("========캐릭터 스테이터스========\n");
	printf("캐릭터명 : %s\n", list[a]->name);
	printf("직업 : %s\n", list[a]->job);
	printf("골드 : %d\n", list[a]->Money);
	printf("레벨 : %d\n", list[a]->level);
	printf("경험치 : %d\n", list[a]->exp);
	printf("힘 : %d\n", list[a]->str);
	printf("민첩 : %d\n", list[a]->dex);
	printf("지력 : %d\n", list[a]->int_);
	printf("체력 : %d\n", list[a]->HP);
	printf("마나 : %d\n", list[a]->MP);
}
int Town(int a) {
	//체력원래대로만들기,상점이용메뉴
	FILE *chf;
	int num;
	chf = fopen("c:/test/test/make_user.txt", "w");
	list[a]->HP = list[a]->level * 100;
	list[a]->MP = 50;
	if (chf != NULL) {
		fprintf(chf, "%s %s %d %d %d %d %d %d %d %d %s %d\n", list[0]->job, list[0]->name, list[0]->level, list[0]->str, list[0]->dex, list[0]->int_, list[0]->HP, list[0]->MP, list[0]->Money, list[0]->exp, list[0]->skill[0], list[0]->num);
		fclose(chf);
	}
	User_Mng(a);
	printf("=================================\n");
	printf("캐릭터의 HP,MP가 원래대로 돌아왔습니다.\n\n");
	printf("1. 상점\n");
	printf("2. 이전으로\n");
	printf("선택 : ");
	scanf("%s", &num);
	return num;
}
void Market() {
	//아이템구매&판매기능구현
	//(ex.포션만 구매가능/switch문으로 1.포션구매 2.판매(이건캐릭터의아이템을출력해서선택후판매)
	//캐릭터의 돈 구현

}
void Dungeon(int a) {
	//던전입장(몬스터텍스트사용)
	//아주 간단하게 아래와 같은 구조
	FILE *chf;
	printf("몬스터퇴치!!\n");
	list[0]->HP = list[0]->HP - 20;
	printf("체력이 %d(으)로 줄었습니다.\n", list[0]->HP);
	system("pause");
	list[0]->Money = list[0]->Money + 100;
	printf("%d골드를 얻었습니다.\n", 100);
	system("pause");
	list[0]->exp = list[0]->exp + 10;
	printf("경험치 %d를 얻었습니다.\n", 10);
	system("pause");
	if (list[0]->exp >= 100) {
		list[0]->level++;
		list[0]->str++;
		list[0]->dex++;
		list[0]->int_++;
	}
	chf = fopen("c:/test/test/make_user.txt", "w");
	if (chf != NULL) {
		fprintf(chf, "%s %s %d %d %d %d %d %d %d %d %s %d\n", list[0]->job, list[0]->name, list[0]->level, list[0]->str, list[0]->dex, list[0]->int_, list[0]->HP, list[0]->MP, list[0]->Money, list[0]->exp, list[0]->skill[0], list[0]->num);
		fclose(chf);
	}
}
void Load() {
	FILE *f;
	f = fopen("c:/test/test/make_user.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
			list[index] = (ct*)malloc(sizeof(ct));
			fscanf(f, "%s %s %d %d %d %d %d %d %d %d %s %d\n", list[index]->job, list[index]->name, &list[index]->level, &list[index]->str, &list[index]->dex, &list[index]->int_, &list[index]->HP, &list[index]->MP, &list[index]->Money, &list[index]->exp, list[index]->skill[0], &list[index]->num);
			index++;
		}
		fclose(f);
		return;
	}
	else {
		User_Make(0);
	}
}