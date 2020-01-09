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


mem* choose();
mem* Login();
char* Entry();
char tmp_id[20], tmp_pw[20];
int index = 0;
int size = 10;
mem**list = NULL; //mem*list[]가 배열포인터(여러명의 회원정보 만들기 위해)니까 list[]를 담는 list는 이차원포인터!!

void main() {
	list = (mem**)malloc(size*sizeof(mem*));

	//몬스터, 아이템 각각 불러오기 함수(불러오는 건 메모장에 몬스터/아이템 이름, 공격력, 방어력 직접 써서 파일로 저장해둔 걸 불러오기)
	//로그인
	//list[size] = choose(list); //choose함수에서 로그인성공 또는 회원가입할 때 그 회원정보 담긴 구조체를 넘겨줌
	//printf("%s님 환영합니다! \n\n", list[]->ID);
	//메뉴 실행
}

mem* choose() { //로그인할지 회원가입할지 정하는 함수. 회원정보 담긴 구조체를 다시 넘겨줘야 함
	int num;

	printf("1. 로그인 \n2. 회원가입");
	scanf("%d", &num);
	while (1) {
		if (num == 1) {//로그인한다고 했을 경우
			list = Login();//로그인함수로 가서 회원정보 담긴 구조체 받아오기
			return list;//그 구조체 다시 넘겨줌
		}
		else if (num == 2) {
			strcpy(tmp_id, Entry(list));// 문자열을 문자열에 대입하는데, 앞에서부터 차례대로...................
			return tmp_id[11];
		}
		else {
			printf("잘못 입력했습니다.");
			system("pause");
		}
		system("cls");
	}
}
mem* Login() {//회원정보 담긴 구조체 넘겨줘야 함
	mem*tmp = NULL;//내가 아이디/비밀번호 입력할 구조체 생성 후 초기화
	tmp = (mem*)malloc(sizeof(mem));
	printf("ID: "); //아이디/비밀번호 tmp에 입력받음
	scanf("%s", tmp->ID);
	printf("PW: ");
	scanf("%s", tmp->PW);
	//이제 파일에 쌓여있는 회원정보들과 한줄한줄 비교해가면서 일치하는 정보의 위치를 찾앙내야 함
	File_Load(*list); //파일에 있는 회원정보 불러오는 함수.
	
}
void File_Load() {
	FILE*f = fopen("c:/textgame/entry.txt", "r"); //파일 읽기전용으로 열기
	if (f != NULL) {//파일이 비어있지 않다면, 불러와서 동적할당된 배열에 저장해야 함
		while (!feof(f)) {//파일이 끝날때까지
			list[index] = (ct*)malloc(size*sizeof(ct));//동적할당. list_[]:한명, list_:list_[]의 주소를 담는 포인터. 첫번째사람에게 동적할당
			fscanf(f, "%d %s %s", list[index]->num, list[index]->ID, list[index]->PW); //파일에서 데이터를 불러와서 해당 index번호의 사람에게 줌.
			index++:
		}
	}
	else {//파일이 비어있다면, 회원가입으로 보내야함

	}
	fclose(f);
}
	void Id_Load(char *tmp_id, char *tmp_pw) {//내가 입력한 아이디/비밀번호 받아서 파일이랑 비교해야 함
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

char* Entry() { //char*여야 함. 


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
