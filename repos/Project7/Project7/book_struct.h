#ifdef BOOK_STRUCT

#else
#define BOOK_STRUCT

typedef struct book {
	int num;  // å ����
	char title[50]; //å ����
	char wirter[50]; // ����
	int book_number; // ������ȣ
	int rent; // �뿩����
	struct book* next; //����Ʈ ����
}book;

book* head = NULL, *tail = NULL;

#endif