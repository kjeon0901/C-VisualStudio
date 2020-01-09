#define _CRT_SECURE_NO_WARNINGS//scanf오류처리
#include<stdio.h>//입출력 관련 전처리
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<string.h>//문자열관련 함수가 들어있음
/*
텍스트 rpg game
1.캐릭터 만들기
2.몬스터 생성
3.아이템(무기,방어구,포션)
sleep함수보기
*/
typedef struct member { //회원정보 구조체 형식
	int num;//회원번호
	char ID[20];
	char PW[20];
}mem;
typedef struct items {
	int item_num;//아이템번호
	char item_name[30];//아이템이름
	int item_kind;//어아템종류
	int attack;//공격력
	int def;//방어력
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
	int def;// 방어력
	int Money;//골드
	int count;
	char skill[10][50];//스킬
	struct items *item[100];//아이템,
}ct;
typedef struct monster {
	char mon_name[20];
	int mon_level;
	int mon_attack;
	int mon_HP;
	int mon_money;
	int mon_exp;
	struct items *mon_item[5];
}mon;

int Menu();//게임메뉴
void Menu_1();//게임메뉴
void Menu_2();//게임메뉴
void Menu_3();//게임메뉴
int Sub_Menu();//서브메뉴
void User_Make();//캐릭터생성
void User_Mng();//캐릭터스테이터출력
void Save();//게임저장
void New_Game();//새로운게임
void Game_Load();//텍스트파일에 저장된 내용 불러오기
void Load();//로그인정보불러오기
int Town();//마을
int Market();//상점
void Recovery();//회복
void Development();//성장
void Sale();
void Dungeon();//던전
void choose();//로그인회원가입메뉴선택
int Login();//로그인아이디,비밀번호입력화면
int File_Load(char *tmp_id, char *tmp_pw);//회원정보텍스트파일에 일치확인
void Entry();//회원가입


ct *list = NULL;//캐릭터정보
mem*list_id = NULL;//회원정보
mon *list_mon = NULL;//몬스터정보
items **list_item[5];//아이템정보
int index = 0, check = 0;//while문등의 반복문을 빠져나올때 사용
int item_index = 0;

void main() {
	FILE *chf, *Item;
	int i;
	chf = fopen("c:/test/test/make_user.txt", "r");
	Item = fopen("c:/test/test/item.txt", "r");
	list = (ct*)malloc(sizeof(ct));//캐릭터정보 동적할당 공간생성
	list_id = (mem*)malloc(sizeof(mem));//회원정보 동적할당 공간생성
	list_mon = (mon*)malloc(sizeof(mon));//몬스터정보 동적할당 공간생성
	for (i = 0; i < 2; i++) {
		list->item[i] = (items*)malloc(sizeof(items));//캐릭터가 가질 아이템정보 동적할당 공간생성
		fscanf(Item, "%d %s %d %d %d %d\n", &list->item[i]->item_num, list->item[i]->item_name, &list->item[i]->attack, &list->item[i]->def, &list->item[i]->item_money, &list->item[i]->item_kind);
	}
	fclose(Item);

	choose();
	Sleep(1000);
	if (index != -1) {
		printf("%s님 환영합니다!\n\n", list_id->ID);
		Sleep(1000);
		system("cls");
		Load();
		system("cls");
		Menu_1();
	}
	else
		return;
	return;
}
void choose() {// index번호 넘겨줌
	int num;
	while (1) {
		printf("1. 로그인 \n2. 회원가입\n");
		printf("선택 : ");
		scanf("%d", &num);
		switch (num) {
		case 1:
			if (Login()) {
				return;
			}
			break;
		case 2:
			Entry();
			return;
		default:
			getchar();
			getchar();
			system("cls");
			choose();
			return;
		}
		system("cls");
	}
}
int Login() {
	char tmp_id[15], tmp_pw[15];
	getchar();
	printf("아이디 : ");
	scanf("%s", tmp_id);
	getchar();
	printf("비밀번호 : ");
	scanf("%s", tmp_pw);
	return File_Load(tmp_id, tmp_pw);
}
int File_Load(char *tmp_id, char *tmp_pw) {//입력한 tmp과 같은 정보가 파일에 있는지 확인
	FILE *f; //파일 읽기전용으로 열기
	int member_num = 1;
	char check_id[15] = { "" }, check_pw[15] = { "" };
	list_id = (mem*)malloc(sizeof(mem));
	f = fopen("c:/test/test/entry.txt", "r");
	if (f != NULL) {//파일이 비어있지 않다면, 불러와서 동적할당된 배열에 저장해야 함
		while (!feof(f)) { //파일 끝날때까지
			fscanf(f, "%d %s %s\n", &member_num, check_id, check_pw);
			if (!strcmp(check_id, tmp_id) && !strcmp(check_pw, tmp_pw)) {
				list_id->num = member_num;
				strcpy(list_id->ID, tmp_id);
				strcpy(list_id->PW, tmp_pw);
				return 1;
			}
			member_num++;
		}
		printf("회원 정보가 없습니다.\n");
		system("pause");
		return 0;
	}
	else {//파일이 비어있다면, 회원가입하라고 하기
		printf("등록된 회원이 없습니다.\n");
		printf("회원가입하세요.\n");
		system("pause");
		return 0;
	}
}
void Entry() {
	FILE *f;
	int index = 0;
	f = fopen("c:/test/test/entry.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
			fscanf(f, "%d %s %s\n", &list_id->num, list_id->ID, list_id->PW);
			index++;
		}
	}
	else {
		index = 0;
	}
	getchar();
	f = fopen("c:/test/test/entry.txt", "a");
	list_id->num = index + 1;
	printf("ID: ");
	scanf("%s", list_id->ID);
	printf("PW: ");
	scanf("%s", list_id->PW);
	fprintf(f, "%d %s %s\n", list_id->num, list_id->ID, list_id->PW);
	fclose(f);
	system("pause");
	return;
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
void Menu_1() {
	while (1) {
		switch (Menu()) {
		case 1:
			New_Game();
			User_Make();
			system("cls");
			Menu_2();
			break;
		case 2:
			//회원번호에 맞는 캐릭터정보 가져오기
			//Continue();
			Menu_2();
			break;
		case 3:
			//텍스트에 캐릭터 정보 저장
			Save();
			break;
		case 4:
			//회원번호에 맞는 캐릭터정보데이터 텍스트파일에서
			Game_Load();
			Menu_2();
			break;
		case 5:
			return;
		default:
			break;
		}
		system("cls");
	}
}
void Menu_2() {
	system("cls");
	while (1) {
		switch (Sub_Menu()) {
		case 1://마을
			system("cls");
			while (1) {
				switch (Town()) {
				case 1:
					//상점
					system("cls");
					Menu_3();
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
			system("cls");
			if (list->HP > 0) {
				Dungeon();
			}
			else {
				list->HP = 0;
				Menu_2();
				return;
			}
			break;
		case 3://이전으로
			return;
		}
		system("cls");
	}
}
void Menu_3() {
	while (1) {
		switch (Market()) {
		case 1:
			Recovery();//회복하기
			break;
		case 2:
			Development();//성장하기
			break;
		case 3://판매
			Sale();
			break;
		case 4:
			return;
		}
		break;
	}
}
int Sub_Menu() {
	int num;
	User_Mng();
	printf("=================================\n");
	printf("\n");
	printf("1. 마을\n");
	printf("2. 던전\n");
	printf("3. 이전으로\n");
	printf("선택 : ");
	scanf("%d", &num);
	return num;
}
void New_Game() {
	char yn;
	FILE *chf;
	chf = fopen("c:/test/test/make_user.txt", "w");
	printf("이전의 정보는 전부 지워집니다....y/n\n");
	getchar();
	printf("입력 : ");
	scanf("%c", &yn);
	if (yn == 'y') {
		while (!feof(chf)) {
			fscanf(chf, "%d %s %s %d %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp, &list->count);
			if (list_id->num == list->num) {
				list->num = 0;
				fprintf(chf, "%d %s %s %d %d %d %d %d %d %d %d %d\n", list->num, list->job, list->name, list->level, list->str, list->dex, list->int_, list->HP, list->MP, list->Money, list->exp, list->count);
				break;
			}
		}
		fclose(chf);
		return;
	}
	else if (yn == 'n') {
		Menu_1();
		return;
	}
	else {
		Menu_1();
		return;
	}
}
void Game_Load() {
	FILE *chf;
	chf = fopen("c:/test/test/make_user.txt", "r");
	if (chf != NULL) {
		while (!feof(chf)) {
			fscanf(chf, "%d %s %s %d %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp, &list->count);
			if (list_id->num == list->num) {
				break;
			}
		}
		fclose(chf);
	}
	printf("캐릭터 정보를 가져왔습니다.\n");
	system("pause");
	return;
}
void User_Make() {
	//자동증가된 회원번호를 가져와서 인덱스번호에 넣고 캐릭터 생성
	FILE *chf;
	int job_num = 0, a = 1;
	chf = fopen("c:/test/test/make_user.txt", "a");
	printf("=====캐릭터 생성하기=====\n");
	printf(" 캐릭터명 : ");
	scanf("%s", list->name);
	printf("직업 - 1.전사 2.도적 3.궁수 4.마법사 : ");
	scanf("%d", &job_num);
	list->level = 1;
	list->Money = 0;
	list->num = list_id->num;
	list->exp = 0;
	list->str = 10;
	list->dex = 10;
	list->int_ = 10;
	list->HP = list->level * 100;
	list->MP = 50;
	list->count = 0;
	while (a) {
		switch (job_num) {
		case 1:
			strcpy(list->job, "전사");
			a = 0;
			break;
		case 2:
			strcpy(list->job, "도적");
			a = 0;
			break;
		case 3:
			strcpy(list->job, "궁수");
			a = 0;
			break;
		case 4:
			strcpy(list->job, "마법사");
			a = 0;
			break;
		default:
			printf("잘못입력했습니다.\n");
			printf("처음부터 다시 진행해주세요...\n");
			system("pause");
			getchar();
			getchar();
			system("cls");
			main();
			return;
		}
	}
	system("cls");
	printf("캐릭터 생성중.....\n");
	Sleep(1000);
	if (chf != NULL) {
		fprintf(chf, "%d %s %s %d %d %d %d %d %d %d %d %d\n", list->num, list->job, list->name, list->level, list->str, list->dex, list->int_, list->HP, list->MP, list->Money, list->exp, list->count);
		fclose(chf);
	}
	return;
}
void User_Mng() {
	//캐릭터 스테이터스창, 항시 화면표시
	//화면에 띄울때는 회원번호를 가져와서 인덱스에 넣어서 캐릭터 정보 표시
	printf("========캐릭터 스테이터스========\n");
	printf("캐릭터명 : %s\n", list->name);
	printf("직업 : %s\n", list->job);
	printf("골드 : %d\n", list->Money);
	printf("레벨 : %d\n", list->level);
	printf("경험치 : %d\n", list->exp);
	printf("힘 : %d\n", list->str);
	printf("민첩 : %d\n", list->dex);
	printf("지력 : %d\n", list->int_);
	printf("체력 : %d\n", list->HP);
	printf("마나 : %d\n", list->MP);
}
int Town() {
	//상점이용메뉴
	int num;
	User_Mng();
	printf("=================================\n");
	printf("\n");
	printf("1. 상점\n");
	printf("2. 이전으로\n");
	printf("선택 : ");
	scanf("%d", &num);
	return num;
}
int Market() {
	//아이템구매&판매기능구현
	//(ex.포션만 구매가능/switch문으로 1.포션구매 2.판매(이건캐릭터의아이템을출력해서선택후판매)
	//캐릭터의 돈 구현
	int num;
	User_Mng();
	printf("=================================\n");
	printf("\n");
	printf("==========상점==========\n\n");
	printf("1. 회복하기(-100골드)\n");
	printf("2. 성장하기(-300골드)\n");
	printf("3. 아이템판매\n");
	printf("4. 이전으로\n");
	printf("선택 : ");
	scanf("%d", &num);
	return num;
}
void Recovery() {
	FILE *chf;
	chf = fopen("c:/test/test/make_user.txt", "w");
	if (chf != NULL) {
		while (!feof(chf)) {
			fscanf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp);
			if (list_id->num == list->num) {
				if (list->Money < 100) {
					printf("소지골드가 부족합니다.\n");
					system("pause");
					Menu_3();
					return;
				}
				list->HP = list->level * 100 + list->item[1]->def;
				list->MP = 50;
				list->Money -= 100;
				break;
			}
		}
		fclose(chf);
	}
	Sleep(1000);
	printf("캐릭터가 모두 회복되었습니다.\n");
	system("pause");
	Menu_3();
}
void Development() {
	FILE *chf;
	chf = fopen("c:/test/test/make_user.txt", "w");
	if (chf != NULL) {
		while (!feof(chf)) {
			fscanf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp);
			if (list_id->num == list->num) {
				if (list->Money < 300) {
					printf("소지골드가 부족합니다.\n");
					system("pause");
					Menu_3();
					return;
				}
				list->str += 2;
				list->dex += 2;
				list->int_ += 2;
				list->Money -= 300;
				break;
			}
		}
		fclose(chf);
	}
	Sleep(1000);
	printf("캐릭터가 소량 성장되었습니다.\n");
	system("pause");
	Menu_3();
}
void Sale() {
	FILE *File;
	int i = 0, num = 0;
	File = fopen("c:/test/test/item.txt", "r");
	printf("[현재 소지한 아이템]\n");
	for (i = 0; i < 2; i++) {
		printf("%d. %s %d\n", list->item[i]->item_num, list->item[i]->item_name, list->item[i]->item_money);
	}
	printf("3. 이전으로\n");
	printf("선택: ");
	scanf("%d", &num);
	if (num == 3) {
		system("cls");
		Menu_3();
		return;
	}
	num -= 1;
	list->Money += list->item[num]->item_money;
	list->item[num]->item_money = 0;
	list->str -= list->item[num]->attack;
	list->def -= list->item[num]->def;
	printf("현재 골드 : %d원\n", list->Money);

	fprintf(File, "%d %s %d\n", list->item[num]->item_num, list->item[num]->item_name, list->item[num]->item_money);//아이템정보 저장되는 파일에서 그 아이템 정보만 바꿔줌
	fclose(File);

	FILE *chf;
	chf = fopen("c:/test/test/make_user.txt", "w");
	if (chf != NULL) {
		while (!feof(chf)) {
			fscanf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp);//그 캐릭터 정보를 list에 담아두기
			if (list_id->num == list->num) {//
				list->Money += list->item[num]->item_money;
				break;
			}
			i++;
		}
		fprintf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", list->num, list->job, list->name, list->level, list->str, list->dex, list->int_, list->HP, list->MP, list->Money, list->exp);
		fclose(chf);
	}
	fclose(chf);
	system("pause");
	system("cls");
	Menu_3();
	return;
}
void Dungeon() {
	//던전입장(몬스터텍스트사용)
	//아주 간단하게 아래와 같은 구조
	//이름 레벨 체력 공격력 골드 경험치
	FILE *File, *Item;
	int i = 0, k = 0;

	File = fopen("c:/test/test/monster.txt", "r");
	Item = fopen("c:/test/test/item.txt", "r");

	for (i = 0; i < 2; i++) {
		list->item[i] = (items*)malloc(sizeof(items));//캐릭터가 가질 아이템정보 동적할당 공간생성
		fscanf(Item, "%d %s %d %d %d %d\n", &list->item[i]->item_num, list->item[i]->item_name, &list->item[i]->attack, &list->item[i]->def, &list->item[i]->item_money, &list->item[i]->item_kind);
	}

	srand((int)time(NULL));
	k = rand() % 2;
	list_mon = (mon*)malloc(sizeof(mon));
	fscanf(File, "%s %d %d %d %d %d\n", list_mon->mon_name, &list_mon->mon_level, &list_mon->mon_HP, &list_mon->mon_attack, &list_mon->mon_money, &list_mon->mon_exp);
	fclose(File);
	printf("던전입장중.....\n");
	Sleep(1000);
	printf("레벨%d의 %s(를)을 조우했습니다!!!\n", list->level, list_mon->mon_name);
	system("pause");
	system("cls");
	list_mon->mon_level = list->level;
	list_mon->mon_HP = list_mon->mon_level * 50;
	list_mon->mon_attack = list_mon->mon_level * 10;
	list_mon->mon_money = list_mon->mon_money*list_mon->mon_level;
	while (1) {
		User_Mng();
		printf("=================================\n");
		printf("\n");
		printf("=================================\n");
		printf("몬스터 : %s\n", list_mon->mon_name);
		printf("레벨 : %d\n", list_mon->mon_level);
		printf("HP : %d\n", list_mon->mon_HP);
		printf("공격력 : %d\n", list_mon->mon_attack);
		printf("=================================\n");
		printf("플레이어의 공격!!\n");
		list_mon->mon_HP = list_mon->mon_HP - (list->str + list->dex + list->int_) / 3;
		printf("%s에게 %d만큼의 데미지를 입혔습니다.\n", list_mon->mon_name, (list->str + list->dex + list->int_) / 3);
		if (list_mon->mon_HP <= 0) {
			printf("%s를 퇴치하였습니다.\n", list_mon->mon_name);
			system("pause");
			printf("%d골드 획득, %d경험치획득\n", list_mon->mon_money, list_mon->mon_exp);

			printf("아이템 %s 획득\n", list->item[k]->item_name);
			list->str = list->str + list->item[k]->attack;
			list->HP = list->HP + list->item[k]->def;
			list->item[k]->item_kind = 1;
			fprintf(Item, "%d %s %d %d %d %d\n", list->item[k]->item_num, list->item[k]->item_name, list->item[k]->attack, list->item[k]->def, list->item[k]->item_money, list->item[k]->item_kind);
			printf("힘이 %d증가, 최대 HP %d증가\n", list->item[k]->attack, list->item[k]->def);
			list->Money = list->Money + list_mon->mon_money;
			list->exp = list->exp + list_mon->mon_exp;
			//k++;
			//if (k == 2) {
			//	k = 0;
			//}
			system("pause");
			if (list->exp >= 100) {
				list->level++;
				list->str += 5;
				list->dex += 5;
				list->int_ += 5;
				list->exp = 0;
				list->HP = list->level * 100;
				printf("레벨이 %d(으)로 업했습니다.\n", list->level);
				system("pause");
			}
			system("cls");
			return;
			Menu_2();
		}
		system("pause");
		printf("%s의 공격!!\n", list_mon->mon_name);
		list->HP = list->HP - list_mon->mon_attack;
		printf("플레이어의 체력이 %d(으)로 줄었습니다.\n", list->HP);
		if (list->HP <= 0) {
			printf("플레이어가 사망했습니다.\n");
			printf("마을로 이동합니다.\n");
			system("pause");
			system("cls");
			return;
			Menu_3();
		}
		system("pause");
		system("cls");
	}
}
void Load() {
	FILE *f;
	f = fopen("c:/test/test/make_user.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
			fscanf(f, "%d %s %s %d %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp, &list->count);
			if (list_id->num == list->num) {
				fprintf(f, "%d %s %s %d %d %d %d %d %d %d %d %d\n", list->num, list->job, list->name, list->level, list->str, list->dex, list->int_, list->HP, list->MP, list->Money, list->exp, list->count);
				return;
			}
		}
		printf("캐릭터정보가 없습니다.\n");
		printf("캐릭터생성으로 이동중.....\n");
		Sleep(1000);
		User_Make();
		fclose(f);
	}
	else {
		printf("캐릭터정보가 없습니다.\n");
		printf("캐릭터생성으로 이동중.....\n");
		Sleep(1000);
		User_Make();
	}
}
void Save() {
	FILE *chf;
	chf = fopen("c:/test/test/make_user.txt", "w");
	if (chf != NULL) {
		while (!feof(chf)) {
			fscanf(chf, "%d %s %s %d %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp, &list->count);
			if (list_id->num == list->num) {
				fprintf(chf, "%d %s %s %d %d %d %d %d %d %d %d %d\n", list->num, list->job, list->name, list->level, list->str, list->dex, list->int_, list->HP, list->MP, list->Money, list->exp, list->count);
				break;
			}
		}
		fclose(chf);
	}
	printf("저장중........\n");
	Sleep(1000);
	printf("저장이 완료되었습니다.\n");
	system("pause");
	system("cls");
	return;
}
