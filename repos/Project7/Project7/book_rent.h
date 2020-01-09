#ifdef BOOK_Rent

#else
#define BOOK_Rent
#include "index.h"
#include "Book_Struct.h"

void Rent_Book() { //대여
	int sel;
	book* Pre_book = head, *Give_Book = head, *Give_Book_=head;
	All_View();
	printf("대여 도서 번호 : ");
	scanf("%d", &sel);
	
	if (Give_Book->rent==1) {
		printf("대여가 불가능합니다\n");
	}
	else if (Give_Book == Pre_book) {
		printf("존재 하지 않는 책입니다. \n");
		system("cls");
		return;
	}
	while (Give_Book->next != NULL) {
		Give_Book_ = Give_Book;
		Give_Book_->rent = 1;
		Give_Book_->next = Give_Book->next;
		Pre_book->next = Give_Book_;
	}
	
	free(Give_Book);
}
void Return_Book() { //반납
	int sel;
	book* Pre_book = head, *Book_Save = head, *Book_Save_ = head;
	All_View();
	printf("반납 도서 번호 : ");
	scanf("%d", &sel);

	if (Book_Save->rent == 0) {
		printf("잘못 입력\n");
		return;
	}
	else if (Book_Save == Pre_book) {
		printf("존재 하지 않는 책입니다. \n");
		system("cls");
		return;
	}
	while (Book_Save->next != NULL) {
		Book_Save_ = Book_Save;
		Book_Save_->rent = 0;
		Book_Save_->next = Book_Save->next;
		Pre_book->next = Book_Save_;
	}

	free(Book_Save);
}
void Rentable_View() { //대여가능 도서
	book* View = head->next;
	FILE *Fy;
	while (View != NULL) {
		if (View->rent == 0) {
			Fy = fopen("c:/test/bookyes.txt", "w");
			fprintf(Fy, "%d번  제목:%s  저자:%s  책번호:%d  대여가능여부:%d\n", View->num, View->title, View->wirter, View->book_number, View->rent);

			View = View->next;
		}
	}
	fclose(Fy);
}

#endif