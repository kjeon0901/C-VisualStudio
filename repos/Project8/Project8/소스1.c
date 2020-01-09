#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct member { //회원정보 구조체 형식
	int num;
	char ID[20];
	char PW[20];
}mem;
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

mem**list_ = NULL;

int index = 0;
int choose(int size);
int Login(int size);
int File_Load(mem*tmp, int size);
int Entry(int size);
void main() {
	int size = 1; //회원가입 하면 할수록 size++되도록
	list_ = (mem**)malloc(size * sizeof(mem*));
	int sel=0;

	index = choose(size);//index번호 받음
	if (index != -1) {
		printf("%s님 환영합니다!\n\n", list_[index]->ID);
		//메뉴실행
	}
	else
		return;
}
int choose(int size) {// index번호 넘겨줌
	int num;
	printf("1. 로그인 \n2. 회원가입\n");
	scanf("%d", &num);
	while (1) {
		if (num == 1) {//로그인한다고 했을 경우
			index = Login(size);//로그인함수로 가서 회원정보 담긴 구조체 받아오기
			if (index != -1)
				return index;//그 구조체 다시 넘겨줌
			else
				return -1;
		}
		else if (num == 2) {//회원가입한다고 했을 경우
			index = Entry(size);//회원정보 담긴 새로운 구조체의 index번호 받아옴
			index-=1;
			return index;
		}
		else {
			printf("잘못 입력했습니다.\n");
			system("pause");
		}
		system("cls");
	}
}
int Login(int size) {//index번호 넘겨줌
	mem*tmp = NULL;//내가 아이디/비밀번호 입력할 구조체 생성 후 초기화
	tmp = (mem*)malloc(sizeof(mem));
	printf("ID: "); //아이디/비밀번호 tmp에 입력받음
	scanf("%s", tmp->ID);
	printf("PW: ");
	scanf("%s", tmp->PW);
	//이제 파일에 쌓여있는 회원정보들과 한줄한줄 비교해가면서 일치하는 정보의 위치를 찾아내야 함
	index = File_Load(tmp, size); //index번호 받아옴
	if (index != -1)
		return index;
	else
		return -1;
}
int File_Load(mem*tmp, int size) {//입력한 tmp과 같은 정보가 파일에 있는지 확인
	FILE*f = fopen("c:/textgame/entry.txt", "r"); //파일 읽기전용으로 열기
	if (f != NULL) {//파일이 비어있지 않다면, 불러와서 동적할당된 배열에 저장해야 함
		while(!feof(f)){ //파일 끝날때까지
			list_[index] = (mem*)malloc(size * sizeof(mem));
			fscanf(f, "%d %s %s", &list_[index]->num, list_[index]->ID, list_[index]->PW);
			if (!strcmp(list_[index]->ID, tmp->ID) && !strcmp(list_[index]->PW, tmp->PW)) {
				return index;
			}
			index++;
		}
		printf("회원 정보가 없습니다\n");
		return -1;
	}
	else {//파일이 비어있다면, 회원가입하라고 하기
		printf("등록된 회원이 없습니다\n");
		printf("회원가입하세요\n");
		return -1;
	}
}
int Entry(int size) {
	FILE*f = fopen("c:/textgame/entry.txt", "a");
	mem*new_entry = (mem*)malloc(sizeof(mem)); //새로입력할 구조체 생성
	mem*move = list_[0]; //파일에 들어있는 값의 갯수 셀 구조체 생성, list_[0]->num=1
	if (f != NULL) { //파일에 이미 값이 들어 있는 경우, 얘만 하면 끝!!
		while (!feof(f)) {
			move->num += 1; //move->num에 들어 있는 값은 파일에 들어 있는 값의 갯수+1과 같음
		}
		list_ = (mem**)realloc(list_, (move->num) * sizeof(mem*));
		list_[move->num-1] = new_entry;
		new_entry->num = list_[move->num - 2]->num + 1;
	}
	else {
		new_entry->num = 1;
	}
	printf("회원번호:%d", new_entry->num);
	printf("ID: ");
	scanf("%s", new_entry->ID);
	printf("PW: ");
	scanf("%s", new_entry->PW);
	fprintf(f, "%d %s %s\n", new_entry->num, new_entry->ID, new_entry->PW);
	fclose(f);
	return new_entry->num - 1;
}