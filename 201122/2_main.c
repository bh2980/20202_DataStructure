#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "SortWay.h"

int main(void) {
	char name[100];

	printf("Input file name : ");
	gets(name);

	int size = checkSize(name);
	int* arr = inputFile(name, size);

	printf("\nChoose a sorting method to use (Seletion : 0, Insertion : 1, Bubble : 2, Quick : 3, Merge : 4) : ");
	int sort = 9;
	scanf("%d", &sort);
	switch (sort) {
	case 0: //Seletion
		seletionSort(arr, size);
		break;
	case 1: //Insertion
		insertionSort(arr, size);
		break;
	case 2: //Bubble
		bubbleSort(arr, size);
		break;
	case 3: //Quick
		quickSort(arr, size);
		break;
	case 4: //Merge
		mergeSort(arr, 0, size-1);
		break;
	default:
		break;
	}

	printf("\nThe numbers sorted : ");
	for (int i = 0; i < size; i++) {
		printf("%d", arr[i]);
		if (i != size - 1) printf(", ");
	}

	printf("\n");

	return 0;
}