#include <stdio.h>
#include <stdlib.h>


/*
	typedef Element

	typedef List

	array �迭�� ������ �� �ִ� �ּҰ��� Element �迭�� ù ���� �ּҸ� ������ ������ ���� List;
	����Ʈ�� size
	������ index���� rear

	�ߺ��� ���� ���� ����.

	CreateList

	Push
	Search �Լ��� ���� index�� MoveElement �Լ��� �־� ��ĭ�� ���� �� ���� ����

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
	�ڱ⺸�� ���ų� ū ���� ������ �� ���� index�� ����
	-> ���� ���� Ŭ ���� index ������ ���� ����.
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

	//�� ĭ�̶� �� ĭ�� �ִٸ�,

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