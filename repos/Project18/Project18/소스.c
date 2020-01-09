#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <string.h>

/*

�л��̸�, �л� ��������(3����), ���

�Է� �Լ� ,����Լ�

�л� 1�� �Է��Ҷ����� ��������(�̸��� ����������,���X)

���� �ҷ����� -> ��� ����ؼ� ����ü�� �Է�(�̰� ����)



�̸� �ϰ� ��ո� ���� �ٸ� ���Ͽ� ����



���Ϻҷ����� �ΰ� ���� �ٺҷ��ͼ� �̸��� �´�

��հ�����







*/

typedef struct test {

	int sc[3];

	float avg;

	char name[10];

	struct test * daum;

}test;

void input();

void disp();

void save();

void load();

test** top = NULL;

int size = 1;



void main() {

	load();

	disp();

	input();

	input();

	input();

	disp();

	// ���� ���� ->  ��� disp

	// ���� �ҷ����� - >�Է� input

	save();

}

void load() {

	FILE *f;

	int i;

	char name[10];

	f = fopen("score.txt", "r");

	if (f != NULL) {// ������ ���翩��

		while (!feof(f)) {

			if (top == NULL)

				top = (test**)malloc(sizeof(test*));

			else {

				size++;

				top = (test**)realloc(top, size * sizeof(test*));

			}

			top[size - 1] = (test*)malloc(sizeof(test));

			fscanf(f, "%s", top[size - 1]->name);

			fscanf(f, "%d", &top[size - 1]->sc[0]);

			fscanf(f, "%d", &top[size - 1]->sc[1]);

			fscanf(f, "%d\n", &top[size - 1]->sc[2]);

		}

		fclose(f);

	}

	f = fopen("avg.txt", "r");

	if (f != NULL) {

		while (!feof(f)) {

			fscanf(f, "%s", name);

			for (i = 0; i < size - 1; i++) {

				if (!strcmp(name, top[i]->name))

					fscanf(f, "%f", &top[i]->avg);

			}

		}

		fclose(f);

	}

}

void input() {

	if (top == NULL)

		top = (test**)malloc(sizeof(test*));

	else {

		size++;

		top = (test**)realloc(top, size * sizeof(test*));

	}

	printf("%d��° �Է� : ", size);

	top[size - 1] = (test*)malloc(sizeof(test));

	printf("�̸� : ");

	scanf("%s", top[size - 1]->name);

	printf("���� : ");

	scanf("%d", &top[size - 1]->sc[0]);

	scanf("%d", &top[size - 1]->sc[1]);

	scanf("%d", &top[size - 1]->sc[2]);

	top[size - 1]->avg = (top[size - 1]->sc[0] + top[size - 1]->sc[1] + top[size - 1]->sc[2]) / 3.0;

	save();

}

void disp() {

	int i;

	

	for (i = 0; i < size; i++)

		printf("%d %s %d %d %d \n", top[i]->avg, top[i]->name, top[i]->sc[0], top[i]->sc[1], top[i]->sc[2]);

}

void save() {

	int i;

	FILE*f;

	f = fopen("score.txt", "a+");

	fprintf(f, "%s %d %d %d \n", top[size - 1]->name, top[size - 1]->sc[0], top[size - 1]->sc[1], top[size - 1]->sc[2]);

	fclose(f);

	f = fopen("avg.txt", "a+");

	fprintf(f, "%s %f \n", top[size - 1]->name, top[size - 1]->avg);

	fclose(f);

}