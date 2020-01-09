#include "index.h"
#include "Book_Mng.h"
#include "Book_Struct.h"
#include "Book_Rent.h"
#include "Menu.h"
/*
메뉴			서브메뉴
1. 도서 대여    1. -> 1) 전체 목록
2) 대여 가능 도서
2. 도서 반납
3. 도서 관리     3. -> 1) 도서 등록
4. 종료				   2) 도서 삭제
3) 도서 목록
-> 도서 구조체를 메뉴에 맞게 만들기
-> 처음 실행 할때 도서목록 불러오기
-> 종료시  저장하고 종료 되게 만들기
*/

void main() {
	Init();
	while (1) {
		switch (Main_Menu()) {
		case 1:
			Sub_Menu(1); break;
		case 2:
			Return_Book(); break;
		case 3:
			Sub_Menu(3); break;
		case 4:
			Save_Book();
			return;
		}
		system("cls");
	}
}