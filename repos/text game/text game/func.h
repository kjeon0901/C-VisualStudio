#ifdef FUNC

#else 
#define FUNC


#include"index.h"
#include"struc.h"

void init();
void input();
void disp();
void save();
void load();

void init() {
	list = (test**)malloc(count * sizeof(test*));
	list[0] = (test*)malloc(sizeof(test));//����ü���� �����Ҵ�
}
void input() {

	printf("��ȣ: ");
	scanf("%d", &list[count - 1]->num);
	printf("�̸�: ");
	scanf("%s", list[count - 1]->name);

	count++;
	list = (test**)realloc(list, count * sizeof(test*));
	list[count - 1] = (test*)malloc(sizeof(test)); //�� count���� 1������ ���ؾȵ�
}
void load() { //������ �Է°� ����ϴϱ� input�Լ��� ���
	FILE *lf;

	lf = fopen("c:/test/test.txt", "r");
	if (lf != NULL) { //NULL���� �� �ִٴ� �� ������ �� ���ȴٴ� ��
		while (!feof(lf)) { //�������� �����鼭 �޸� ������ 0, ������ -1��ȯ
			fscanf(lf, "%d %s \n", &list[count - 1]->num, &list[count - 1]->name); //������ ���� ������� Ŀ���� ����. ������ ���൵ ������ ���� \n ������.���� ������ ����� ���ٵ� �����ؼ� 5���̶�� ����. 

			count++;
			list = (test**)realloc(list, count * sizeof(test*));
			list[count - 1] = (test*)malloc(sizeof(test));
		}
		fclose(lf);
	}
}
void disp() {
	int i;
	for (i = 0; i < count - 1; i++) {
		printf("��ȣ: %d �̸�: %s \n", list[i]->num, list[i]->name);
	}
}
void save() { //������ ��°� ����ϴϱ� disp�Լ��� ���
	FILE*sf;
	int i;
	sf = fopen("c:/test/test.txt", "w"); //��ġ �Ƚᵵ �ǳ�?

	for (i = 0; i < count - 1; i++) {
		fprintf(sf, "%d %s \n", list[i]->num, list[i]->name);
	}
	fclose(sf);
}

#endif