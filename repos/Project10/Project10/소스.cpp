#define _CRT_SECURE_NO_WARNINGS//scanf����ó��
#include<stdio.h>//����� ���� ��ó��
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<string.h>//���ڿ����� �Լ��� �������
/*
�ؽ�Ʈ rpg game
1.ĳ���� �����
2.���� ����
3.������(����,��,����)
sleep�Լ�����
*/
typedef struct member { //ȸ������ ����ü ����
	int num;//ȸ����ȣ
	char ID[20];
	char PW[20];
}mem;
typedef struct items {
	int item_num;//�����۹�ȣ
	char item_name[30];//�������̸�
	int item_kind;//���������
	int attack;//���ݷ�
	int def;//����
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
	int def;// ����
	int Money;//���
	int count;
	char skill[10][50];//��ų
	struct items *item[100];//������,
}ct;
typedef struct monster {
	char mon_name[20];
	int mon_level;
	int mon_attack;
	int mon_HP;
	int mon_money;
	int mon_exp;
	struct items *mon_item[5];
}mon;

int Menu();//���Ӹ޴�
void Menu_1();//���Ӹ޴�
void Menu_2();//���Ӹ޴�
void Menu_3();//���Ӹ޴�
int Sub_Menu();//����޴�
void User_Make();//ĳ���ͻ���
void User_Mng();//ĳ���ͽ����������
void Save();//��������
void New_Game();//���ο����
void Game_Load();//�ؽ�Ʈ���Ͽ� ����� ���� �ҷ�����
void Load();//�α��������ҷ�����
int Town();//����
int Market();//����
void Recovery();//ȸ��
void Development();//����
void Sale();
void Dungeon();//����
void choose();//�α���ȸ�����Ը޴�����
int Login();//�α��ξ��̵�,��й�ȣ�Է�ȭ��
int File_Load(char *tmp_id, char *tmp_pw);//ȸ�������ؽ�Ʈ���Ͽ� ��ġȮ��
void Entry();//ȸ������


ct *list = NULL;//ĳ��������
mem*list_id = NULL;//ȸ������
mon *list_mon = NULL;//��������
items **list_item[5];//����������
int index = 0, check = 0;//while������ �ݺ����� �������ö� ���
int item_index = 0;

void main() {
	FILE *chf, *Item;
	int i;
	chf = fopen("c:/test/test/make_user.txt", "r");
	Item = fopen("c:/test/test/item.txt", "r");
	list = (ct*)malloc(sizeof(ct));//ĳ�������� �����Ҵ� ��������
	list_id = (mem*)malloc(sizeof(mem));//ȸ������ �����Ҵ� ��������
	list_mon = (mon*)malloc(sizeof(mon));//�������� �����Ҵ� ��������
	for (i = 0; i < 2; i++) {
		list->item[i] = (items*)malloc(sizeof(items));//ĳ���Ͱ� ���� ���������� �����Ҵ� ��������
		fscanf(Item, "%d %s %d %d %d %d\n", &list->item[i]->item_num, list->item[i]->item_name, &list->item[i]->attack, &list->item[i]->def, &list->item[i]->item_money, &list->item[i]->item_kind);
	}
	fclose(Item);

	choose();
	Sleep(1000);
	if (index != -1) {
		printf("%s�� ȯ���մϴ�!\n\n", list_id->ID);
		Sleep(1000);
		system("cls");
		Load();
		system("cls");
		Menu_1();
	}
	else
		return;
	return;
}
void choose() {// index��ȣ �Ѱ���
	int num;
	while (1) {
		printf("1. �α��� \n2. ȸ������\n");
		printf("���� : ");
		scanf("%d", &num);
		switch (num) {
		case 1:
			if (Login()) {
				return;
			}
			break;
		case 2:
			Entry();
			return;
		default:
			getchar();
			getchar();
			system("cls");
			choose();
			return;
		}
		system("cls");
	}
}
int Login() {
	char tmp_id[15], tmp_pw[15];
	getchar();
	printf("���̵� : ");
	scanf("%s", tmp_id);
	getchar();
	printf("��й�ȣ : ");
	scanf("%s", tmp_pw);
	return File_Load(tmp_id, tmp_pw);
}
int File_Load(char *tmp_id, char *tmp_pw) {//�Է��� tmp�� ���� ������ ���Ͽ� �ִ��� Ȯ��
	FILE *f; //���� �б��������� ����
	int member_num = 1;
	char check_id[15] = { "" }, check_pw[15] = { "" };
	list_id = (mem*)malloc(sizeof(mem));
	f = fopen("c:/test/test/entry.txt", "r");
	if (f != NULL) {//������ ������� �ʴٸ�, �ҷ��ͼ� �����Ҵ�� �迭�� �����ؾ� ��
		while (!feof(f)) { //���� ����������
			fscanf(f, "%d %s %s\n", &member_num, check_id, check_pw);
			if (!strcmp(check_id, tmp_id) && !strcmp(check_pw, tmp_pw)) {
				list_id->num = member_num;
				strcpy(list_id->ID, tmp_id);
				strcpy(list_id->PW, tmp_pw);
				return 1;
			}
			member_num++;
		}
		printf("ȸ�� ������ �����ϴ�.\n");
		system("pause");
		return 0;
	}
	else {//������ ����ִٸ�, ȸ�������϶�� �ϱ�
		printf("��ϵ� ȸ���� �����ϴ�.\n");
		printf("ȸ�������ϼ���.\n");
		system("pause");
		return 0;
	}
}
void Entry() {
	FILE *f;
	int index = 0;
	f = fopen("c:/test/test/entry.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
			fscanf(f, "%d %s %s\n", &list_id->num, list_id->ID, list_id->PW);
			index++;
		}
	}
	else {
		index = 0;
	}
	getchar();
	f = fopen("c:/test/test/entry.txt", "a");
	list_id->num = index + 1;
	printf("ID: ");
	scanf("%s", list_id->ID);
	printf("PW: ");
	scanf("%s", list_id->PW);
	fprintf(f, "%d %s %s\n", list_id->num, list_id->ID, list_id->PW);
	fclose(f);
	system("pause");
	return;
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
void Menu_1() {
	while (1) {
		switch (Menu()) {
		case 1:
			New_Game();
			User_Make();
			system("cls");
			Menu_2();
			break;
		case 2:
			//ȸ����ȣ�� �´� ĳ�������� ��������
			//Continue();
			Menu_2();
			break;
		case 3:
			//�ؽ�Ʈ�� ĳ���� ���� ����
			Save();
			break;
		case 4:
			//ȸ����ȣ�� �´� ĳ�������������� �ؽ�Ʈ���Ͽ���
			Game_Load();
			Menu_2();
			break;
		case 5:
			return;
		default:
			break;
		}
		system("cls");
	}
}
void Menu_2() {
	system("cls");
	while (1) {
		switch (Sub_Menu()) {
		case 1://����
			system("cls");
			while (1) {
				switch (Town()) {
				case 1:
					//����
					system("cls");
					Menu_3();
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
			system("cls");
			if (list->HP > 0) {
				Dungeon();
			}
			else {
				list->HP = 0;
				Menu_2();
				return;
			}
			break;
		case 3://��������
			return;
		}
		system("cls");
	}
}
void Menu_3() {
	while (1) {
		switch (Market()) {
		case 1:
			Recovery();//ȸ���ϱ�
			break;
		case 2:
			Development();//�����ϱ�
			break;
		case 3://�Ǹ�
			Sale();
			break;
		case 4:
			return;
		}
		break;
	}
}
int Sub_Menu() {
	int num;
	User_Mng();
	printf("=================================\n");
	printf("\n");
	printf("1. ����\n");
	printf("2. ����\n");
	printf("3. ��������\n");
	printf("���� : ");
	scanf("%d", &num);
	return num;
}
void New_Game() {
	char yn;
	FILE *chf;
	chf = fopen("c:/test/test/make_user.txt", "w");
	printf("������ ������ ���� �������ϴ�....y/n\n");
	getchar();
	printf("�Է� : ");
	scanf("%c", &yn);
	if (yn == 'y') {
		while (!feof(chf)) {
			fscanf(chf, "%d %s %s %d %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp, &list->count);
			if (list_id->num == list->num) {
				list->num = 0;
				fprintf(chf, "%d %s %s %d %d %d %d %d %d %d %d %d\n", list->num, list->job, list->name, list->level, list->str, list->dex, list->int_, list->HP, list->MP, list->Money, list->exp, list->count);
				break;
			}
		}
		fclose(chf);
		return;
	}
	else if (yn == 'n') {
		Menu_1();
		return;
	}
	else {
		Menu_1();
		return;
	}
}
void Game_Load() {
	FILE *chf;
	chf = fopen("c:/test/test/make_user.txt", "r");
	if (chf != NULL) {
		while (!feof(chf)) {
			fscanf(chf, "%d %s %s %d %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp, &list->count);
			if (list_id->num == list->num) {
				break;
			}
		}
		fclose(chf);
	}
	printf("ĳ���� ������ �����Խ��ϴ�.\n");
	system("pause");
	return;
}
void User_Make() {
	//�ڵ������� ȸ����ȣ�� �����ͼ� �ε�����ȣ�� �ְ� ĳ���� ����
	FILE *chf;
	int job_num = 0, a = 1;
	chf = fopen("c:/test/test/make_user.txt", "a");
	printf("=====ĳ���� �����ϱ�=====\n");
	printf(" ĳ���͸� : ");
	scanf("%s", list->name);
	printf("���� - 1.���� 2.���� 3.�ü� 4.������ : ");
	scanf("%d", &job_num);
	list->level = 1;
	list->Money = 0;
	list->num = list_id->num;
	list->exp = 0;
	list->str = 10;
	list->dex = 10;
	list->int_ = 10;
	list->HP = list->level * 100;
	list->MP = 50;
	list->count = 0;
	while (a) {
		switch (job_num) {
		case 1:
			strcpy(list->job, "����");
			a = 0;
			break;
		case 2:
			strcpy(list->job, "����");
			a = 0;
			break;
		case 3:
			strcpy(list->job, "�ü�");
			a = 0;
			break;
		case 4:
			strcpy(list->job, "������");
			a = 0;
			break;
		default:
			printf("�߸��Է��߽��ϴ�.\n");
			printf("ó������ �ٽ� �������ּ���...\n");
			system("pause");
			getchar();
			getchar();
			system("cls");
			main();
			return;
		}
	}
	system("cls");
	printf("ĳ���� ������.....\n");
	Sleep(1000);
	if (chf != NULL) {
		fprintf(chf, "%d %s %s %d %d %d %d %d %d %d %d %d\n", list->num, list->job, list->name, list->level, list->str, list->dex, list->int_, list->HP, list->MP, list->Money, list->exp, list->count);
		fclose(chf);
	}
	return;
}
void User_Mng() {
	//ĳ���� �������ͽ�â, �׽� ȭ��ǥ��
	//ȭ�鿡 ��ﶧ�� ȸ����ȣ�� �����ͼ� �ε����� �־ ĳ���� ���� ǥ��
	printf("========ĳ���� �������ͽ�========\n");
	printf("ĳ���͸� : %s\n", list->name);
	printf("���� : %s\n", list->job);
	printf("��� : %d\n", list->Money);
	printf("���� : %d\n", list->level);
	printf("����ġ : %d\n", list->exp);
	printf("�� : %d\n", list->str);
	printf("��ø : %d\n", list->dex);
	printf("���� : %d\n", list->int_);
	printf("ü�� : %d\n", list->HP);
	printf("���� : %d\n", list->MP);
}
int Town() {
	//�����̿�޴�
	int num;
	User_Mng();
	printf("=================================\n");
	printf("\n");
	printf("1. ����\n");
	printf("2. ��������\n");
	printf("���� : ");
	scanf("%d", &num);
	return num;
}
int Market() {
	//�����۱���&�Ǹű�ɱ���
	//(ex.���Ǹ� ���Ű���/switch������ 1.���Ǳ��� 2.�Ǹ�(�̰�ĳ�����Ǿ�����������ؼ��������Ǹ�)
	//ĳ������ �� ����
	int num;
	User_Mng();
	printf("=================================\n");
	printf("\n");
	printf("==========����==========\n\n");
	printf("1. ȸ���ϱ�(-100���)\n");
	printf("2. �����ϱ�(-300���)\n");
	printf("3. �������Ǹ�\n");
	printf("4. ��������\n");
	printf("���� : ");
	scanf("%d", &num);
	return num;
}
void Recovery() {
	FILE *chf;
	chf = fopen("c:/test/test/make_user.txt", "w");
	if (chf != NULL) {
		while (!feof(chf)) {
			fscanf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp);
			if (list_id->num == list->num) {
				if (list->Money < 100) {
					printf("������尡 �����մϴ�.\n");
					system("pause");
					Menu_3();
					return;
				}
				list->HP = list->level * 100 + list->item[1]->def;
				list->MP = 50;
				list->Money -= 100;
				break;
			}
		}
		fclose(chf);
	}
	Sleep(1000);
	printf("ĳ���Ͱ� ��� ȸ���Ǿ����ϴ�.\n");
	system("pause");
	Menu_3();
}
void Development() {
	FILE *chf;
	chf = fopen("c:/test/test/make_user.txt", "w");
	if (chf != NULL) {
		while (!feof(chf)) {
			fscanf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp);
			if (list_id->num == list->num) {
				if (list->Money < 300) {
					printf("������尡 �����մϴ�.\n");
					system("pause");
					Menu_3();
					return;
				}
				list->str += 2;
				list->dex += 2;
				list->int_ += 2;
				list->Money -= 300;
				break;
			}
		}
		fclose(chf);
	}
	Sleep(1000);
	printf("ĳ���Ͱ� �ҷ� ����Ǿ����ϴ�.\n");
	system("pause");
	Menu_3();
}
void Sale() {
	FILE *File;
	int i = 0, num = 0;
	File = fopen("c:/test/test/item.txt", "r");
	printf("[���� ������ ������]\n");
	for (i = 0; i < 2; i++) {
		printf("%d. %s %d\n", list->item[i]->item_num, list->item[i]->item_name, list->item[i]->item_money);
	}
	printf("3. ��������\n");
	printf("����: ");
	scanf("%d", &num);
	if (num == 3) {
		system("cls");
		Menu_3();
		return;
	}
	num -= 1;
	list->Money += list->item[num]->item_money;
	list->item[num]->item_money = 0;
	list->str -= list->item[num]->attack;
	list->def -= list->item[num]->def;
	printf("���� ��� : %d��\n", list->Money);

	fprintf(File, "%d %s %d\n", list->item[num]->item_num, list->item[num]->item_name, list->item[num]->item_money);//���������� ����Ǵ� ���Ͽ��� �� ������ ������ �ٲ���
	fclose(File);

	FILE *chf;
	chf = fopen("c:/test/test/make_user.txt", "w");
	if (chf != NULL) {
		while (!feof(chf)) {
			fscanf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp);//�� ĳ���� ������ list�� ��Ƶα�
			if (list_id->num == list->num) {//
				list->Money += list->item[num]->item_money;
				break;
			}
			i++;
		}
		fprintf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", list->num, list->job, list->name, list->level, list->str, list->dex, list->int_, list->HP, list->MP, list->Money, list->exp);
		fclose(chf);
	}
	fclose(chf);
	system("pause");
	system("cls");
	Menu_3();
	return;
}
void Dungeon() {
	//��������(�����ؽ�Ʈ���)
	//���� �����ϰ� �Ʒ��� ���� ����
	//�̸� ���� ü�� ���ݷ� ��� ����ġ
	FILE *File, *Item;
	int i = 0, k = 0;

	File = fopen("c:/test/test/monster.txt", "r");
	Item = fopen("c:/test/test/item.txt", "r");

	for (i = 0; i < 2; i++) {
		list->item[i] = (items*)malloc(sizeof(items));//ĳ���Ͱ� ���� ���������� �����Ҵ� ��������
		fscanf(Item, "%d %s %d %d %d %d\n", &list->item[i]->item_num, list->item[i]->item_name, &list->item[i]->attack, &list->item[i]->def, &list->item[i]->item_money, &list->item[i]->item_kind);
	}

	srand((int)time(NULL));
	k = rand() % 2;
	list_mon = (mon*)malloc(sizeof(mon));
	fscanf(File, "%s %d %d %d %d %d\n", list_mon->mon_name, &list_mon->mon_level, &list_mon->mon_HP, &list_mon->mon_attack, &list_mon->mon_money, &list_mon->mon_exp);
	fclose(File);
	printf("����������.....\n");
	Sleep(1000);
	printf("����%d�� %s(��)�� �����߽��ϴ�!!!\n", list->level, list_mon->mon_name);
	system("pause");
	system("cls");
	list_mon->mon_level = list->level;
	list_mon->mon_HP = list_mon->mon_level * 50;
	list_mon->mon_attack = list_mon->mon_level * 10;
	list_mon->mon_money = list_mon->mon_money*list_mon->mon_level;
	while (1) {
		User_Mng();
		printf("=================================\n");
		printf("\n");
		printf("=================================\n");
		printf("���� : %s\n", list_mon->mon_name);
		printf("���� : %d\n", list_mon->mon_level);
		printf("HP : %d\n", list_mon->mon_HP);
		printf("���ݷ� : %d\n", list_mon->mon_attack);
		printf("=================================\n");
		printf("�÷��̾��� ����!!\n");
		list_mon->mon_HP = list_mon->mon_HP - (list->str + list->dex + list->int_) / 3;
		printf("%s���� %d��ŭ�� �������� �������ϴ�.\n", list_mon->mon_name, (list->str + list->dex + list->int_) / 3);
		if (list_mon->mon_HP <= 0) {
			printf("%s�� ��ġ�Ͽ����ϴ�.\n", list_mon->mon_name);
			system("pause");
			printf("%d��� ȹ��, %d����ġȹ��\n", list_mon->mon_money, list_mon->mon_exp);

			printf("������ %s ȹ��\n", list->item[k]->item_name);
			list->str = list->str + list->item[k]->attack;
			list->HP = list->HP + list->item[k]->def;
			list->item[k]->item_kind = 1;
			fprintf(Item, "%d %s %d %d %d %d\n", list->item[k]->item_num, list->item[k]->item_name, list->item[k]->attack, list->item[k]->def, list->item[k]->item_money, list->item[k]->item_kind);
			printf("���� %d����, �ִ� HP %d����\n", list->item[k]->attack, list->item[k]->def);
			list->Money = list->Money + list_mon->mon_money;
			list->exp = list->exp + list_mon->mon_exp;
			//k++;
			//if (k == 2) {
			//	k = 0;
			//}
			system("pause");
			if (list->exp >= 100) {
				list->level++;
				list->str += 5;
				list->dex += 5;
				list->int_ += 5;
				list->exp = 0;
				list->HP = list->level * 100;
				printf("������ %d(��)�� ���߽��ϴ�.\n", list->level);
				system("pause");
			}
			system("cls");
			return;
			Menu_2();
		}
		system("pause");
		printf("%s�� ����!!\n", list_mon->mon_name);
		list->HP = list->HP - list_mon->mon_attack;
		printf("�÷��̾��� ü���� %d(��)�� �پ����ϴ�.\n", list->HP);
		if (list->HP <= 0) {
			printf("�÷��̾ ����߽��ϴ�.\n");
			printf("������ �̵��մϴ�.\n");
			system("pause");
			system("cls");
			return;
			Menu_3();
		}
		system("pause");
		system("cls");
	}
}
void Load() {
	FILE *f;
	f = fopen("c:/test/test/make_user.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
			fscanf(f, "%d %s %s %d %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp, &list->count);
			if (list_id->num == list->num) {
				fprintf(f, "%d %s %s %d %d %d %d %d %d %d %d %d\n", list->num, list->job, list->name, list->level, list->str, list->dex, list->int_, list->HP, list->MP, list->Money, list->exp, list->count);
				return;
			}
		}
		printf("ĳ���������� �����ϴ�.\n");
		printf("ĳ���ͻ������� �̵���.....\n");
		Sleep(1000);
		User_Make();
		fclose(f);
	}
	else {
		printf("ĳ���������� �����ϴ�.\n");
		printf("ĳ���ͻ������� �̵���.....\n");
		Sleep(1000);
		User_Make();
	}
}
void Save() {
	FILE *chf;
	chf = fopen("c:/test/test/make_user.txt", "w");
	if (chf != NULL) {
		while (!feof(chf)) {
			fscanf(chf, "%d %s %s %d %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp, &list->count);
			if (list_id->num == list->num) {
				fprintf(chf, "%d %s %s %d %d %d %d %d %d %d %d %d\n", list->num, list->job, list->name, list->level, list->str, list->dex, list->int_, list->HP, list->MP, list->Money, list->exp, list->count);
				break;
			}
		}
		fclose(chf);
	}
	printf("������........\n");
	Sleep(1000);
	printf("������ �Ϸ�Ǿ����ϴ�.\n");
	system("pause");
	system("cls");
	return;
}
