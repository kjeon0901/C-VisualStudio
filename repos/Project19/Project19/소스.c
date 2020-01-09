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
void disp(bin*show) {////////전위/중위/후위 => 오늘 만든 tree 프로그램에서 view함수, save함수에서 각각 적용시켜볼 수 있음. 
	printf("%d \n", show->num);//printf가 처음에 => 전위 방식 : root가 처음에 출력됨. 
	if (show->left != NULL)
		disp(show->left);
	//printf가 가운데 => 중위 방식 : root가 가운데 출력됨. 
	if (show->right != NULL)
		disp(show->right);
	//printf가 마지막에 => 후위 방식 : root가 마지막에 출력됨.
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