#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

/*
[��ũ�� ����Ʈ]
-���ϸ���Ʈ
����Ʈ n�� ����ü ���� ���, ����Ʈ n�� n+1�� �ּҸ� ��� ����
����:head, ��:tail=>��� ���� (�����ͷ� ����)

-���߸���Ʈ
-ȯ�ฮ��Ʈ
*/

typedef struct student {
	int num;
	char name[10];
	struct student *next; //�ڽ��� �ּ�(���� ����)�� ���� �� �ִ� next��� �̸��� ������ ���� ����. ��������
}std;

std* input(std*top); //head�� �����ͺ����ϱ� �����ͺ����� �޵�, top�̶�� �̸����� ����
void main() {
	std*head = NULL;
	head = input(head); //�������Է�
	head = input(head); //1�� ���� head ������ top�� ����. 
	head = input(head);


}
std* input(std*top) {
	std*tail = top;	//while�� �����ۿ� ���� ����: tail, head�� �Ѵ� ����������
	std*temp = NULL;

	temp = (std*)malloc(sizeof(std)); //temp�� ù��° �����Ҵ�
	printf("��ȣ: ");
	scanf("%d", &temp->num); //->�� &���� ����. num�� �޸𸮴ϱ� �ּҸ� ��Ÿ���� ���� &
	printf("�̸�: ");
	scanf("%s", temp->name); //->�� &���� ����. name�� name[]�� �ּҴϱ� &�ʿ����
	temp->next = NULL; //�����߿�

	if (top == NULL) //ù��° input���� �����
		return temp; //�Ƚ��ָ� temp�� ���������� ù��° ����Ʈ�� �����. 
	while (tail->next != NULL) { //while�� �����߿�. �Ϻ��� �����ؾ� ��.
		tail = tail->next;
	}
	tail->next = temp;

	return top;
}