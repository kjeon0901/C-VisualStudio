#ifdef BOOK_STRUCT

#else
#define BOOK_STRUCT

typedef struct book {
	int num;  // 책 순번
	char title[50]; //책 제목
	char wirter[50]; // 저자
	int book_number; // 관리번호
	int rent; // 대여여부
	struct book* next; //리스트 연결
}book;

book* head = NULL, *tail = NULL;

#endif