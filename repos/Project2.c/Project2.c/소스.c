#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

int main() {
	int arr[10] = { 0 };
	int i = 0, k=0;
	int *ptr = arr;

	for (i = 0; i < 10; i++) {
		while (getchar() != '\n');
		scanf("%d", ptr + 1);
	}
	for (k = 0; k < 10; k++) {
		printf("%d,", ptr[k]);
	}
	return 0;
}