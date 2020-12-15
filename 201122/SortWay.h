#include <stdio.h>
#include <stdlib.h>

int checkSize(char* name) {
	FILE* fp = fopen(name, "r");
	if (!fp) {
		printf("Open Filed\n");
		return 0;
	}

	char ch = fgetc(fp);
	int i = -1;
	int j = 0;
	char string[100] = { 0 };

	while (ch != EOF) {
		if (ch >= '0' && ch <= '9') {//받아온 글자가 숫자라면
			i++;
			string[i] = ch;
		}
		else {//기호나 공백이라면
			if (i >= 0) {
				j++;

				for (; i >= 0; i--) {
					string[i] = 0;
				}//clear
			}
		}

		ch = fgetc(fp);
	}

	if (string[0]) {
		j++;
		for (; i >= 0; i--) {
			string[i] = 0;
		}//clear
	}

	return j;
}

int* inputFile(char* name, int size) {
	FILE* fp = fopen(name, "r");
	if (fp == NULL) {
		printf("Open Failed\n");
		return NULL;
	}

	int* arr = (int*)calloc(size, sizeof(int));
	if (arr == NULL) {
		printf("malloc Failed\n");
		fclose(fp);
		return NULL;
	}

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

	fclose(fp);

	return arr;
}

void seletionSort(int* arr, int size) {
	int small = 0;
	int i = 0;

	for (i = 0; i < size - 1; i++) {
		small = i;
		for (int j = i + 1; j < size; j++) {
			if (arr[small] > arr[j]) small = j;
		}

		int tmp = 0;
		tmp = arr[i];
		arr[i] = arr[small];
		arr[small] = tmp;
	}

	return;
}

void insertionSort(int* arr, int size) {
	//unsort의 앞에 있는 데이터를 가져옴.
	//arr에서 data 보다 큰 index의 값을 만나면 브릭
	//거기부터 한칸씩 뒤로 미룬다.
	//그 값에 데이터를 넣는다.
	/*
	unsorted 영역을 정함 i=1부터
	sorted 영역 j<i에서 i번째와 크기 비교 후 i가 작다면 break;
	*/
	int i = 1;

	for (int i = 1; i < size; i++) {
		int j = 0;

		for (; j < i; j++) {
			if(arr[j] > arr[i]) break;
		}

		if (j < i) {
			int tmp = arr[i];

			for (; i > j; i--) {
				arr[i] = arr[i - 1];
			}

			arr[j] = tmp;
		}
	}

	return;
}

void bubbleSort(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		int min = size - 1;

		for (int j = size - 1; j >= i; j--) {
			if (arr[j] > arr[min]) {
				int tmp = arr[min];
				arr[min] = arr[j];
				arr[j] = tmp;
				//둘이 교체
			}
			
			if (arr[j] < arr[min]) {
			//최소값을 교체하고 끝
				min = j;
			}
		}
	}

	return;
}

void quickSort(int* arr, int size) {
	if (size <= 1) return;

	int start = 0;
	int middle = size / 2;
	int end = size - 1;
	int pivot = 0;

	 /*
	 중간값을 찾는다.
	 어떻게 찾지.
	 */

	if (arr[start] > arr[middle]) {
		if (arr[end] > arr[start]) {
			//end > start > middle
			pivot = start;
		}
		else if (arr[middle] > arr[end]) {
			//start > middle > end
			pivot = middle;
		}
		else {
			//start > end > middle
			pivot = end;
		}
	}
	else {
		if (arr[end] > arr[middle]) {
			//end > middle > start
			pivot = middle;
		}
		else if (arr[start] > arr[end]) {
			//middle > start > end
			pivot = start;
		}
		else {
			//middle > end > start
			pivot = end;
		}
	}

	int tmp = arr[start];
	arr[start] = arr[pivot];
	arr[pivot] = tmp;

	//pivot을 시작위치로 바꾼다.

	/*
	for문으로 양 끝에서 오면서 pivot보다 작은것을 찾으면 break
	둘이 바꾸고 다시 for문
	둘의 index가 같아지면 stop하고 상황 분석
	*/

	int i = 1; //pivot 제외
	int j = size - 1;

	while (1) {
		for (; i < size; i++) {
			if (arr[i] > arr[start]) break;
		}

		for (; j > 0; j--) {
			if (arr[j] < arr[start]) break;
		}

		if (i > j) break;

		tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
	}

	tmp = arr[j];
	arr[j] = arr[start];
	arr[start] = tmp;

	quickSort(arr, j);
	quickSort(arr+j+1, size-j-1);

	return;
}

void merge(int* arr, int low, int mid, int high) {
	int tmparr[500] = { 0 };

	int i, j, k;

	for (i = low, j = mid+1, k = 0; i <= mid && j <= high; k++) {
		if (arr[i] > arr[j]) {
			tmparr[k] = arr[j];
			j++;
		}
		else {
			tmparr[k] = arr[i];
			i++;
		}
	}

	if (j == high + 1) {//i가 남음
		for (; i <= mid; i++, k++) {
			tmparr[k] = arr[i];
		}
	}
	
	if (i == mid + 1) {
		for (; j <= high; j++, k++) {
			tmparr[k] = arr[j];
		}
	}

	for (i = low, k=0; i <= high; i++, k++) {
		arr[i] = tmparr[k];
	}

	return;
}

void mergeSort(int* arr, int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;
		mergeSort(arr, low, mid);
		mergeSort(arr, mid + 1, high);
		merge(arr, low, mid, high);
	}

	return;
}