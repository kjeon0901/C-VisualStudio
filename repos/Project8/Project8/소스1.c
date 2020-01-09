#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct member { //ȸ������ ����ü ����
	int num;
	char ID[20];
	char PW[20];
}mem;
typedef struct items {
	char item_name[30];//�������̸�
	int item_kind;//���������
	int attack;//���ݷ�
	int ac;//����
	int HP_, MP_;//����
	int item_money;//�ǸŽ� ����
}items;
typedef struct character {
	int num;
	int exp;
	char name[20];//ĳ�����̸�
	int level;//����
	char job[10];//����
	int str, dex, int_;//�� ��ø ����
	int HP, MP;//ü�� ����
	int Money;//���
	char skill[10][50];//��ų
	struct items *item[100];//������,
}ct;

mem**list_ = NULL;

int index = 0;
int choose(int size);
int Login(int size);
int File_Load(mem*tmp, int size);
int Entry(int size);
void main() {
	int size = 1; //ȸ������ �ϸ� �Ҽ��� size++�ǵ���
	list_ = (mem**)malloc(size * sizeof(mem*));
	int sel=0;

	index = choose(size);//index��ȣ ����
	if (index != -1) {
		printf("%s�� ȯ���մϴ�!\n\n", list_[index]->ID);
		//�޴�����
	}
	else
		return;
}
int choose(int size) {// index��ȣ �Ѱ���
	int num;
	printf("1. �α��� \n2. ȸ������\n");
	scanf("%d", &num);
	while (1) {
		if (num == 1) {//�α����Ѵٰ� ���� ���
			index = Login(size);//�α����Լ��� ���� ȸ������ ��� ����ü �޾ƿ���
			if (index != -1)
				return index;//�� ����ü �ٽ� �Ѱ���
			else
				return -1;
		}
		else if (num == 2) {//ȸ�������Ѵٰ� ���� ���
			index = Entry(size);//ȸ������ ��� ���ο� ����ü�� index��ȣ �޾ƿ�
			index-=1;
			return index;
		}
		else {
			printf("�߸� �Է��߽��ϴ�.\n");
			system("pause");
		}
		system("cls");
	}
}
int Login(int size) {//index��ȣ �Ѱ���
	mem*tmp = NULL;//���� ���̵�/��й�ȣ �Է��� ����ü ���� �� �ʱ�ȭ
	tmp = (mem*)malloc(sizeof(mem));
	printf("ID: "); //���̵�/��й�ȣ tmp�� �Է¹���
	scanf("%s", tmp->ID);
	printf("PW: ");
	scanf("%s", tmp->PW);
	//���� ���Ͽ� �׿��ִ� ȸ��������� �������� ���ذ��鼭 ��ġ�ϴ� ������ ��ġ�� ã�Ƴ��� ��
	index = File_Load(tmp, size); //index��ȣ �޾ƿ�
	if (index != -1)
		return index;
	else
		return -1;
}
int File_Load(mem*tmp, int size) {//�Է��� tmp�� ���� ������ ���Ͽ� �ִ��� Ȯ��
	FILE*f = fopen("c:/textgame/entry.txt", "r"); //���� �б��������� ����
	if (f != NULL) {//������ ������� �ʴٸ�, �ҷ��ͼ� �����Ҵ�� �迭�� �����ؾ� ��
		while(!feof(f)){ //���� ����������
			list_[index] = (mem*)malloc(size * sizeof(mem));
			fscanf(f, "%d %s %s", &list_[index]->num, list_[index]->ID, list_[index]->PW);
			if (!strcmp(list_[index]->ID, tmp->ID) && !strcmp(list_[index]->PW, tmp->PW)) {
				return index;
			}
			index++;
		}
		printf("ȸ�� ������ �����ϴ�\n");
		return -1;
	}
	else {//������ ����ִٸ�, ȸ�������϶�� �ϱ�
		printf("��ϵ� ȸ���� �����ϴ�\n");
		printf("ȸ�������ϼ���\n");
		return -1;
	}
}
int Entry(int size) {
	FILE*f = fopen("c:/textgame/entry.txt", "a");
	mem*new_entry = (mem*)malloc(sizeof(mem)); //�����Է��� ����ü ����
	mem*move = list_[0]; //���Ͽ� ����ִ� ���� ���� �� ����ü ����, list_[0]->num=1
	if (f != NULL) { //���Ͽ� �̹� ���� ��� �ִ� ���, �길 �ϸ� ��!!
		while (!feof(f)) {
			move->num += 1; //move->num�� ��� �ִ� ���� ���Ͽ� ��� �ִ� ���� ����+1�� ����
		}
		list_ = (mem**)realloc(list_, (move->num) * sizeof(mem*));
		list_[move->num-1] = new_entry;
		new_entry->num = list_[move->num - 2]->num + 1;
	}
	else {
		new_entry->num = 1;
	}
	printf("ȸ����ȣ:%d", new_entry->num);
	printf("ID: ");
	scanf("%s", new_entry->ID);
	printf("PW: ");
	scanf("%s", new_entry->PW);
	fprintf(f, "%d %s %s\n", new_entry->num, new_entry->ID, new_entry->PW);
	fclose(f);
	return new_entry->num - 1;
}