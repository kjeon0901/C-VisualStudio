#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*
�̸��ϰ� ��ո� ���� �ٸ� ���Ͽ� ����

���� �ҷ��� �� ��� ����ؼ� ����ü�� �Է��ϸ� �ȵǰ�, �ΰ� ���� �� �ҷ��ͼ� ���� ����ü������ �����Ų ����, �̸��� �´� ��հ� ����

*/

typedef struct student {
	char name[10];
	int grade[3];
	float avg;
	struct std *daum;
}std;
std**top = NULL;
int size = 1;
void input();
void disp();
void load();
void save(float sum);
void main() {
	load();
	disp();
	input();
	input();
	input();
	disp();
}

void input() {
	int i;
	float sum = 0;
	if (top == NULL)
		top = (std**)malloc(sizeof(std*));
	else
		top = (std**)realloc(top, size * sizeof(std*));
	top[size - 1] = (std*)malloc(sizeof(std));
	printf("<<%d��° �Է�>>\n", size);
	printf("�л� �̸�: ");
	scanf("%s", top[size - 1]->name);
	for (i = 0; i < 3; i++) {
		printf("���� %d ����: ", i + 1);
		scanf("%d", &top[size - 1]->grade[i]);
		sum += top[size - 1]->grade[i];
	}
	top[size - 1]->avg = 0.0;
	save(sum);
	size++;
}

void save(float a) {
	FILE*f;

	f = fopen("student.txt", "a+");

	fprintf(f, "%s %d %d %d \n", top[size - 1]->name, top[size - 1]->grade[0], top[size - 1]->grade[1], top[size - 1]->grade[2]);
	fclose(f);
	f = fopen("std_avg.txt", "a+");
	fprintf(f, "%s %f \n", top[size - 1]->name, a/3);
	fclose(f);
}

void disp() {
	int i = 0;
	for (i = 0; i < size - 1; i++) {
		printf("<< %d��° ��� >>\n", i + 1);
		printf("�̸�: %s \n", top[i]->name);
		printf("���� 1: %d \n����2: %d \n����3: %d \n", top[i]->grade[0], top[i]->grade[1], top[i]->grade[2]);
		if(top[i]->avg==0)
			printf("���: %f\n\n", 0.0);
		else
			printf("���: %f\n\n", top[i]->avg);
	}

}

void load() {
	int i;
	std*temp = NULL;
	FILE*f;
	f = fopen("student.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
			if (top == NULL)
				top = (std**)malloc(sizeof(std*));
			else
				top = (std**)realloc(top, size * sizeof(std*));
			top[size - 1] = (std*)malloc(sizeof(std));
			fscanf(f, "%s %d %d %d \n", top[size - 1]->name, &top[size - 1]->grade[0], &top[size - 1]->grade[1], &top[size - 1]->grade[2]);
			size++;
		}
		fclose(f);
	}
	temp = (std*)malloc(sizeof(std));
	f = fopen("std_avg.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
			fscanf(f, "%s %f\n", temp->name, temp->avg);
			for (i = 0; i < size - 1; i++) {
				if (!strcmp(temp->name, top[i]->name)) {
					top[i]->avg = temp->avg;
				}
			}
		}
		fclose(f);
	}
	free(temp);
}