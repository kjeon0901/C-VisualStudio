#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

void main() {
	int arr[] = { 10, 20, 30, 40 };
	char arr2[4];
	int i = 0;
	char*pi = arr2;

	printf("arr size: %dbyte \n", sizeof(arr));
	printf("pi size: %dbyte \n", sizeof(pi));
}