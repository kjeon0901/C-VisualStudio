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


mem* choose();
mem* Login();
char* Entry();
char tmp_id[20], tmp_pw[20];
int index = 0;
int size = 10;
mem**list = NULL; //mem*list[]�� �迭������(�������� ȸ������ ����� ����)�ϱ� list[]�� ��� list�� ������������!!

void main() {
	list = (mem**)malloc(size*sizeof(mem*));

	//����, ������ ���� �ҷ����� �Լ�(�ҷ����� �� �޸��忡 ����/������ �̸�, ���ݷ�, ���� ���� �Ἥ ���Ϸ� �����ص� �� �ҷ�����)
	//�α���
	//list[size] = choose(list); //choose�Լ����� �α��μ��� �Ǵ� ȸ�������� �� �� ȸ������ ��� ����ü�� �Ѱ���
	//printf("%s�� ȯ���մϴ�! \n\n", list[]->ID);
	//�޴� ����
}

mem* choose() { //�α������� ȸ���������� ���ϴ� �Լ�. ȸ������ ��� ����ü�� �ٽ� �Ѱ���� ��
	int num;

	printf("1. �α��� \n2. ȸ������");
	scanf("%d", &num);
	while (1) {
		if (num == 1) {//�α����Ѵٰ� ���� ���
			list = Login();//�α����Լ��� ���� ȸ������ ��� ����ü �޾ƿ���
			return list;//�� ����ü �ٽ� �Ѱ���
		}
		else if (num == 2) {
			strcpy(tmp_id, Entry(list));// ���ڿ��� ���ڿ��� �����ϴµ�, �տ������� ���ʴ��...................
			return tmp_id[11];
		}
		else {
			printf("�߸� �Է��߽��ϴ�.");
			system("pause");
		}
		system("cls");
	}
}
mem* Login() {//ȸ������ ��� ����ü �Ѱ���� ��
	mem*tmp = NULL;//���� ���̵�/��й�ȣ �Է��� ����ü ���� �� �ʱ�ȭ
	tmp = (mem*)malloc(sizeof(mem));
	printf("ID: "); //���̵�/��й�ȣ tmp�� �Է¹���
	scanf("%s", tmp->ID);
	printf("PW: ");
	scanf("%s", tmp->PW);
	//���� ���Ͽ� �׿��ִ� ȸ��������� �������� ���ذ��鼭 ��ġ�ϴ� ������ ��ġ�� ã�ӳ��� ��
	File_Load(*list); //���Ͽ� �ִ� ȸ������ �ҷ����� �Լ�.
	
}
void File_Load() {
	FILE*f = fopen("c:/textgame/entry.txt", "r"); //���� �б��������� ����
	if (f != NULL) {//������ ������� �ʴٸ�, �ҷ��ͼ� �����Ҵ�� �迭�� �����ؾ� ��
		while (!feof(f)) {//������ ����������
			list[index] = (ct*)malloc(size*sizeof(ct));//�����Ҵ�. list_[]:�Ѹ�, list_:list_[]�� �ּҸ� ��� ������. ù��°������� �����Ҵ�
			fscanf(f, "%d %s %s", list[index]->num, list[index]->ID, list[index]->PW); //���Ͽ��� �����͸� �ҷ��ͼ� �ش� index��ȣ�� ������� ��.
			index++:
		}
	}
	else {//������ ����ִٸ�, ȸ���������� ��������

	}
	fclose(f);
}
	void Id_Load(char *tmp_id, char *tmp_pw) {//���� �Է��� ���̵�/��й�ȣ �޾Ƽ� �����̶� ���ؾ� ��
		//���̵� ��й�ȣ üũ
		//����� ���Ϸκ��� �о Ȯ���ϱ�
		//���̵� ������ ����� ȸ�������ϵ���
		//ȸ�������Ҷ� ȸ����ȣ�� �ڵ����� ���̵� ��й�ȣ�� �Է��ؼ� �ؽ�Ʈ�� ����
		
		
		char id[2][10];
		FILE *idf;
		idf = fopen("c:/test/test/id_data.txt", "r");
		fscanf(idf, "%s %s\n", id[0], id[1]);
		printf("���̵�:%s  ��й�ȣ:%s\n", id[0], id[1]);
		fclose(idf);
	}

char* Entry() { //char*���� ��. 


	FILE *entry;

	printf("�̸�: ");
	gets(list->name);
	printf("\n���̵�: ");
	gets(list->ID);
	printf("\n��й�ȣ: ");
	gets(list->PW);

	entry = fopen("c:/testgame/entry.txt", "w");
	fprintf(entry, "%s %s %s\n", list->name, list->ID, list->PW);
	fclose(entry);

	return list->ID;
}
int Login_Check(char * a, char* b, mem**list_a, mem**list_b) { //
	if ((a == (*list_a)->ID) && (b == (*list_b)->PW)) //�迭�� ����� ���ڿ����� ���ؾ� �ϴµ� �迭�ּ�(char a)�� mem**list_a(*list_a)�� ������. 
		return 1;
	return 2;
}
