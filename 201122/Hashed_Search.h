#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*
hash �Լ��� ���� �����ؾ��Ѵ�. ��ȯ��
�׳� ���� ������ �迭 ������� ���� �������� ���� ����. �׸��� ���� ������
������ index�� +1�ؼ� �ְ� �������� ��� +1�ؼ� ����
������ ���µ��� �������� ������ ���ƿͼ� �ٽ� +1�ؼ� ����.

hash �Լ��� �����Ϳ� �迭�� ũ�⸦ �޾Ƽ� hash���� ����. int
�޴� �迭���� ��� 0���� �ʱ�ȭ
*/

typedef int Find2;

int hash(Find2 data, int size) {
	return data % size;
}

int hashedSearch(Find2 data, int* arr, int size) {
	 /*
	 0�� �ƴ϶�� hash �Լ��� ���ļ� ���� addr�� ���� ������ 1return
	 �ƴϸ� 1�� �����ϸ鼭 ������ 1 return�ϰ� ���ڸ��� ���ƿ��� 0 return
	 */

	int addr = hash(data, size);
	int i = addr;

	if (data == 0) data = size + 1;
	
	while (arr[i] != data) {
		i++;

		if (i == size) i = 0;

		if (i == addr) break;
	}

	if (arr[i] == data) return 1;
	else return 0;
}

void inputHash(Find2 data, int* arr, int size) {

	if (!arr[hash(data, size)]) {//ĭ�� ����ִٸ�
		if (!data) arr[hash(data, size)] = size+1;//�����Ͱ� 0�̶��
		else arr[hash(data, size)] = data;
	}
	else {
		int add = hash(data, size);
		int i = add;

		while (arr[add]) {
			add++;
			if (add == i) break;

			if (add == size-1) add = 0;
		}

		if (add == i) {
			printf("The array is FULL\n");
			return;
		}

		if (!data) arr[add] = size+1;
		else arr[add] = data;
	}

	return;
}

int fileInputHash(char* name, int* arr, int size) {
	FILE* fp = fopen(name, "r");
	if (!fp) {
		printf("Open Filed\n");
		return 0;
	}

	int i = -1;
	char string[100];
	char ch = fgetc(fp);

	while (ch != EOF) {
		if (ch >= '0' && ch <= '9') {//�޾ƿ� ���ڰ� ���ڶ��
			i++;
			string[i] = ch;
		}
		else {//��ȣ�� �����̶��
			if (i >= 0) {
				inputHash(atoi(string), arr, size);

				for (; i >= 0; i--) {
					string[i] = 0;
				}//clear
			}
		}

		ch = fgetc(fp);
	}

	if (string[0]) {
		inputHash(atoi(string), arr, size);
	}

	fclose(fp);
}