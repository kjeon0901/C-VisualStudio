#ifdef Book_Mng

#else
#define Book_Mng


#include "index.h"
#include "Book_Struct.h"

void All_View() { //전체 목록
	book* View = head->next;
	while (View != NULL) {
		printf("%d %s %s %d %d\n", View->num, View->title, View->wirter, View->book_number, View->rent);
		View = View->next;
	}
}
void Book_Enter() {
	book* New_Data = (book*)malloc(sizeof(book));
	New_Data->num = tail->num + 1;
	New_Data->book_number = tail->book_number + 1;
	printf("책 제목 : ");
	scanf("%s", New_Data->title);
	printf("책 저자 : ");
	scanf("%s", New_Data->wirter);
	New_Data->rent = 0;
	New_Data->next = NULL;
	tail->next = New_Data;
	tail = New_Data;
}
void Book_delete() {
	int sel;
	book* Pre_book = head, *Del_Book = head;
	All_View();
	printf("삭제 도서 번호 : ");
	scanf("%d", &sel);
	while (Del_Book->next != NULL) {
		Del_Book = Del_Book->next;
		if (Del_Book->book_number == sel)
			break;
		Pre_book = Pre_book->next;
	}
	if (Del_Book == Pre_book) {
		printf("존재 하지 않는 책입니다. \n");
		system("cls");
		return;
	}
	Pre_book->next = Del_Book->next;
	printf("관리번호 : %d  제목 : %s \n", Del_Book->book_number, Del_Book->title);
	free(Del_Book);
}
#endif