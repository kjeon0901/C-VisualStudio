#define _CRT_SECURE_NO_WARNINGS//scanf오류처리
#include<stdio.h>//입출력 관련 전처리
#include<stdlib.h>
#include<time.h>
#include<windows.h>
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

int Menu();//로그인하면 바로 나타나는 게임메뉴
void Menu_1();
void Menu_2();
void Menu_3();
int Sub_Menu();//서브메뉴
void User_Make();//캐릭터생성
void User_Mng();//캐릭터스테이터스출력
void Save();//게임저장
void New_Game();//새로운게임
void Game_Load();//텍스트파일에 저장된 내용 불러오기
void Load();//로그인정보불러오기
int Town();//마을
int Market();//상점
void Recovery();//회복
void Development();//성장
void Sale();//팔기
void Dungeon();//던전
void choose();//로그인회원가입메뉴선택
int Login();//로그인아이디,비밀번호입력화면
int File_Load(char *tmp_id, char *tmp_pw);//회원정보텍스트파일에 일치확인
void Entry();//회원가입

ct *list = NULL;//로그인, 회원가입 된 회원 정보에 해당하는 캐릭터정보
mem*list_id = NULL;//로그인, 회원가입 된 회원의 회원정보
mon *list_mon = NULL;//몬스터정보
items **list_item[5];//아이템정보
int index = 0, check = 0;//while문등의 반복문을 빠져나올때 사용
int item_index = 0;

void main() {
	FILE *chf, *Item;
	int i;
	chf = fopen("c:/test/test/make_user.txt", "r"); //회원별로 만들어지는 캐릭터 정보가 make_user 파일에 구조체로 저장됨. 게임을 하면서 수정됨
	Item = fopen("c:/test/test/item.txt", "r");
	list = (ct*)malloc(sizeof(ct));//로그인, 회원가입 된 회원 정보에 해당하는 캐릭터정보 동적할당 공간생성
	list_id = (mem*)malloc(sizeof(mem));//회원정보 동적할당 공간생성
	list_mon = (mon*)malloc(sizeof(mon));//몬스터정보 동적할당 공간생성

	for (i = 0; i < 2; i++) {////////////////////////여기아직안봄
		list->item[i] = (items*)malloc(sizeof(items));//캐릭터가 가질 아이템정보 동적할당 공간생성
		fscanf(Item, "%d %s %d %d %d %d\n", &list->item[i]->item_num, list->item[i]->item_name, &list->item[i]->attack, &list->item[i]->def, &list->item[i]->item_money, &list->item[i]->item_kind);
	}
	fclose(Item);///////////////////여기까지아직안봄


	choose();
	Sleep(1000);
	if (index != -1) { //???index==1인 경우가 없지 않았나??
		printf("%s님 환영합니다!\n\n", list_id->ID); //로그인, 회원가입 다 되면 다시 로그인 창이 뜨지 않고 자동 로그인됨
		Sleep(1000);
		system("cls");
		Load();//회원정보에 해당하는 캐릭터 정보 불러오기
		system("cls");
		Menu_1();
	}
	else
		return;
	return;
}
void choose() {// 로그인, 회원가입, 종료 중 선택하는 함수.여기서 index값에 변화가 있음
	int num;
	while (1) {
		printf("1. 로그인 \n2. 회원가입\n");
		printf("선택 : ");
		scanf("%d", &num);
		switch (num) {
		case 1: //로그인 선택하면
			if (Login()) { //로그인함수에서 로그인성공하면 1받아오고 틀리면 0받아옴. 1받아올땐 항상 return 되고, 0받아올땐 자동으로 return 안됨. 
				return; //결과적으로 로그인 성공할 경우만 main함수로 넘어감. entry값은 0
			}
			break;
		case 2: //회원가입 선택하면 그 정보 가지고 자동 로그인, 바로 게임시작
			Entry(); 
			return; //entry 값은 모두 양수인 상태
		default: //셋다 아니면 다시 다시 
			getchar();//???
			getchar();
			system("cls");
			choose();
			return;
		}
		system("cls");
	}
} 
int Login() {//로그인한다고 했을 경우 여기로 와서 문자열 입력받음
	char tmp_id[15], tmp_pw[15];
	getchar();
	printf("아이디 : ");
	scanf("%s", tmp_id);
	getchar();
	printf("비밀번호 : ");
	scanf("%s", tmp_pw);
	return File_Load(tmp_id, tmp_pw); //file_load함수로 내가 입력한 id, pw보내서 맞는지 확인, 맞으면 1받아오고 틀리면 0받아옴. 최종적으로 1 또는 0을 다시 choose함수로 보냄
}
int File_Load(char *tmp_id, char *tmp_pw) {//입력한 tmp과 같은 정보가 파일에 있는지 확인, ????????다시한번확인
	FILE *f; //파일 읽기전용으로 열기
	int member_num = 1;
	char check_id[15] = { "" }, check_pw[15] = { "" };//
	list_id = (mem*)malloc(sizeof(mem));
	f = fopen("c:/test/test/entry.txt", "r");
	if (f != NULL) {//파일이 비어있지 않다면, 불러와서 동적할당된 배열에 저장해야 함
		while (!feof(f)) { //파일 끝날때까지
			fscanf(f, "%d %s %s\n", &member_num, check_id, check_pw);//파일에 있는 정보 처음부터 끝까지 불러오는 동안
			if (!strcmp(check_id, tmp_id) && !strcmp(check_pw, tmp_pw)) { //id, pw 각각 문자열 비교해서 내가 입력한 것과 저장된 정보가 일치하는 경우
				list_id->num = member_num; //그때 그 줄에 저장되어있던 회원정보의 회원번호를 내가 동적할당한 구조체에 담음
				strcpy(list_id->ID, tmp_id); //문자열복사 함수 써서 내가 입력한 아이디를 동적할당한 구조체에 담음
				strcpy(list_id->PW, tmp_pw);//똑같이 입력한 비밀번호를 동적할당한 구조체에 담음
				return 1; //결과적으로 동적할당한 구조체 list_id에는 로그인이 통과되는 회원정보가 담겨 있음.
			}
			member_num++;//일치하지 않는다면 계속 다음줄로 넘어가야 되니까 
		}
		printf("회원 정보가 없습니다\n");//파일끝날때까지 일치하는 정보 못찾으면 0넘겨줌
		system("pause");
		return 0;
	}
	else {//파일이 비어있다면, 회원가입하라고 하기
		printf("등록된 회원이 없습니다\n");
		printf("회원가입하세요\n");
		system("pause");
		return 0;
	}
}
void Entry() { //회원가입 선택했을 때
	FILE *f; 
	int index = 0;
	f = fopen("c:/test/test/entry.txt", "r"); //회원정보 저장되는 파일 읽기 모드로 열어서
	if (f != NULL) { // f파일에 저장된 회원 정보가 있는 경우에만
		while (!feof(f)) { //파일 처음부터 끝까지 읽는 동안에 
			fscanf(f, "%d %s %s\n", &list_id->num, list_id->ID, list_id->PW);//파일로부터 정보 가져와서 main함수에서 공간 할당해둔 list_id구조체에 담기
			index++; //이미 저장되어 있던 회원정보 중 가장 마지막 것의 회원번호를 index로 구하기
		}
	}
	else { // f파일이 비어있는경우엔 fscanf든 fprintf든 아무것도 하지 말기
		index = 0; //새로 저장할 때 회원번호 1부터 시작할 수 있도록 index=0이라고 두기
	}
	getchar();
	f = fopen("c:/test/test/entry.txt", "a"); //파일에 이어서 저장할수있는 a모드로 파일 열기
	list_id->num = index + 1;//새로 저장하는 회원정보의 회원번호를 index+1이라고 두기
	printf("ID: ");
	scanf("%s", list_id->ID);//id입력
	printf("PW: ");
	scanf("%s", list_id->PW);//pw입력
	fprintf(f, "%d %s %s\n", list_id->num, list_id->ID, list_id->PW);//파일에 회원번호, id, pw 저장하기
	
	fclose(f);//파일닫기
	system("pause");
	return;
}
int Menu() {
	int num;
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
		switch (Menu()) {//새게임, 이어하기, 캐릭터 세이브, 캐릭터 불러오기
		case 1://새게임
			New_Game();//y선택한 경우만 여기로 다시 옴(아닌 경우는 menu_1함수 다시 실행)
			User_Make();//그리고 회원번호에 해당하는 새로운 캐릭터 만듦
			system("cls");
			Menu_2();//어디로 이동할지 정하는 함수
			break;
		case 2://회원번호에 해당하는 캐릭터 정보 가져와서 게임 이어하기
			Menu_2();//어디로 이동할지 정하는 함수
			break;
		case 3://파일에 캐릭터 정보(게임 도중 변화되니까) 저장
			Save();//저장하는 함수
			break;
		case 4://회원번호에 해당하는 캐릭터정보 텍스트파일에서 불러오기
			Game_Load();//회원정보로 save한 캐릭터정보 불러와서 이어하기
			Menu_2();//어디로 이동할지 정하는 함수
			break;
		case 5://게임종료
			return;
		default:
			break;
		}
		system("cls");
	}
}
void Menu_2() {//어디로 이동할지 정하는 함수
	system("cls");
	while (1) {
		switch (Sub_Menu()) {//마을갈지 던전갈지 선택
		case 1://마을
			system("cls");
			while (1) {
				switch (Town()) {//마을에 왔을때 상점갈지 안갈지 선택
				case 1:
					//상점
					system("cls");
					Menu_3();//상점에서 뭐할지 선택
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
			if (list->HP > 0) {//체력이 있을 때
				Dungeon();//정말 던전으로 가서 몬스터와 싸움
			}
			else {//체력이 없을 때
				list->HP = 0;//체력이 음수가 되었든 0이 되었든 모두 0으로 두기
				Menu_2();//다시 menu_2함수 시작으로 돌아가서 어디로 갈지 정하기(체력이 없을 땐 던전으로 못 들어감)
				return;
			}
			break;
		case 3://이전으로
			return;//그냥 돌아가면 됨
		}
		system("cls");
	}
}
void Menu_3() {//상점에 왔을때
	while (1) {
		switch (Market()) {//상점에서 뭐할지 선택
		case 1:
			Recovery();//회복하기
			break;
		case 2:
			Development();//성장하기
			break;
		case 3:
			Sale();//판매하기
			break;
		case 4:
			return;
		}
		break;
	}
}
int Sub_Menu() {//마을갈지 던전갈지 선택
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
	printf("이전의 정보는 전부 지워집니다....y/n\n");//정말 지울것인지 확인하는 부분
	getchar();
	printf("입력 : ");
	scanf("%c", &yn);
	if (yn == 'y') {//y누르면 new게임 시작하면서 기존 캐릭터가 있다면 지우고 캐릭터 생성부터 다시 시작.
		while (!feof(chf)) {
			fscanf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp);
			if (list_id->num == list->num) {
				list->num = 0;//회원번호가 0으로 설정되는 일은 없기 때문에 캐릭터 번호를 0으로 둔다는 것은 더이상 쓸 수 없게끔 만들어준다는 것.
				fprintf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", list->num, list->job, list->name, list->level, list->str, list->dex, list->int_, list->HP, list->MP, list->Money, list->exp);
				break;//그렇게 파일에 저장까지 하면 더이상 완전 쓸수없게됨. 새로 만들어야함
			}
		}
		fclose(chf);
		return;//리턴되고 새로 캐릭터 만들러 감
	}
	else if (yn == 'n') {//n누르면 new게임시작하는 걸 반대한다는 뜻이므로 다시 menu_1함수 실행.
		Menu_1();
		return;
	}
	else {//yn 둘다 안누르고 다른걸 누른다면 잘못누른것이므로 다시 menu_1함수 실행
		Menu_1();
		return;
	}
}
void Game_Load() {//파일에 저장된 게임캐릭터 불러오는 함수
	FILE *chf; //캐릭터 정보 저장되어있는 파일 읽기 전용으로 열기
	chf = fopen("c:/test/test/make_user.txt", "r");
	if (chf != NULL) {//파일에 하나라도 정보가 들어있다면//?????????????????????정보가 없는 상태라면? 그런 상태가 될수없나?
		while (!feof(chf)) {//처음부터 끝까지 훑어보면서
			fscanf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp);//내가만든 list라는 동적할당된 변수에 한줄씩 집어넣다가
			if (list_id->num == list->num) {//회원번호와 같은 캐릭터번호를 찾으면
				break;//그 캐릭터를 list에 담은 채로 반복문 빠져나옴
			}
		}
		fclose(chf);
	}
	printf("캐릭터 정보를 가져왔습니다.\n");
	system("pause");
	return;
}
void User_Make() { //회원번호(list_id에 저장되어 있음)를 가져와서 인덱스번호에 넣고 캐릭터 생성
	FILE *chf;//캐릭터 정보가 저장되는 파일을 a모드로 연다. (이유: 파일이 없는 경우 만들어야 하고, 있는 경우엔 정보를 이어서 저장해야 하므로)
	int job_num = 0, a = 1;
	chf = fopen("c:/test/test/make_user.txt", "a");
	printf("=====캐릭터 생성하기=====\n");//캐릭터 저장하려고 동적할당시킨 구조체 변수에 정보 저장
	printf(" 캐릭터명 : ");
	scanf("%s", list->name);
	printf("직업 - 1.전사 2.도적 3.궁수 4.마법사 :  ");
	scanf("%d", &job_num);
	list->level = 1;//신규 캐릭터가 갖는 레벨은 무조건 1로 초기화
	list->Money = 0;//돈 0으로 초기화
	list->num = list_id->num;//캐릭터 번호는 회원번호와 일치시키기
	list->exp = 0;//경험치 0으로 초기화
	list->str = 10;//힘 0으로 초기화
	list->dex = 10;//민첩 0으로 초기화
	list->int_ = 10;//지력 0으로 초기화
	list->HP = list->level * 100;//체력은 100으로 초기화
	list->MP = 50;//마나 0으로 초기화
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
	if (chf != NULL) {//캐릭터정보가 저장되어있는 파일에는 이제 무조건 정보가 들어있음. ???????????그러면 굳이 if를 안써도 되지 않나? if문이 성립 안할때가 있나?
		fprintf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", list->num, list->job, list->name, list->level, list->str, list->dex, list->int_, list->HP, list->MP, list->Money, list->exp);//list구조체변수가 캐릭터 정보를 담고 있었으니까 이걸 이제 파일에 저장. 
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
int Market() {//상점에서 뭐할지 선택
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
void Recovery() {//회복하기 함수
	FILE *chf;//캐릭터 정보 저장되어 있는 파일 쓰기 모드로 열어서(파일 수정해야하니까)
	chf = fopen("c:/test/test/make_user.txt", "w");
	if (chf != NULL) {//파일에 정보가 있을 경우
		while (!feof(chf)) {//처음부터 끝까지 훑어보면서
			fscanf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp);//캐릭터정보를 list 에 담음
			if (list_id->num == list->num) {//그러다가 회원번호랑 같은 캐릭터 번호를 만나면 (자신의 캐릭터를 찾아내는 방법) 체력, 마나, 돈 수정하기
				if (list->Money < 100) {//회복하기를 실행하려면 돈 100원을 내야 하는데, 만약 가지고 있는 돈이 100원보다 적다면
					printf("소지골드가 부족합니다.\n");
					system("pause");
					Menu_3();//자동으로  menu_3, 즉 상점으로 돌아감
					return;
				}
				list->HP = list->level * 100+ list->item[1]->def;//체력 최고치로 올려놓기
				list->MP = 50;//마나 최고치로 올려놓기
				list->Money -= 100;//돈에서 100원 빼기
				break;
			}
		}
		fclose(chf);//????????????그럼 fprintf는 필요없나? 저장안해도 파일도 수정됨?
	}
	Sleep(1000);
	printf("캐릭터가 모두 회복되었습니다.\n");
	system("pause");
	Menu_3();//회복하기가 실행되었을 때 파일 수정 후 다시 menu_3, 즉 상점으로 돌아가기
}
void Development() {//성장하기 함수
	FILE *chf;//캐릭터 정보가 담긴 make_user파일을 쓰기 모드로 열기(파일 수정해야 하니까)
	chf = fopen("c:/test/test/make_user.txt", "w");
	if (chf != NULL) {//파일에 정보가 들어있다면
		while (!feof(chf)) {//처음부터 끝까지 훑으면서
			fscanf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp);//일단 한줄씩 캐릭터정보를 불러와서 list에 담아두기
			if (list_id->num == list->num) {//그러다가 회원번호랑 같은 캐릭터번호를 가진 캐릭터를 만나면 회복하기 실행
				if (list->Money < 300) {//회복하기를 위해서 돈 300이 필요한데 만약 가지고 있는 돈이 300보다 적으면
					printf("소지골드가 부족합니다.\n");
					system("pause");
					Menu_3();//아무것도 처리되지 않고 자동으로 menu_3, 즉 상점으로 다시 돌아감
					return;
				}
				list->str += 2;//돈이 충분하면 
				list->dex += 2;
				list->int_ += 2;
				list->Money -= 300;
				break;
			}
		}
		fclose(chf);//????????????그럼 fprintf는 필요없나? 저장안해도 파일도 수정됨?
	}
	Sleep(1000);
	printf("캐릭터가 소량 성장되었습니다.\n");
	system("pause");
	Menu_3();//성장하기 끝나면 자동으로 menu_3, 즉 상점으로 돌아감
}
void Sale() {//내가 소지한 아이템을 파는 함수
	FILE *File;//아이템이 저장된 파일을 쓰기 모드로 열어서
	int i = 0, num=0;
	File = fopen("c:/test/test/item.txt", "r");
	printf("[현재 소지한 아이템]\n");
	for (i = 0; i < 2; i++) {//아이템 2가지 정보 출력
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
	num -= 1;//선택한건 아이템번호이고, 인덱스 번호는 아이템번호보다 1 작으니까 1 빼줌
	list->Money += list->item[num]->item_money;
	list->item[num]->item_money = 0;
	list->str -= list->item[num]->attack;
	list->def -= list->item[num]->def;
	printf("현재 골드 : %d원\n", list->Money);

	fprintf(File, "%d %s %d\n", list->item[num]->item_num, list->item[num]->item_name, list->item[num]->item_money);//아이템정보 저장되는 파일에서 그 아이템 정보만 바꿔줌
	fclose(File);

	FILE *chf;//캐릭터 파일을 쓰기 모드로 열기
	chf = fopen("c:/test/test/make_user.txt", "w");
	if (chf != NULL) {//파일이 비어있지 않은 경우(어떤 캐릭터라도 저장되어 있는 경우)
		while (!feof(chf)) {//파일을 처음부터 끝까지 훑으면서
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
	int i = 0, k = 0, j = 0;

	File = fopen("c:/test/test/monster.txt", "r");//몬스터텍스트파일 읽기모드로 열기...???????
	Item = fopen("c:/test/test/item.txt", "r");//아이템텍스트파일 읽기모드로 열기

	for (i = 0; i < 2; i++) {
		list->item[i] = (items*)malloc(sizeof(items));//캐릭터가 가질 아이템정보 동적할당 공간생성
		fscanf(Item, "%d %s %d %d %d %d\n", &list->item[i]->item_num, list->item[i]->item_name, &list->item[i]->attack, &list->item[i]->def, &list->item[i]->item_money, &list->item[i]->item_kind);
	}

	srand((int)time(NULL));
	k = rand() % 2;//아이템 처음에 뭐나올지 랜덤으로 정하기
	list_mon = (mon*)malloc(sizeof(mon));//몬스터 공간할당
	fscanf(File, "%s %d %d %d %d %d\n", list_mon->mon_name, &list_mon->mon_level, &list_mon->mon_HP, &list_mon->mon_attack, &list_mon->mon_money, &list_mon->mon_exp);
	fclose(File);//파일에서 꺼내서 list_mon에 담아두기(몬스터는 하나만 만들었음)
	printf("던전입장중.....\n");
	Sleep(1000);
	printf("레벨%d의 %s(를)을 조우했습니다!!!\n", list->level, list_mon->mon_name);
	system("pause");
	system("cls");
	list_mon->mon_level = list->level;//캐릭터의 레벨이 올라가면 몬스터 레벨도 똑같이 올라가도록
	list_mon->mon_HP = list_mon->mon_level * 50;//몬스터 체력 정하기
	list_mon->mon_attack = list_mon->mon_level * 10;//몬스터 공격력 정하기
	list_mon->mon_money = list_mon->mon_money*list_mon->mon_level;//몬스터 이기면 받는 돈 정하기
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
		if (list_mon->mon_HP <= 0) {//계속 반복하다가 몬스터 HP가 0보다 작아지면 골드, 경험치, 아이템 획득
			printf("%s를 퇴치하였습니다.\n", list_mon->mon_name);
			system("pause");
			printf("%d골드 획득, %d경험치획득\n", list_mon->mon_money, list_mon->mon_exp);
			printf("아이템 %s 획득\n", list->item[k]->item_name);//Item_index를 k로 모두 바꿈

			list->str = list->str + list->item[k]->attack; //아이템을 얻었으니까 캐릭터의 힘이 아이템 공격력만큼 증가
			list->HP = list->HP + list->item[k]->def; //아이템을 얻었으니까 캐릭터의 체력이 아이템 방어력만큼 증가
			list->item[k]->item_kind = 1;//????????????
			fprintf(Item, "%d %s %d %d %d %d\n", list->item[k]->item_num, list->item[k]->item_name, list->item[k]->attack, list->item[k]->def, list->item[k]->item_money, list->item[k]->item_kind);
			printf("힘이 %d증가, 최대 HP %d증가\n", list->item[k]->attack, list->item[k]->def);
			list->Money = list->Money + list_mon->mon_money;//캐릭터 머니 증가
			list->exp = list->exp + list_mon->mon_exp;//캐릭터 경험치 증가
			//k++;
			//if (k == 2) {//아이템이 
			//	k = 0;
			//}
			system("pause");
			if (list->exp >= 100) { //경험치 계속 증가하다가 100 넘으면 레벨 1 오르고 경험치는 다시 0으로 초기화
				list->level++;
				list->str += 5;
				list->dex += 5;
				list->int_ += 5;
				list->exp = 0;
				list->HP = list->level * 100;
				printf("레벨이 %d(으)로 업했습니다.\n", list->level);
				system("pause");
			}
			fclose(Item);
			system("cls");
			return;
			Menu_2();//몬스터랑 싸워서 이기면 다시 어디로갈지 정하도록
		}
		system("pause");//mon->HP가 0보다 큰 경우에는 계속 플레이어 HP, 몬스터 HP 가 같이 줄어들면서  반복되도록
		printf("%s의 공격!!\n", list_mon->mon_name);
		list->HP = list->HP - list_mon->mon_attack;
		printf("플레이어의 체력이 %d(으)로 줄었습니다.\n", list->HP);
		if (list->HP <= 0) {
			printf("플레이어가 사망했습니다.\n");//도중에 플레이어HP가 다 닳으면 사망해서 마을로 가도록
			printf("마을로 이동합니다.\n");
			fclose(Item);//
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
	f = fopen("c:/test/test/make_user.txt", "r"); //회원마다 캐릭터 정보를 저장해두는 파일을 읽기 전용으로 열기
	if (f != NULL) {//파일에 정보가 들어있는 경우
		while (!feof(f)) {//파일을 처음부터 끝까지 훑으면서
			fscanf(f, "%d %s %s %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp);//내가 동적할당해둔 공간 list 에 계속 넣어보다가
			if (list_id->num == list->num) {//아까 로그인, 회원가입을 통해 찾아낸 회원번호와 같은 캐릭터 번호를 찾아내면(user_make함수에서 캐릭터정보를 저장할때 애초에 회원정보랑 캐릭터번호랑 같게 했음)
				fprintf(f, "%d %s %s %d %d %d %d %d %d %d %d\n", list->num, list->job, list->name, list->level, list->str, list->dex, list->int_, list->HP, list->MP, list->Money, list->exp);//그 줄에 있는 캐릭터정보를 모두 list에 저장함. 
				return;
			}
		}
		printf("캐릭터정보가 없습니다.\n");//파일 끝까지 가도 아까 로그인, 회원가입을 통해 찾아낸 회원번호와 같은 캐릭터 번호를 찾지 못한다면
		printf("캐릭터생성으로 이동중.....\n");
		Sleep(1000);
		User_Make();//캐릭터 생성하는 함수로 가기
		fclose(f);
	}
	else {//파일에 정보가 아직 아무것도 없는 경우
		printf("캐릭터정보가 없습니다.\n");
		printf("캐릭터생성으로 이동중.....\n");
		Sleep(1000);
		User_Make();//캐릭터 생성하는 함수로 가기
	}
}
void Save() {
	FILE *chf;//캐릭터정보 저장하는 파일 쓰기모드로 열어서 수정
	chf = fopen("c:/test/test/make_user.txt", "w");
	if (chf != NULL) {
		while (!feof(chf)) {
			fscanf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp);
			if (list_id->num == list->num) {
				fprintf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", list->num, list->job, list->name, list->level, list->str, list->dex, list->int_, list->HP, list->MP, list->Money, list->exp);
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