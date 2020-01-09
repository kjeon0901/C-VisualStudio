#define _CRT_SECURE_NO_WARNINGS//scanf����ó��
#include<stdio.h>//����� ���� ��ó��
#include<stdlib.h>
#include<time.h>
#include<windows.h>
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

int Menu();//�α����ϸ� �ٷ� ��Ÿ���� ���Ӹ޴�
void Menu_1();
void Menu_2();
void Menu_3();
int Sub_Menu();//����޴�
void User_Make();//ĳ���ͻ���
void User_Mng();//ĳ���ͽ������ͽ����
void Save();//��������
void New_Game();//���ο����
void Game_Load();//�ؽ�Ʈ���Ͽ� ����� ���� �ҷ�����
void Load();//�α��������ҷ�����
int Town();//����
int Market();//����
void Recovery();//ȸ��
void Development();//����
void Sale();//�ȱ�
void Dungeon();//����
void choose();//�α���ȸ�����Ը޴�����
int Login();//�α��ξ��̵�,��й�ȣ�Է�ȭ��
int File_Load(char *tmp_id, char *tmp_pw);//ȸ�������ؽ�Ʈ���Ͽ� ��ġȮ��
void Entry();//ȸ������

ct *list = NULL;//�α���, ȸ������ �� ȸ�� ������ �ش��ϴ� ĳ��������
mem*list_id = NULL;//�α���, ȸ������ �� ȸ���� ȸ������
mon *list_mon = NULL;//��������
items **list_item[5];//����������
int index = 0, check = 0;//while������ �ݺ����� �������ö� ���
int item_index = 0;

void main() {
	FILE *chf, *Item;
	int i;
	chf = fopen("c:/test/test/make_user.txt", "r"); //ȸ������ ��������� ĳ���� ������ make_user ���Ͽ� ����ü�� �����. ������ �ϸ鼭 ������
	Item = fopen("c:/test/test/item.txt", "r");
	list = (ct*)malloc(sizeof(ct));//�α���, ȸ������ �� ȸ�� ������ �ش��ϴ� ĳ�������� �����Ҵ� ��������
	list_id = (mem*)malloc(sizeof(mem));//ȸ������ �����Ҵ� ��������
	list_mon = (mon*)malloc(sizeof(mon));//�������� �����Ҵ� ��������

	for (i = 0; i < 2; i++) {////////////////////////��������Ⱥ�
		list->item[i] = (items*)malloc(sizeof(items));//ĳ���Ͱ� ���� ���������� �����Ҵ� ��������
		fscanf(Item, "%d %s %d %d %d %d\n", &list->item[i]->item_num, list->item[i]->item_name, &list->item[i]->attack, &list->item[i]->def, &list->item[i]->item_money, &list->item[i]->item_kind);
	}
	fclose(Item);///////////////////������������Ⱥ�


	choose();
	Sleep(1000);
	if (index != -1) { //???index==1�� ��찡 ���� �ʾҳ�??
		printf("%s�� ȯ���մϴ�!\n\n", list_id->ID); //�α���, ȸ������ �� �Ǹ� �ٽ� �α��� â�� ���� �ʰ� �ڵ� �α��ε�
		Sleep(1000);
		system("cls");
		Load();//ȸ�������� �ش��ϴ� ĳ���� ���� �ҷ�����
		system("cls");
		Menu_1();
	}
	else
		return;
	return;
}
void choose() {// �α���, ȸ������, ���� �� �����ϴ� �Լ�.���⼭ index���� ��ȭ�� ����
	int num;
	while (1) {
		printf("1. �α��� \n2. ȸ������\n");
		printf("���� : ");
		scanf("%d", &num);
		switch (num) {
		case 1: //�α��� �����ϸ�
			if (Login()) { //�α����Լ����� �α��μ����ϸ� 1�޾ƿ��� Ʋ���� 0�޾ƿ�. 1�޾ƿö� �׻� return �ǰ�, 0�޾ƿö� �ڵ����� return �ȵ�. 
				return; //��������� �α��� ������ ��츸 main�Լ��� �Ѿ. entry���� 0
			}
			break;
		case 2: //ȸ������ �����ϸ� �� ���� ������ �ڵ� �α���, �ٷ� ���ӽ���
			Entry(); 
			return; //entry ���� ��� ����� ����
		default: //�´� �ƴϸ� �ٽ� �ٽ� 
			getchar();//???
			getchar();
			system("cls");
			choose();
			return;
		}
		system("cls");
	}
} 
int Login() {//�α����Ѵٰ� ���� ��� ����� �ͼ� ���ڿ� �Է¹���
	char tmp_id[15], tmp_pw[15];
	getchar();
	printf("���̵� : ");
	scanf("%s", tmp_id);
	getchar();
	printf("��й�ȣ : ");
	scanf("%s", tmp_pw);
	return File_Load(tmp_id, tmp_pw); //file_load�Լ��� ���� �Է��� id, pw������ �´��� Ȯ��, ������ 1�޾ƿ��� Ʋ���� 0�޾ƿ�. ���������� 1 �Ǵ� 0�� �ٽ� choose�Լ��� ����
}
int File_Load(char *tmp_id, char *tmp_pw) {//�Է��� tmp�� ���� ������ ���Ͽ� �ִ��� Ȯ��, ????????�ٽ��ѹ�Ȯ��
	FILE *f; //���� �б��������� ����
	int member_num = 1;
	char check_id[15] = { "" }, check_pw[15] = { "" };//
	list_id = (mem*)malloc(sizeof(mem));
	f = fopen("c:/test/test/entry.txt", "r");
	if (f != NULL) {//������ ������� �ʴٸ�, �ҷ��ͼ� �����Ҵ�� �迭�� �����ؾ� ��
		while (!feof(f)) { //���� ����������
			fscanf(f, "%d %s %s\n", &member_num, check_id, check_pw);//���Ͽ� �ִ� ���� ó������ ������ �ҷ����� ����
			if (!strcmp(check_id, tmp_id) && !strcmp(check_pw, tmp_pw)) { //id, pw ���� ���ڿ� ���ؼ� ���� �Է��� �Ͱ� ����� ������ ��ġ�ϴ� ���
				list_id->num = member_num; //�׶� �� �ٿ� ����Ǿ��ִ� ȸ�������� ȸ����ȣ�� ���� �����Ҵ��� ����ü�� ����
				strcpy(list_id->ID, tmp_id); //���ڿ����� �Լ� �Ἥ ���� �Է��� ���̵� �����Ҵ��� ����ü�� ����
				strcpy(list_id->PW, tmp_pw);//�Ȱ��� �Է��� ��й�ȣ�� �����Ҵ��� ����ü�� ����
				return 1; //��������� �����Ҵ��� ����ü list_id���� �α����� ����Ǵ� ȸ�������� ��� ����.
			}
			member_num++;//��ġ���� �ʴ´ٸ� ��� �����ٷ� �Ѿ�� �Ǵϱ� 
		}
		printf("ȸ�� ������ �����ϴ�\n");//���ϳ��������� ��ġ�ϴ� ���� ��ã���� 0�Ѱ���
		system("pause");
		return 0;
	}
	else {//������ ����ִٸ�, ȸ�������϶�� �ϱ�
		printf("��ϵ� ȸ���� �����ϴ�\n");
		printf("ȸ�������ϼ���\n");
		system("pause");
		return 0;
	}
}
void Entry() { //ȸ������ �������� ��
	FILE *f; 
	int index = 0;
	f = fopen("c:/test/test/entry.txt", "r"); //ȸ������ ����Ǵ� ���� �б� ���� ���
	if (f != NULL) { // f���Ͽ� ����� ȸ�� ������ �ִ� ��쿡��
		while (!feof(f)) { //���� ó������ ������ �д� ���ȿ� 
			fscanf(f, "%d %s %s\n", &list_id->num, list_id->ID, list_id->PW);//���Ϸκ��� ���� �����ͼ� main�Լ����� ���� �Ҵ��ص� list_id����ü�� ���
			index++; //�̹� ����Ǿ� �ִ� ȸ������ �� ���� ������ ���� ȸ����ȣ�� index�� ���ϱ�
		}
	}
	else { // f������ ����ִ°�쿣 fscanf�� fprintf�� �ƹ��͵� ���� ����
		index = 0; //���� ������ �� ȸ����ȣ 1���� ������ �� �ֵ��� index=0�̶�� �α�
	}
	getchar();
	f = fopen("c:/test/test/entry.txt", "a"); //���Ͽ� �̾ �����Ҽ��ִ� a���� ���� ����
	list_id->num = index + 1;//���� �����ϴ� ȸ�������� ȸ����ȣ�� index+1�̶�� �α�
	printf("ID: ");
	scanf("%s", list_id->ID);//id�Է�
	printf("PW: ");
	scanf("%s", list_id->PW);//pw�Է�
	fprintf(f, "%d %s %s\n", list_id->num, list_id->ID, list_id->PW);//���Ͽ� ȸ����ȣ, id, pw �����ϱ�
	
	fclose(f);//���ϴݱ�
	system("pause");
	return;
}
int Menu() {
	int num;
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
		switch (Menu()) {//������, �̾��ϱ�, ĳ���� ���̺�, ĳ���� �ҷ�����
		case 1://������
			New_Game();//y������ ��츸 ����� �ٽ� ��(�ƴ� ���� menu_1�Լ� �ٽ� ����)
			User_Make();//�׸��� ȸ����ȣ�� �ش��ϴ� ���ο� ĳ���� ����
			system("cls");
			Menu_2();//���� �̵����� ���ϴ� �Լ�
			break;
		case 2://ȸ����ȣ�� �ش��ϴ� ĳ���� ���� �����ͼ� ���� �̾��ϱ�
			Menu_2();//���� �̵����� ���ϴ� �Լ�
			break;
		case 3://���Ͽ� ĳ���� ����(���� ���� ��ȭ�Ǵϱ�) ����
			Save();//�����ϴ� �Լ�
			break;
		case 4://ȸ����ȣ�� �ش��ϴ� ĳ�������� �ؽ�Ʈ���Ͽ��� �ҷ�����
			Game_Load();//ȸ�������� save�� ĳ�������� �ҷ��ͼ� �̾��ϱ�
			Menu_2();//���� �̵����� ���ϴ� �Լ�
			break;
		case 5://��������
			return;
		default:
			break;
		}
		system("cls");
	}
}
void Menu_2() {//���� �̵����� ���ϴ� �Լ�
	system("cls");
	while (1) {
		switch (Sub_Menu()) {//�������� �������� ����
		case 1://����
			system("cls");
			while (1) {
				switch (Town()) {//������ ������ �������� �Ȱ��� ����
				case 1:
					//����
					system("cls");
					Menu_3();//�������� ������ ����
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
			if (list->HP > 0) {//ü���� ���� ��
				Dungeon();//���� �������� ���� ���Ϳ� �ο�
			}
			else {//ü���� ���� ��
				list->HP = 0;//ü���� ������ �Ǿ��� 0�� �Ǿ��� ��� 0���� �α�
				Menu_2();//�ٽ� menu_2�Լ� �������� ���ư��� ���� ���� ���ϱ�(ü���� ���� �� �������� �� ��)
				return;
			}
			break;
		case 3://��������
			return;//�׳� ���ư��� ��
		}
		system("cls");
	}
}
void Menu_3() {//������ ������
	while (1) {
		switch (Market()) {//�������� ������ ����
		case 1:
			Recovery();//ȸ���ϱ�
			break;
		case 2:
			Development();//�����ϱ�
			break;
		case 3:
			Sale();//�Ǹ��ϱ�
			break;
		case 4:
			return;
		}
		break;
	}
}
int Sub_Menu() {//�������� �������� ����
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
	printf("������ ������ ���� �������ϴ�....y/n\n");//���� ��������� Ȯ���ϴ� �κ�
	getchar();
	printf("�Է� : ");
	scanf("%c", &yn);
	if (yn == 'y') {//y������ new���� �����ϸ鼭 ���� ĳ���Ͱ� �ִٸ� ����� ĳ���� �������� �ٽ� ����.
		while (!feof(chf)) {
			fscanf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp);
			if (list_id->num == list->num) {
				list->num = 0;//ȸ����ȣ�� 0���� �����Ǵ� ���� ���� ������ ĳ���� ��ȣ�� 0���� �дٴ� ���� ���̻� �� �� ���Բ� ������شٴ� ��.
				fprintf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", list->num, list->job, list->name, list->level, list->str, list->dex, list->int_, list->HP, list->MP, list->Money, list->exp);
				break;//�׷��� ���Ͽ� ������� �ϸ� ���̻� ���� �������Ե�. ���� ��������
			}
		}
		fclose(chf);
		return;//���ϵǰ� ���� ĳ���� ���鷯 ��
	}
	else if (yn == 'n') {//n������ new���ӽ����ϴ� �� �ݴ��Ѵٴ� ���̹Ƿ� �ٽ� menu_1�Լ� ����.
		Menu_1();
		return;
	}
	else {//yn �Ѵ� �ȴ����� �ٸ��� �����ٸ� �߸��������̹Ƿ� �ٽ� menu_1�Լ� ����
		Menu_1();
		return;
	}
}
void Game_Load() {//���Ͽ� ����� ����ĳ���� �ҷ����� �Լ�
	FILE *chf; //ĳ���� ���� ����Ǿ��ִ� ���� �б� �������� ����
	chf = fopen("c:/test/test/make_user.txt", "r");
	if (chf != NULL) {//���Ͽ� �ϳ��� ������ ����ִٸ�//?????????????????????������ ���� ���¶��? �׷� ���°� �ɼ�����?
		while (!feof(chf)) {//ó������ ������ �Ⱦ�鼭
			fscanf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp);//�������� list��� �����Ҵ�� ������ ���پ� ����ִٰ�
			if (list_id->num == list->num) {//ȸ����ȣ�� ���� ĳ���͹�ȣ�� ã����
				break;//�� ĳ���͸� list�� ���� ä�� �ݺ��� ��������
			}
		}
		fclose(chf);
	}
	printf("ĳ���� ������ �����Խ��ϴ�.\n");
	system("pause");
	return;
}
void User_Make() { //ȸ����ȣ(list_id�� ����Ǿ� ����)�� �����ͼ� �ε�����ȣ�� �ְ� ĳ���� ����
	FILE *chf;//ĳ���� ������ ����Ǵ� ������ a���� ����. (����: ������ ���� ��� ������ �ϰ�, �ִ� ��쿣 ������ �̾ �����ؾ� �ϹǷ�)
	int job_num = 0, a = 1;
	chf = fopen("c:/test/test/make_user.txt", "a");
	printf("=====ĳ���� �����ϱ�=====\n");//ĳ���� �����Ϸ��� �����Ҵ��Ų ����ü ������ ���� ����
	printf(" ĳ���͸� : ");
	scanf("%s", list->name);
	printf("���� - 1.���� 2.���� 3.�ü� 4.������ :  ");
	scanf("%d", &job_num);
	list->level = 1;//�ű� ĳ���Ͱ� ���� ������ ������ 1�� �ʱ�ȭ
	list->Money = 0;//�� 0���� �ʱ�ȭ
	list->num = list_id->num;//ĳ���� ��ȣ�� ȸ����ȣ�� ��ġ��Ű��
	list->exp = 0;//����ġ 0���� �ʱ�ȭ
	list->str = 10;//�� 0���� �ʱ�ȭ
	list->dex = 10;//��ø 0���� �ʱ�ȭ
	list->int_ = 10;//���� 0���� �ʱ�ȭ
	list->HP = list->level * 100;//ü���� 100���� �ʱ�ȭ
	list->MP = 50;//���� 0���� �ʱ�ȭ
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
	if (chf != NULL) {//ĳ���������� ����Ǿ��ִ� ���Ͽ��� ���� ������ ������ �������. ???????????�׷��� ���� if�� �Ƚᵵ ���� �ʳ�? if���� ���� ���Ҷ��� �ֳ�?
		fprintf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", list->num, list->job, list->name, list->level, list->str, list->dex, list->int_, list->HP, list->MP, list->Money, list->exp);//list����ü������ ĳ���� ������ ��� �־����ϱ� �̰� ���� ���Ͽ� ����. 
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
int Market() {//�������� ������ ����
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
void Recovery() {//ȸ���ϱ� �Լ�
	FILE *chf;//ĳ���� ���� ����Ǿ� �ִ� ���� ���� ���� ���(���� �����ؾ��ϴϱ�)
	chf = fopen("c:/test/test/make_user.txt", "w");
	if (chf != NULL) {//���Ͽ� ������ ���� ���
		while (!feof(chf)) {//ó������ ������ �Ⱦ�鼭
			fscanf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp);//ĳ���������� list �� ����
			if (list_id->num == list->num) {//�׷��ٰ� ȸ����ȣ�� ���� ĳ���� ��ȣ�� ������ (�ڽ��� ĳ���͸� ã�Ƴ��� ���) ü��, ����, �� �����ϱ�
				if (list->Money < 100) {//ȸ���ϱ⸦ �����Ϸ��� �� 100���� ���� �ϴµ�, ���� ������ �ִ� ���� 100������ ���ٸ�
					printf("������尡 �����մϴ�.\n");
					system("pause");
					Menu_3();//�ڵ�����  menu_3, �� �������� ���ư�
					return;
				}
				list->HP = list->level * 100+ list->item[1]->def;//ü�� �ְ�ġ�� �÷�����
				list->MP = 50;//���� �ְ�ġ�� �÷�����
				list->Money -= 100;//������ 100�� ����
				break;
			}
		}
		fclose(chf);//????????????�׷� fprintf�� �ʿ����? ������ص� ���ϵ� ������?
	}
	Sleep(1000);
	printf("ĳ���Ͱ� ��� ȸ���Ǿ����ϴ�.\n");
	system("pause");
	Menu_3();//ȸ���ϱⰡ ����Ǿ��� �� ���� ���� �� �ٽ� menu_3, �� �������� ���ư���
}
void Development() {//�����ϱ� �Լ�
	FILE *chf;//ĳ���� ������ ��� make_user������ ���� ���� ����(���� �����ؾ� �ϴϱ�)
	chf = fopen("c:/test/test/make_user.txt", "w");
	if (chf != NULL) {//���Ͽ� ������ ����ִٸ�
		while (!feof(chf)) {//ó������ ������ �����鼭
			fscanf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp);//�ϴ� ���پ� ĳ���������� �ҷ��ͼ� list�� ��Ƶα�
			if (list_id->num == list->num) {//�׷��ٰ� ȸ����ȣ�� ���� ĳ���͹�ȣ�� ���� ĳ���͸� ������ ȸ���ϱ� ����
				if (list->Money < 300) {//ȸ���ϱ⸦ ���ؼ� �� 300�� �ʿ��ѵ� ���� ������ �ִ� ���� 300���� ������
					printf("������尡 �����մϴ�.\n");
					system("pause");
					Menu_3();//�ƹ��͵� ó������ �ʰ� �ڵ����� menu_3, �� �������� �ٽ� ���ư�
					return;
				}
				list->str += 2;//���� ����ϸ� 
				list->dex += 2;
				list->int_ += 2;
				list->Money -= 300;
				break;
			}
		}
		fclose(chf);//????????????�׷� fprintf�� �ʿ����? ������ص� ���ϵ� ������?
	}
	Sleep(1000);
	printf("ĳ���Ͱ� �ҷ� ����Ǿ����ϴ�.\n");
	system("pause");
	Menu_3();//�����ϱ� ������ �ڵ����� menu_3, �� �������� ���ư�
}
void Sale() {//���� ������ �������� �Ĵ� �Լ�
	FILE *File;//�������� ����� ������ ���� ���� ���
	int i = 0, num=0;
	File = fopen("c:/test/test/item.txt", "r");
	printf("[���� ������ ������]\n");
	for (i = 0; i < 2; i++) {//������ 2���� ���� ���
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
	num -= 1;//�����Ѱ� �����۹�ȣ�̰�, �ε��� ��ȣ�� �����۹�ȣ���� 1 �����ϱ� 1 ����
	list->Money += list->item[num]->item_money;
	list->item[num]->item_money = 0;
	list->str -= list->item[num]->attack;
	list->def -= list->item[num]->def;
	printf("���� ��� : %d��\n", list->Money);

	fprintf(File, "%d %s %d\n", list->item[num]->item_num, list->item[num]->item_name, list->item[num]->item_money);//���������� ����Ǵ� ���Ͽ��� �� ������ ������ �ٲ���
	fclose(File);

	FILE *chf;//ĳ���� ������ ���� ���� ����
	chf = fopen("c:/test/test/make_user.txt", "w");
	if (chf != NULL) {//������ ������� ���� ���(� ĳ���Ͷ� ����Ǿ� �ִ� ���)
		while (!feof(chf)) {//������ ó������ ������ �����鼭
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
	int i = 0, k = 0, j = 0;

	File = fopen("c:/test/test/monster.txt", "r");//�����ؽ�Ʈ���� �б���� ����...???????
	Item = fopen("c:/test/test/item.txt", "r");//�������ؽ�Ʈ���� �б���� ����

	for (i = 0; i < 2; i++) {
		list->item[i] = (items*)malloc(sizeof(items));//ĳ���Ͱ� ���� ���������� �����Ҵ� ��������
		fscanf(Item, "%d %s %d %d %d %d\n", &list->item[i]->item_num, list->item[i]->item_name, &list->item[i]->attack, &list->item[i]->def, &list->item[i]->item_money, &list->item[i]->item_kind);
	}

	srand((int)time(NULL));
	k = rand() % 2;//������ ó���� �������� �������� ���ϱ�
	list_mon = (mon*)malloc(sizeof(mon));//���� �����Ҵ�
	fscanf(File, "%s %d %d %d %d %d\n", list_mon->mon_name, &list_mon->mon_level, &list_mon->mon_HP, &list_mon->mon_attack, &list_mon->mon_money, &list_mon->mon_exp);
	fclose(File);//���Ͽ��� ������ list_mon�� ��Ƶα�(���ʹ� �ϳ��� �������)
	printf("����������.....\n");
	Sleep(1000);
	printf("����%d�� %s(��)�� �����߽��ϴ�!!!\n", list->level, list_mon->mon_name);
	system("pause");
	system("cls");
	list_mon->mon_level = list->level;//ĳ������ ������ �ö󰡸� ���� ������ �Ȱ��� �ö󰡵���
	list_mon->mon_HP = list_mon->mon_level * 50;//���� ü�� ���ϱ�
	list_mon->mon_attack = list_mon->mon_level * 10;//���� ���ݷ� ���ϱ�
	list_mon->mon_money = list_mon->mon_money*list_mon->mon_level;//���� �̱�� �޴� �� ���ϱ�
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
		if (list_mon->mon_HP <= 0) {//��� �ݺ��ϴٰ� ���� HP�� 0���� �۾����� ���, ����ġ, ������ ȹ��
			printf("%s�� ��ġ�Ͽ����ϴ�.\n", list_mon->mon_name);
			system("pause");
			printf("%d��� ȹ��, %d����ġȹ��\n", list_mon->mon_money, list_mon->mon_exp);
			printf("������ %s ȹ��\n", list->item[k]->item_name);//Item_index�� k�� ��� �ٲ�

			list->str = list->str + list->item[k]->attack; //�������� ������ϱ� ĳ������ ���� ������ ���ݷ¸�ŭ ����
			list->HP = list->HP + list->item[k]->def; //�������� ������ϱ� ĳ������ ü���� ������ ���¸�ŭ ����
			list->item[k]->item_kind = 1;//????????????
			fprintf(Item, "%d %s %d %d %d %d\n", list->item[k]->item_num, list->item[k]->item_name, list->item[k]->attack, list->item[k]->def, list->item[k]->item_money, list->item[k]->item_kind);
			printf("���� %d����, �ִ� HP %d����\n", list->item[k]->attack, list->item[k]->def);
			list->Money = list->Money + list_mon->mon_money;//ĳ���� �Ӵ� ����
			list->exp = list->exp + list_mon->mon_exp;//ĳ���� ����ġ ����
			//k++;
			//if (k == 2) {//�������� 
			//	k = 0;
			//}
			system("pause");
			if (list->exp >= 100) { //����ġ ��� �����ϴٰ� 100 ������ ���� 1 ������ ����ġ�� �ٽ� 0���� �ʱ�ȭ
				list->level++;
				list->str += 5;
				list->dex += 5;
				list->int_ += 5;
				list->exp = 0;
				list->HP = list->level * 100;
				printf("������ %d(��)�� ���߽��ϴ�.\n", list->level);
				system("pause");
			}
			fclose(Item);
			system("cls");
			return;
			Menu_2();//���Ͷ� �ο��� �̱�� �ٽ� ���ΰ��� ���ϵ���
		}
		system("pause");//mon->HP�� 0���� ū ��쿡�� ��� �÷��̾� HP, ���� HP �� ���� �پ��鼭  �ݺ��ǵ���
		printf("%s�� ����!!\n", list_mon->mon_name);
		list->HP = list->HP - list_mon->mon_attack;
		printf("�÷��̾��� ü���� %d(��)�� �پ����ϴ�.\n", list->HP);
		if (list->HP <= 0) {
			printf("�÷��̾ ����߽��ϴ�.\n");//���߿� �÷��̾�HP�� �� ������ ����ؼ� ������ ������
			printf("������ �̵��մϴ�.\n");
			fclose(Item);//
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
	f = fopen("c:/test/test/make_user.txt", "r"); //ȸ������ ĳ���� ������ �����صδ� ������ �б� �������� ����
	if (f != NULL) {//���Ͽ� ������ ����ִ� ���
		while (!feof(f)) {//������ ó������ ������ �����鼭
			fscanf(f, "%d %s %s %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp);//���� �����Ҵ��ص� ���� list �� ��� �־�ٰ�
			if (list_id->num == list->num) {//�Ʊ� �α���, ȸ�������� ���� ã�Ƴ� ȸ����ȣ�� ���� ĳ���� ��ȣ�� ã�Ƴ���(user_make�Լ����� ĳ���������� �����Ҷ� ���ʿ� ȸ�������� ĳ���͹�ȣ�� ���� ����)
				fprintf(f, "%d %s %s %d %d %d %d %d %d %d %d\n", list->num, list->job, list->name, list->level, list->str, list->dex, list->int_, list->HP, list->MP, list->Money, list->exp);//�� �ٿ� �ִ� ĳ���������� ��� list�� ������. 
				return;
			}
		}
		printf("ĳ���������� �����ϴ�.\n");//���� ������ ���� �Ʊ� �α���, ȸ�������� ���� ã�Ƴ� ȸ����ȣ�� ���� ĳ���� ��ȣ�� ã�� ���Ѵٸ�
		printf("ĳ���ͻ������� �̵���.....\n");
		Sleep(1000);
		User_Make();//ĳ���� �����ϴ� �Լ��� ����
		fclose(f);
	}
	else {//���Ͽ� ������ ���� �ƹ��͵� ���� ���
		printf("ĳ���������� �����ϴ�.\n");
		printf("ĳ���ͻ������� �̵���.....\n");
		Sleep(1000);
		User_Make();//ĳ���� �����ϴ� �Լ��� ����
	}
}
void Save() {
	FILE *chf;//ĳ�������� �����ϴ� ���� ������� ��� ����
	chf = fopen("c:/test/test/make_user.txt", "w");
	if (chf != NULL) {
		while (!feof(chf)) {
			fscanf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", &list->num, list->job, list->name, &list->level, &list->str, &list->dex, &list->int_, &list->HP, &list->MP, &list->Money, &list->exp);
			if (list_id->num == list->num) {
				fprintf(chf, "%d %s %s %d %d %d %d %d %d %d %d\n", list->num, list->job, list->name, list->level, list->str, list->dex, list->int_, list->HP, list->MP, list->Money, list->exp);
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