#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct member {
	int num; //ȸ����ȣ
	char ID[20];
	char PW[20];
}mem;

int count = 1;
char choose(mem*list);
char Login(mem*list);
char* Entry(mem*list);
int Login_Check(char * a, char* b, mem**list_a, mem**list_b);
//int Menu();
char tmp_id[20], tmp_pw[20];


void main() {
	mem*list;
	list = (mem*)malloc(count * sizeof(mem));

	//����, ������ ���� �ҷ����� �Լ�(�ҷ����� �� �޸��忡 ����/������ �̸�, ���ݷ�, ���� ���� �Ἥ ���Ϸ� �����ص� �� �ҷ�����)
	//�α���
	tmp_id[20] = choose(list);
	printf("%s�� ȯ���մϴ�! \n\n", tmp_id[11]);
	//�޴� ����
}

char choose(mem*list) {
	int num;

	printf("1. �α��� \n2. ȸ������\n");
	scanf("%d", &num);
	while (1) {
		if (num == 1) {
			tmp_id[20] = Login(list);
			return tmp_id[20];
		}
		else if (num == 2) {
			strcpy(tmp_id, Entry(list));// ���ڿ��� ���ڿ��� �����ϴµ�, �տ������� ���ʴ��
			return tmp_id[20];
		}
		else {
			printf("�߸� �Է��߽��ϴ�.\n");
			system("pause");
		}
		system("cls");
	}
}
char Login(mem*list) {

	char myID[] = "kiwi";
	char myPW[] = "kiwi1234!";

	printf("���̵�: ");
	scanf("%s", list->ID);
	printf("��й�ȣ: ");
	scanf("%s", list->PW);

	switch (Login_Check(myID, myPW, *list->ID, *list->PW)) {
	case 1:
		return tmp_id[20];
	case 2:
		printf("ID �Ǵ� PW�� �߸� �Է��Ͽ��ų� ȸ�� ����� ���� �ʾҽ��ϴ�. \n");
		choose(list); //�°� �Ѱǰ�?
	}
}
char* Entry(mem*list) { //char�°� �Ѱǰ�? //Ʋ����. char*���� ��. 


	FILE *entry;


	printf("\n���̵�: ");
	scanf("%d", &list->ID);
	printf("\n��й�ȣ: ");
	scanf("%d", &list->PW);
	//ȸ����ȣ: tail->num+1�� �α�

	entry = fopen("c:/testgame/entry.txt", "w");
	fprintf(entry, "%s %s %s\n", list->num, list->ID, list->PW);
	fclose(entry);

	return list->ID;
}
int Login_Check(char * a, char* b, mem**list_a, mem**list_b) { //
	if ((a == (*list_a)->ID) && (b == (*list_b)->PW)) //�迭�� ����� ���ڿ����� ���ؾ� �ϴµ� �迭�ּ�(char a)�� mem**list_a(*list_a)�� ������. 
		return 1;
	return 2;
}