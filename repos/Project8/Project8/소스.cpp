#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
�ؽ�Ʈ rpg game
1.ĳ���� �����
2.���� ����
3.������(����,��,����)
sleep�Լ�����
*/
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

int Menu();
void User_Make(int a);//ĳ���ͻ���
void User_Mng(int a);//ĳ���ͽ������ͽ�
					 //void Item_Make();//�����ۻ���,�ؽ�Ʈ���� ������ ������ �����ͼ� ������ ���
void Game_();//���ӽ���
void Save();//��������
void Load();//���Ӻҷ�����
void Id_Load(char *tmp_id, char *tmp_pw);
char* Login();//�α���,ȸ�������ؽ�Ʈ���Ͽ� ��ġ�ϴ� ���������� �ٷ� ȸ���������� ����
int Sub_Menu();//����޴�
int Town(int a);//����
void Market();//����
void Dungeon(int a);//����

char ID[11];
ct *Name;//ĳ���� ����ü �ּ� ����
ct **list = NULL;//���δٸ������� ĳ���͸� ���������
int index = 0;

void main() {
	FILE *chf;
	int i;
	list = (ct**)malloc(sizeof(ct*));
	chf = fopen("c:/test/test/make_user.txt", "r");
	//�޴�����
	while (1) {
		switch (Menu()) {
		case 1:
			system("cls");
			Load();
			while (1) {
				switch (Sub_Menu()) {
				case 1://����
					system("cls");
					while (1) {
						switch (Town(0)) {
						case 1:
							//����
							break;
						case 2:
							//��������
							break;
						}
						system("cls");
						break;
					}
					break;
				case 2://����
					Dungeon(0);
					break;
				case 3://��������
					break;
				}
				system("cls");
				break;
			}
			break;
		case 2:
			//ȸ����ȣ�� �´� ĳ���������� ������ �����Ͱ�������
			break;
		case 3:
			//�ؽ�Ʈ�� ĳ���� ���� ����(�������� ����)
			break;
		case 4:
			//ȸ����ȣ�� �´� ĳ�������������� �ؽ�Ʈ���Ͽ��� 
			//������ ������ ��ΰ����ͼ� ��� �����Ͱ���������(�̰� �����ϸ� �������� ����)
			break;
		case 5:
			return;
		}
		system("cls");
	}
}
int Menu() {
	int num;
	//���� : �޴� �ٹ̱�
	printf("1. New Game\n");
	printf("2. Game Continue\n");
	printf("3. Game Save\n");
	printf("4. Game Load\n");
	printf("5. Exit\n");
	printf("���� : ");
	scanf("%d", &num);
	return num;
}
int Sub_Menu() {
	int num;
	printf("1. ����\n");
	printf("2. ����\n");
	printf("3. ��������\n");
	printf("���� : ");
	scanf("%d", &num);
	return num;
}
char* Login() {
	char tmp_id[11], tmp_pw[15];
	printf("���̵� : ");
	gets_s(tmp_id);
	printf("��й�ȣ : ");
	gets_s(tmp_pw);
	Id_Load(tmp_id, tmp_pw);
	//���̵�,��й�ȣ üũ �� �α����ϱ�
	//�α����� ĳ���ͺҷ�����(�����Ҵ�)
	//ĳ���� ������ �׳� �α����ϱ�
	return tmp_id;
}
void Id_Load(char *tmp_id, char *tmp_pw) {
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
void User_Make(int b/*ȸ����ȣ*/) {
	//�ڵ������� ȸ����ȣ�� �����ͼ� �ε�����ȣ�� �ְ� ĳ���� ����
	FILE *chf;
	int job_num = 0, a = 1;
	list[b] = (ct*)malloc(sizeof(ct));
	printf("=====ĳ���� �����ϱ�=====\n");
	printf(" ĳ���͸� : ");
	scanf("%s", list[b]->name);
	printf("���� - 1.���� 2.���� 3.�ü� 4.������ :  ");
	scanf("%d", &job_num);
	list[b]->level = 1;
	list[b]->Money = 0;
	list[b]->num = b + 1;
	list[b]->exp = 0;
	while (a == 1) {
		if (job_num == 1) {
			strcpy(list[b]->job, "����");
			list[b]->str = 12;
			list[b]->dex = 7;
			list[b]->int_ = 5;
			list[b]->HP = list[b]->level * 100;
			list[b]->MP = 50;
			strcpy(list[b]->skill[0], "��ų1");
			a = 0;
		}
		else if (job_num == 2) {
			strcpy(list[b]->job, "����");
			list[b]->str = 6;
			list[b]->dex = 10;
			list[b]->int_ = 8;
			list[b]->HP = list[b]->level * 100;
			list[b]->MP = 50;
			strcpy(list[b]->skill[0], "��ų1");
			a = 0;
		}
		else if (job_num == 3) {
			strcpy(list[b]->job, "�ü�");
			list[b]->str = 7;
			list[b]->dex = 10;
			list[b]->int_ = 7;
			list[b]->HP = list[b]->level * 100;
			list[b]->MP = 50;
			strcpy(list[b]->skill[0], "��ų1");
			a = 0;
		}
		else if (job_num == 4) {
			strcpy(list[b]->job, "������");
			list[b]->str = 5;
			list[b]->dex = 7;
			list[b]->int_ = 12;
			list[b]->HP = list[b]->level * 100;
			list[b]->MP = 50;
			strcpy(list[b]->skill[0], "��ų1");
			a = 0;
		}
		else {
			printf("�߸��Է��߽��ϴ�.\n");
			a = 1;
		}
	}
	chf = fopen("c:/test/test/make_user.txt", "w+");
	if (chf != NULL) {
		fprintf(chf, "%s %s %d %d %d %d %d %d %d %d %s %d\n", list[b]->job, list[b]->name, list[b]->level, list[b]->str, list[b]->dex, list[b]->int_, list[b]->HP, list[b]->MP, list[b]->Money, list[b]->exp, list[b]->skill[0], list[b]->num);
		fclose(chf);
	}
	return;
}
void User_Mng(int a/*ȸ����ȣ*/) {
	//ĳ���� �������ͽ�â, �׽� ȭ��ǥ��
	//ȭ�鿡 ��ﶧ�� ȸ����ȣ�� �����ͼ� �ε����� �־ ĳ���� ���� ǥ��
	printf("========ĳ���� �������ͽ�========\n");
	printf("ĳ���͸� : %s\n", list[a]->name);
	printf("���� : %s\n", list[a]->job);
	printf("��� : %d\n", list[a]->Money);
	printf("���� : %d\n", list[a]->level);
	printf("����ġ : %d\n", list[a]->exp);
	printf("�� : %d\n", list[a]->str);
	printf("��ø : %d\n", list[a]->dex);
	printf("���� : %d\n", list[a]->int_);
	printf("ü�� : %d\n", list[a]->HP);
	printf("���� : %d\n", list[a]->MP);
}
int Town(int a) {
	//ü�¿�����θ����,�����̿�޴�
	FILE *chf;
	int num;
	chf = fopen("c:/test/test/make_user.txt", "w");
	list[a]->HP = list[a]->level * 100;
	list[a]->MP = 50;
	if (chf != NULL) {
		fprintf(chf, "%s %s %d %d %d %d %d %d %d %d %s %d\n", list[0]->job, list[0]->name, list[0]->level, list[0]->str, list[0]->dex, list[0]->int_, list[0]->HP, list[0]->MP, list[0]->Money, list[0]->exp, list[0]->skill[0], list[0]->num);
		fclose(chf);
	}
	User_Mng(a);
	printf("=================================\n");
	printf("ĳ������ HP,MP�� ������� ���ƿԽ��ϴ�.\n\n");
	printf("1. ����\n");
	printf("2. ��������\n");
	printf("���� : ");
	scanf("%s", &num);
	return num;
}
void Market() {
	//�����۱���&�Ǹű�ɱ���
	//(ex.���Ǹ� ���Ű���/switch������ 1.���Ǳ��� 2.�Ǹ�(�̰�ĳ�����Ǿ�����������ؼ��������Ǹ�)
	//ĳ������ �� ����

}
void Dungeon(int a) {
	//��������(�����ؽ�Ʈ���)
	//���� �����ϰ� �Ʒ��� ���� ����
	FILE *chf;
	printf("������ġ!!\n");
	list[0]->HP = list[0]->HP - 20;
	printf("ü���� %d(��)�� �پ����ϴ�.\n", list[0]->HP);
	system("pause");
	list[0]->Money = list[0]->Money + 100;
	printf("%d��带 ������ϴ�.\n", 100);
	system("pause");
	list[0]->exp = list[0]->exp + 10;
	printf("����ġ %d�� ������ϴ�.\n", 10);
	system("pause");
	if (list[0]->exp >= 100) {
		list[0]->level++;
		list[0]->str++;
		list[0]->dex++;
		list[0]->int_++;
	}
	chf = fopen("c:/test/test/make_user.txt", "w");
	if (chf != NULL) {
		fprintf(chf, "%s %s %d %d %d %d %d %d %d %d %s %d\n", list[0]->job, list[0]->name, list[0]->level, list[0]->str, list[0]->dex, list[0]->int_, list[0]->HP, list[0]->MP, list[0]->Money, list[0]->exp, list[0]->skill[0], list[0]->num);
		fclose(chf);
	}
}
void Load() {
	FILE *f;
	f = fopen("c:/test/test/make_user.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
			list[index] = (ct*)malloc(sizeof(ct));
			fscanf(f, "%s %s %d %d %d %d %d %d %d %d %s %d\n", list[index]->job, list[index]->name, &list[index]->level, &list[index]->str, &list[index]->dex, &list[index]->int_, &list[index]->HP, &list[index]->MP, &list[index]->Money, &list[index]->exp, list[index]->skill[0], &list[index]->num);
			index++;
		}
		fclose(f);
		return;
	}
	else {
		User_Make(0);
	}
}