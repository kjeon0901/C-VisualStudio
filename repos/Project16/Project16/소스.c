#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

char chDay[7][3] = { "��", "��", "��", "ȭ", "��", "��", "��" };
void display();

int main()
{
	int day, nal, moon_day;
	int Month = 5;
	char total;

	while (1)
	{
		printf("��¥�� �Է��ϼ��� : ");
		if (scanf("%d", &day) == 0)
		{
			scanf("%c", &total);
			if (total == '#')
				display();
			else if (total == 'q')
			{
				printf("���α׷��� �����մϴ�.\n");
				break;
			}
			else
				printf("�߸��� �Է� �Դϴ�. �ٽ� Ȯ���Ͻð� �Է��ϼ���\n");
		}
		else
		{

			nal = day % 7;
			moon_day = day + 1;

			if (moon_day > 30)
			{
				moon_day -= 30;
				Month++;
			}
			printf("��� ��¥ : %04d/%02d/%02d \n", 2003, 6, day);
			printf("���� ��¥ : %04d/%02d/%02d \n", 2003, Month, moon_day);
			printf("%s���� �Դϴ�.\n", chDay[nal]);
		}
		printf("\n���Ḧ ���Ͻø� q�� �Է��ϼ���.\n");
	}
	return 0;
}

void display()
{
	int i;
	printf("************ 6�� ***********\n");
	printf(" �� �� ȭ �� �� �� ��\n");
	printf(" --------------------------\n");
	for (i = 1; i <= 30; i++)
	{
		printf("%4d", i);
		if (i % 7 == 0)
			printf("\n");
	}
	printf("\n");
}