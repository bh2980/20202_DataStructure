#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Binary_Search.h"
#include "Hashed_Search.h"

int main(void) {
	int name[173] = { 0 };
	int target, choose;

	printf("Input file name : ");
	gets(name);

	printf("Target integer : ");
	scanf("%d", &target);

A:
	printf("Choose a searching method (Binary : 1, Hashed : 2) : ");
	scanf("%d", &choose);

	int result = 0;
	int size = checkSize(name);
	int* arr = (int*)calloc(size, sizeof(int));
	int* address = (int*)malloc(sizeof(int));

	switch (choose) {
	case 1:
		//input
		fileInputBinary(name, arr);
		result = binarySearch(target, arr, size, address);
		break;
	case 2:
		//input
		fileInputHash(name, arr, size);
		result = hashedSearch(target, arr, size);
		break;
	default: printf("잘못된 입력입니다\n\n");
		goto A;
	}

	if (result) {
		printf("%d is found!\n", target, result);
	}
	else {
		printf("%d is not found\n", target, result);
	}

	free(arr);
	free(address);

	return 0;
}