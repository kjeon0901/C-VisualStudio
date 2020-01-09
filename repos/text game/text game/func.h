#ifdef FUNC

#else 
#define FUNC


#include"index.h"
#include"struc.h"

void init();
void input();
void disp();
void save();
void load();

void init() {
	list = (test**)malloc(count * sizeof(test*));
	list[0] = (test*)malloc(sizeof(test));//구조체공간 동적할당
}
void input() {

	printf("번호: ");
	scanf("%d", &list[count - 1]->num);
	printf("이름: ");
	scanf("%s", list[count - 1]->name);

	count++;
	list = (test**)realloc(list, count * sizeof(test*));
	list[count - 1] = (test*)malloc(sizeof(test)); //왜 count에서 1빼는지 이해안됨
}
void load() { //저장은 입력과 비슷하니까 input함수와 비슷
	FILE *lf;

	lf = fopen("c:/test/test.txt", "r");
	if (lf != NULL) { //NULL값이 들어가 있다는 건 파일이 안 열렸다는 것
		while (!feof(lf)) { //한줄한줄 읽으면서 메모리 있으면 0, 없으면 -1반환
			fscanf(lf, "%d %s \n", &list[count - 1]->num, &list[count - 1]->name); //마지막 한줄 빈공간도 커서가 있음. 마지막 개행도 따지기 위해 \n 넣은것.쓰지 않으면 빈공간 한줄도 포함해서 5줄이라고 읽음. 

			count++;
			list = (test**)realloc(list, count * sizeof(test*));
			list[count - 1] = (test*)malloc(sizeof(test));
		}
		fclose(lf);
	}
}
void disp() {
	int i;
	for (i = 0; i < count - 1; i++) {
		printf("번호: %d 이름: %s \n", list[i]->num, list[i]->name);
	}
}
void save() { //저장은 출력과 비슷하니까 disp함수와 비슷
	FILE*sf;
	int i;
	sf = fopen("c:/test/test.txt", "w"); //위치 안써도 되나?

	for (i = 0; i < count - 1; i++) {
		fprintf(sf, "%d %s \n", list[i]->num, list[i]->name);
	}
	fclose(sf);
}

#endif