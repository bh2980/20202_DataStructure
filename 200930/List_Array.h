#include <stdio.h>
#include <stdlib.h>


/*
	typedef Element

	typedef List

	array 배열을 저장할 수 있는 주소공간 Element 배열의 첫 시작 주소를 가지는 포인터 변수 List;
	리스트의 size
	마지막 index값인 rear

	중복된 값은 넣지 않음.

	CreateList

	Push
	Search 함수로 받은 index를 MoveElement 함수에 넣어 빈칸을 만든 후 값을 넣음

	Delete
	Search
	PrintfList == travel

	DestoryList

	isNullList
	isFullList

*/

typedef int Element;

typedef struct listst {
	Element* list;

	int size;

	int rear;
}List;

int isNullList(List* pList) {
	if (pList->rear < 0) {
		return 1;
	}
	
	return 0;
}

int isFullList(List* pList) {
	if (pList->rear == pList->size) {
		return 1;
	}

	return 0;
}

List* createList(int size) {
	List* pList = (List*)malloc(sizeof(List));

	if (pList == NULL) {
		printf("Memory allocation failed\n");
		return NULL;
	}

	pList->list = (Element*)malloc(sizeof(Element) * size);
	if (pList->list == NULL) {
		printf("Memory allocation failed\n");
		free(pList);
		return NULL;
	}

	pList->size = size;
	pList->rear = -1;
	
	return pList;
}

int indexSearch(List* pList, Element data) {
	/*
	자기보다 같거나 큰 값을 만나면 그 값의 index를 리턴
	-> 같을 때와 클 때의 index 구분을 하지 못함.
	*/

	if (isNullList(pList)) {
		return -1;
	}

	int index = 0;
	
	while (data > pList->list[index] && index <= pList->rear) {
		index++;
	}

	return index;
}

int search(List* pList, Element data) {
	int index = indexSearch(pList, data);

	if (data == pList->list[index]) {
		return 1;
	}
	else return 0;
}

void pushList(List* pList, Element data){
	if (isFullList(pList)) {
		printf("This list is Full.\n");
		return;
	}

	//한 칸이라도 빈 칸이 있다면,

	if (search(pList, data)) {
		printf("This data is already existed.\n");
		return;
	}

	if (isNullList(pList)) {
		pList->list[0] = data;
	}
	else {
		Element tmp = NULL;
		int ground = indexSearch(pList, data);
		int index = pList->rear;

		while (index >= ground) {
			pList->list[index + 1] = pList->list[index];
			index--;
		}

		pList->list[index + 1] = data;
	}

	pList->rear++;

	return;
}

Element popList(List* pList, Element data) {
	if (isNullList(pList)) {
		printf("This list is NULL.\n");
		return NULL;
	}

	if (!search(pList, data)) {
		printf("The data isn't in the list.\n");
		return NULL;
	}

	int index = indexSearch(pList, data);
	Element tmp = pList->list[index];

	while (index < pList->rear) {
		pList->list[index] = pList->list[index+1];
		index++;
	}

	pList->list[pList->rear] = NULL;
	pList->rear--;

	return tmp;
}

void printfList(List* pList) {
	if (isNullList(pList)) {
		return;
	}

	int index = 0;

	while (index < pList->rear) {
		printf("%d, ", pList->list[index++]);
	}

	printf("%d", pList->list[index]);

	printf("\n");
	
	return;
} 

void clearList(List* pList) {
	while (!isNullList(pList)) {
		popList(pList, pList->list[pList->rear]);
	}

	return;
}

void destroyList(List* pList) {
	clearList(pList);
	free(pList->list);
	free(pList);
	pList = NULL;

	return;
}