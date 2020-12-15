#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SortWay.h"

/*
정렬된*** array가 들어옴
size의 반인 녀석을 읽어서 찾으려는 값과 비교함

만약 읽은 값이 같다면 return 1
작다면 앞에 있는 나머지의 중간값의 크기와 비교함
크다면 나머지의 뒤에 있는 나머지에서의 중간값과 크기 비교함.

->없다면 어떻게 될까?
반띵한 인덱스가 자기자신과 같아짐.
-> return 0

어떤 유형의 값이 들어올 지 모르므로 return값은 T/F
*/

typedef int Find;

int binarySearch(Find data, int* arr, int size, int** address) {
	/*
	data : 찾아야하는 값
	arr : 들어오는 배열
	size 배열의 크기
	address : 찾은 값의 주소
	*/

	if (data == *(arr + size / 2)) {
		*address = arr + size / 2;
		return 1;
	}

	if (size == 0) {
		return 0;
	}

	if (data > * (arr + size / 2)) {//배열 중간값이 데이터보다 작다면
		if (!size % 2) {//size가 짝수라면
			return binarySearch(data, arr + size / 2, size / 2, address);
		}
		else {//홀수라면
			return binarySearch(data, (arr + size / 2) + 1, size / 2, address);
		}
	}
	else {//배열 중간값이 데이터보다 크다면
		if (!size % 2) {//size가 짝수라면
			return binarySearch(data, arr, size / 2, address);
		}
		else {//홀수라면
			return binarySearch(data, arr, size / 2, address);
		}
	}
}

int fileInputBinary(char* name, int* arr) {
	FILE* fp = fopen(name, "r");
	if (!fp) {
		printf("Open Filed\n");
		return 0;
	}

	/*
	파일 형식에 관계없이 숫자를 넣고싶음
	반복문을 통해서 하나씩 읽어서 숫자면(isdigit) string 배열에 저장
	기호가 나온다면 저장하지 않고 atoi로 int 배열에 저장 후 int 배열 i++
	*/

	int i = -1;
	int j = 0;
	char ch = fgetc(fp);
	char string[100];

	while (ch != EOF) {
		if (ch >= '0' && ch <= '9') {//받아온 글자가 숫자라면
			i++;
			string[i] = ch;
		}
		else {//기호나 공백이라면
			if (i >= 0) {
				arr[j] = atoi(string);
				j++;
				for (; i >= 0; i--) {
					string[i] = 0;
				}//clear
			}
		}

		ch = fgetc(fp);
	}

	if (string[0]) {
		arr[j] = atoi(string);
		j++;
	}

	seletionSort(arr, j);

	fclose(fp);

	return j;
}