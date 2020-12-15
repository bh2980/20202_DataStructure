#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SortWay.h"

/*
���ĵ�*** array�� ����
size�� ���� �༮�� �о ã������ ���� ����

���� ���� ���� ���ٸ� return 1
�۴ٸ� �տ� �ִ� �������� �߰����� ũ��� ����
ũ�ٸ� �������� �ڿ� �ִ� ������������ �߰����� ũ�� ����.

->���ٸ� ��� �ɱ�?
�ݶ��� �ε����� �ڱ��ڽŰ� ������.
-> return 0

� ������ ���� ���� �� �𸣹Ƿ� return���� T/F
*/

typedef int Find;

int binarySearch(Find data, int* arr, int size, int** address) {
	/*
	data : ã�ƾ��ϴ� ��
	arr : ������ �迭
	size �迭�� ũ��
	address : ã�� ���� �ּ�
	*/

	if (data == *(arr + size / 2)) {
		*address = arr + size / 2;
		return 1;
	}

	if (size == 0) {
		return 0;
	}

	if (data > * (arr + size / 2)) {//�迭 �߰����� �����ͺ��� �۴ٸ�
		if (!size % 2) {//size�� ¦�����
			return binarySearch(data, arr + size / 2, size / 2, address);
		}
		else {//Ȧ�����
			return binarySearch(data, (arr + size / 2) + 1, size / 2, address);
		}
	}
	else {//�迭 �߰����� �����ͺ��� ũ�ٸ�
		if (!size % 2) {//size�� ¦�����
			return binarySearch(data, arr, size / 2, address);
		}
		else {//Ȧ�����
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
	���� ���Ŀ� ������� ���ڸ� �ְ����
	�ݺ����� ���ؼ� �ϳ��� �о ���ڸ�(isdigit) string �迭�� ����
	��ȣ�� ���´ٸ� �������� �ʰ� atoi�� int �迭�� ���� �� int �迭 i++
	*/

	int i = -1;
	int j = 0;
	char ch = fgetc(fp);
	char string[100];

	while (ch != EOF) {
		if (ch >= '0' && ch <= '9') {//�޾ƿ� ���ڰ� ���ڶ��
			i++;
			string[i] = ch;
		}
		else {//��ȣ�� �����̶��
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