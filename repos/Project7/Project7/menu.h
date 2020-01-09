#ifdef MENU

#else
#define MENU
#include "index.h"
#include "Book_Mng.h"
#include "Book_Rent.h"
#include "Book_Struct.h"

void Load_Book() {
	FILE *File_;
	book* new_data = NULL;
	File_ = fopen("c:/test/book.txt", "r");
	if (File_ != NULL) {
		while (!feof(File_)) {
			new_data = (book*)malloc(sizeof(book));
			fscanf(File_, "%d %s %s %d %d\n", &new_data->num, new_data->title, new_data->wirter, &new_data->book_number, &new_data->rent);
			new_data->next = NULL;
			tail->next = new_data;
			tail = new_data;
		}
		fclose(File_);
	}
}
void Save_Book() {
	FILE *File_;
	book* Data_Save = head->next, *Lift = NULL;
	File_ = fopen("c:/test/book.txt", "w");
	while (Data_Save != NULL) {
		fprintf(File_, "%d %s %s %d %d\n", Data_Save->num, Data_Save->title, Data_Save->wirter, Data_Save->book_number, Data_Save->rent);
		Lift = Data_Save;
		Data_Save = Data_Save->next;
		free(Lift);
	}
	fclose(File_);
}

void Init() {
	head = (book*)malloc(sizeof(book));
	head->num = 0;
	head->book_number = 2018121001;
	head->next = NULL;
	tail = head;
	Load_Book();
}
int Main_Menu() {
	int num;
	printf("1. ���� �뿩\n");
	printf("2. ���� �ݳ�\n");
	printf("3. ���� ����\n");
	printf("4. ����\n");
	printf("���� : ");
	scanf("%d", &num);
	return num;
}
int Sub_Menu(int Mnum) {
	int sel;
	system("cls");
	switch (Mnum) {
	case 1:// �뿩
		printf("1. ��ü ���\n");
		printf("2. �뿩���� ����\n");
		printf("3. ��������\n");
		printf("���� : ");
		scanf("%d", &sel);
		if (sel == 1) {
			All_View();
			system("pause");
		}
		if (sel == 2)
			Rentable_View();
		break;
	case 3:// ����
		printf("1. ���� ���\n");
		printf("2. ���� ����\n");
		printf("3. ���� ���\n");
		printf("4. ��������\n");
		printf("���� : ");
		scanf("%d", &sel);
		if (sel == 1)
			Book_Enter();
		if (sel == 2)
			Book_delete();
		if (sel == 3) {
			All_View();
			system("pause");
		}
		break;
	}
}
#endif