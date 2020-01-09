#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

/*
[링크드 리스트]
-단일리스트
리스트 n에 구조체 공간 담기, 리스트 n은 n+1의 주소를 담고 있음
시작:head, 끝:tail=>계속 변함 (포인터로 만듦)

-이중리스트
-환행리스트
*/

typedef struct student {
	int num;
	char name[10];
	struct student *next; //자신의 주소(다음 공간)를 가질 수 있는 next라는 이름의 포인터 변수 만듦. 내부참조
}std;

std* input(std*top); //head가 포인터변수니까 포인터변수로 받되, top이라는 이름으로 받음
void main() {
	std*head = NULL;
	head = input(head); //데이터입력
	head = input(head); //1번 가진 head 보내면 top이 받음. 
	head = input(head);


}
std* input(std*top) {
	std*tail = top;	//while문 갈수밖에 없는 이유: tail, head가 둘다 지역변수라서
	std*temp = NULL;

	temp = (std*)malloc(sizeof(std)); //temp에 첫번째 공간할당
	printf("번호: ");
	scanf("%d", &temp->num); //->가 &보다 먼저. num은 메모리니까 주소를 나타내기 위해 &
	printf("이름: ");
	scanf("%s", temp->name); //->가 &보다 먼저. name은 name[]의 주소니까 &필요없음
	temp->next = NULL; //완전중요

	if (top == NULL) //첫번째 input에만 실행됨
		return temp; //안써주면 temp가 지역변수라서 첫번째 리스트가 사라짐. 
	while (tail->next != NULL) { //while문 완전중요. 완벽히 이해해야 함.
		tail = tail->next;
	}
	tail->next = temp;

	return top;
}