#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct bin {
	int num;
	struct bin*left;
	struct bin*right;
}bin;
void input(bin*top, int num);
void disp(bin*show);
bin*root = NULL;

void main() {
	input(root, 10);
	input(root, 20);
	input(root->left, 30);
	input(root->left, 40);
	input(root, 50);
	input(root->right, 60);
	input(root->right, 70);
	disp(root);
}
void disp(bin*show) {////////����/����/���� => ���� ���� tree ���α׷����� view�Լ�, save�Լ����� ���� ������Ѻ� �� ����. 
	printf("%d \n", show->num);//printf�� ó���� => ���� ��� : root�� ó���� ��µ�. 
	if (show->left != NULL)
		disp(show->left);
	//printf�� ��� => ���� ��� : root�� ��� ��µ�. 
	if (show->right != NULL)
		disp(show->right);
	//printf�� �������� => ���� ��� : root�� �������� ��µ�.
}
void input(bin*top, int num) {
	bin*data = (bin*)malloc(sizeof(bin));
	data->num = num;
	data->left = NULL;
	data->right = NULL;

	if (root == NULL) {
		root = data;
		return;
	}

	if (top->left == NULL) {
		top->left = data;
		return;
	}
	if (top->right == NULL) {
		top->right = data;
		return;
	}

}