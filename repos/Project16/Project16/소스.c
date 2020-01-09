#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

char chDay[7][3] = { "토", "일", "월", "화", "수", "목", "금" };
void display();

int main()
{
	int day, nal, moon_day;
	int Month = 5;
	char total;

	while (1)
	{
		printf("날짜를 입력하세요 : ");
		if (scanf("%d", &day) == 0)
		{
			scanf("%c", &total);
			if (total == '#')
				display();
			else if (total == 'q')
			{
				printf("프로그램을 종료합니다.\n");
				break;
			}
			else
				printf("잘못된 입력 입니다. 다시 확인하시고 입력하세요\n");
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
			printf("양력 날짜 : %04d/%02d/%02d \n", 2003, 6, day);
			printf("음력 날짜 : %04d/%02d/%02d \n", 2003, Month, moon_day);
			printf("%s요일 입니다.\n", chDay[nal]);
		}
		printf("\n종료를 원하시면 q를 입력하세요.\n");
	}
	return 0;
}

void display()
{
	int i;
	printf("************ 6월 ***********\n");
	printf(" 일 월 화 수 목 금 토\n");
	printf(" --------------------------\n");
	for (i = 1; i <= 30; i++)
	{
		printf("%4d", i);
		if (i % 7 == 0)
			printf("\n");
	}
	printf("\n");
}