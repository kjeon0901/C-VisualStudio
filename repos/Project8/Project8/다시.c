#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct member {
	int num; //ȸ����ȣ
	char ID[20];
	char PW[20];
	struct mem *next;
}mem;

mem*head=NULL, *tail=NULL;
mem*move = NULL; 
int count = 1;
char tmp_id[20], tmp_pw[20];

mem*choose(mem*pass);
mem* Login(mem*pass);
mem*Entry();
//mem* Login_Check(mem*tmp);

void main() {
	head = (mem*)malloc(count * sizeof(mem));
	head->num = 0;
	head->next = NULL;
	tail = head;
	mem*pass=head;
	if (choose(head, pass) == pass) {
		pass = choose(head, pass);
		printf("%s�� ȯ���մϴ�!\n\n", pass->ID);
		//�޴� ����
	}
	else {
		return;
	}
}
mem*choose(mem*pass) {
	int num;
	printf("1. �α��� \n2. ȸ������\n");
	scanf("%d", &num);
	while (1) {
		if (num == 1) { //�α���
			if (Login(pass) == head) {
				return head;
			}
			else {
				pass = Login(pass);
				return pass;
			}
		}
		else if (num == 2) { //ȸ������
			pass = Entry();
			return pass;
		}
		else {
			printf("�߸� �Է��߽��ϴ�.\n");
			system("pause");
			return head;
		}
		system("cls");
	}	
}
/*
mem* Login(mem*pass) {
	mem*tmp=NULL;//�긦 �ٲ�����ҰͰ�����
	tmp = (mem*)malloc(sizeof(mem));

	printf("ID: ");
	scanf("%s", tmp->ID);
	printf("PW: ");
	scanf("%s", tmp->PW);
	if (Login_Check(tmp) == head) { //��ġ�� ��쿡�� pass�� ����
		printf("ȸ�������� �����ϴ�\n");
		system("pause");
		system("cls");
		return head;
	}
	else {
		pass = move;
		return pass;
	}
}
*/
mem*Entry() {
	FILE*entry = fopen("c:/textgame/entry.txt", "w");
	
	mem*new = (mem*)malloc(sizeof(mem));
	new->num = tail->num + 1;
	printf("ID: ");
	scanf("%s", new->ID);
	printf("PW: ");
	scanf("%s", new->PW);
	new->next = NULL;
	tail->next = new;
	tail = new;

	fprintf(entry, "%d %s %s\n\n", new->num, new->ID, new->PW);
	fclose(entry);

	return new;
}
/*
mem* Login_Check(mem*tmp) { //���� �Է��� ID, PW�� ��ġ�ϴ� �� �ִ��� Ȯ��
	move = head; //�տ������� ������ �Ⱦ�� �ϹǷ� head�� �ʱ�ȭ
	while (move->next != NULL) { //Ȯ��x
		if ((strcmp(move->ID, tmp->ID)==0)&&(strcmp(move->PW, tmp->PW) == 0)) { //Ȯ��x
			return move;
		}
		move = move->next;
	}
	printf("�߸� �Է��Ͽ��ų� ȸ�� ������ �����ϴ�\n");
	return  head;
}
*/