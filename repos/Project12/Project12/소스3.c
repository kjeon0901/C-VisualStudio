#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <windows.h> 
#include <time.h> 
#include <math.h> 
typedef struct member
{
	char ID[20];
	char PW[20];
	//��и޸� ��й�ȣ �߰� 
	struct mem*next;
}mem;
mem*head = NULL, *tail = NULL, *pass;

void Init();
void addMember(char *id, char *pw);
int Main_Menu();//�α���, ȸ������, ���� ���� 
int Login();//ID, PW �Է� 
int Login_Check(char*tmp_id, char*tmp_pw);//���� �о �Է��� ID, PW�� ��ġ�ϸ� pass�� ��� 
int Entry();//ȸ������, ���� ���̵� ������ �ڷΰ��� 


void Init()
{
	FILE*fc;
	char ID[20];
	char PW[20];
	fc = fopen("c:/test/diary/mem.txt", "r");
	head = (mem*)malloc(sizeof(mem));
	head->next = NULL;
	tail = head;
	if (fc != NULL)
	{
		while (!feof(fc))//���α׷� ���۽� ȸ�������� �о ����Ʈ�� ���� 
		{
			fscanf(fc, "%s %s\n", ID, PW);
			addMember(ID, PW);
		}
	}
}
void main()
{
	Init();
	//printMember();
	int num;
	num = Main_Menu();
	if (num == 0)
	{//���� �������� ���� 
		return;
	}
	printf("%s�� ȯ���մϴ�!\n\n", pass->ID);
}
int Main_Menu()
{
	while (1)
	{
		int num;
		printf("1.�α��� \n2.ȸ������ \n3.���� \n����: ");
		scanf("%d", &num);
		switch (num)
		{
		case 1:
			if (Login())
			{
				return 1;
			}
			break;
		case 2:
			if (Entry())
			{
				return 1;
			}
		case 3:return 0;
		default:break;
		}
		system("cls");
	}
}
int Login()
{
	char tmp_id[20], tmp_pw[20];
	getchar();
	printf("ID: ");
	scanf("%s", tmp_id);
	getchar();
	printf("PW: ");
	scanf("%s", tmp_pw);
	return Login_Check(tmp_id, tmp_pw);
}
int Login_Check(char*tmp_id, char*tmp_pw)
{
	mem *move = head->next;
	FILE*fc;
	fc = fopen("c:/test/diary/mem.txt", "r");
	if (fc == NULL)
	{
		printf("��ϵ� ȸ�������� �����ϴ�\nȸ�������ϼ���\n");
		system("pause");
		return 0;
	}
	while (!feof(fc))
	{
		fscanf(fc, "%s %s\n", move->ID, move->PW);
		if (!strcmp(move->ID, tmp_id) && !strcmp(move->PW, tmp_pw))
		{
			pass = move;
			return 1;
		}
		move = move->next;
	}
	printf("ID �Ǵ� PW�� �������� �ʽ��ϴ�\n");
	system("pause");
	return 0;
	fclose(fc);
}
int Entry()
{
	char ID[20];
	char PW[20];
	mem move;
	FILE *fc;
	fc = fopen("c:/test/diary/mem.txt", "r");
	printf("ID: ");
	scanf("%s", ID);
	printf("PW: ");
	scanf("%s", PW);
	if (fc != NULL)
	{
		while (!feof(fc))
		{
			fscanf(fc, "%s %s\n", move.ID, move.PW);
			if (!strcmp(move.ID, ID))
			{
				printf("������ ID�� �ֽ��ϴ�. \n");
				fclose(fc);
				return 0;
			}
		}
		fclose(fc);
		fc = fopen("c:/test/diary/mem.txt", "a");
	}
	else
		fc = fopen("c:/test/diary/mem.txt", "w");
	fprintf(fc, "%s %s\n", ID, PW);//���ο� ȸ�������� ���Ͽ� �߰� 
	fclose(fc);
	addMember(ID, PW);//���� �Է� ���� ȸ������ ����Ʈ�� ���� 
	return 1;
}
void addMember(char *id, char *pw)//����Ʈ �ǵڿ� �߰��ϴ� �Լ� 
{
	mem *add = (mem*)malloc(sizeof(mem));
	strcpy(add->ID, id);
	strcpy(add->PW, pw);
	add->next = NULL;
	tail->next = add;
	tail = add;
	pass = add;
}