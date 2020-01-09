#ifdef STRUC

#else
#define STRUC

#include"index.h"

typedef struct test {
	int num;
	char name[10];
}test;

test **list; //전역으로 구조체 2차원 포인터변수 만들기
int count = 1;


#endif