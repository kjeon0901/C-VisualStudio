#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/*
������1. ���Ͽ� ���ο� ���̵� �Էµ� ������ 
					num���� ��� �����ؾ� �ϴµ�, ��� 1��.
������2. ��·�� ȸ�������ؼ� ���Ͽ� ������ �����Ų �ڿ� �� ���̵�� �α����� �ϸ� 
					"ȯ���մϴ�"�� ���� �ϴµ� ��� "ȸ�������� ���ų� �߸� �Է�"�̶�� ��
������3. choose�Լ��� while���� 2�������� �����
*/

typedef struct member {
	int num; //ȸ����ȣ
	char ID[20];
	char PW[20];
	struct mem *next;
}mem;
mem*head = NULL, *tail = NULL;
char tmp_id[20], tmp_pw[20];

mem*choose(mem*pass);
mem*Login(mem*pass);
mem*Entry();
mem*Login_Check(mem*tmp);
void main() {

	mem*pass = NULL;
		pass = choose(pass); //�α��� ȸ������ �����Լ�, Ȯ�ε� ���̵� ����ü ������
		printf("%s�� ȯ���մϴ�!\n\n", pass->ID);

}
mem*choose(mem*pass) {
	head = (mem*)malloc(sizeof(mem));//��������head�� �����Ҵ� �� �ʱ�ȭ
	head->num = 0;
	head->next = NULL;
	tail = head;
	int num;

	while (1) {
	printf("1. �α��� \n2. ȸ������\n");
	scanf("%d", &num);
		if (num == 1) {
			if (Login(pass)->ID == pass->ID) {
				pass = Login(pass); return pass;
			}
		}
		else if (num == 2) {
				pass = Entry();

				return pass;
		}
		else {
				printf("�߸� �Է�\n");
				system("pause");	
		}
		system("cls");
	}
}
mem*Login(mem*pass) {
	mem*tmp = NULL;
	tmp = (mem*)malloc(sizeof(mem));

	printf("ID: ");
	scanf("%s", tmp->ID);
	printf("PW: ");
	scanf("%s", tmp->PW);

	tmp = Login_Check(tmp);
	return tmp;
}
mem*Entry() { 
FILE*f = fopen("c:/textgame/entry.txt", "a+b"); 

	mem*new = (mem*)malloc(sizeof(mem));
	new->num = tail->num+1;
	printf("ID: ");
	scanf("%s", new->ID);
	printf("PW: ");
	scanf("%s", new->PW);
	new->next = NULL;	
	fprintf(f, "%d %s %s \r\n", new->num, new->ID, new->PW);
	fclose(f);

	if (head == NULL) {
		head = new;
		tail = head;
		return tail;
	}
	else { 
		tail->next = new;
		tail = new;
		return tail;
	}
	free(new);//return �ڿ� �ᵵ �ǳ�?
}
mem*Login_Check(mem*tmp) {
	mem*move = head;;
	while(move!=tail->next){
		if (strcmp(move->ID, tmp->ID) == 0 && strcmp(move->PW, tmp->PW) == 0) {
			return move;
		}
		move = move->next;
	} 
	printf("ȸ�������� ���ų� �߸� �Է�\n");
	system("pause");
	system("cls");
}