#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*
hash 함수를 내가 구현해야한다. 실환가
그냥 들어온 정수를 배열 사이즈로 나눈 나머지에 값을 넣자. 그르면 되지 않을까
같으면 index에 +1해서 넣고 차있으면 계속 +1해서 넣자
끝까지 갔는데도 차있으면 앞으로 돌아와서 다시 +1해서 넣자.

hash 함수는 데이터와 배열의 크기를 받아서 hash값을 뱉음. int
받는 배열값은 모두 0으로 초기화
*/

typedef int Find2;

int hash(Find2 data, int size) {
	return data % size;
}

int hashedSearch(Find2 data, int* arr, int size) {
	 /*
	 0이 아니라면 hash 함수를 거쳐서 나온 addr의 값과 같으면 1return
	 아니면 1씩 증가하면서 맞으면 1 return하고 제자리로 돌아오면 0 return
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

	if (!arr[hash(data, size)]) {//칸이 비어있다면
		if (!data) arr[hash(data, size)] = size+1;//데이터가 0이라면
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
		if (ch >= '0' && ch <= '9') {//받아온 글자가 숫자라면
			i++;
			string[i] = ch;
		}
		else {//기호나 공백이라면
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