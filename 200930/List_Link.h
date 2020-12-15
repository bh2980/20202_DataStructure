#include <stdio.h>
#include <stdlib.h>

typedef int Element;

typedef struct listnode {
	Element data;
	struct listnode* next;
}ListNode;

typedef struct listheader {
	int count;
	ListNode* top;
	ListNode* rear;
}List;

int isNullList(List* pList) {
	if (pList->count < 0) return 1;
	else return 0;
}

void printfList(List* pList) {
	if (isNullList(pList)) {
		printf("\n");
		return;
	}

	ListNode* tmpNode = pList->top;

	while (tmpNode->next != NULL) {
		printf("%d, ", tmpNode->data);
		tmpNode = tmpNode->next;
	}

	printf("%d\n", tmpNode->data);

	return;
}

List* createList(int size) {
	List* pList = (List*)malloc(sizeof(List));
	if (pList == NULL) {
		printf("Memory allocation failed\n");
		return NULL;
	}

	pList->count = -1;
	pList->top = NULL;
	pList->rear = NULL;

	return pList;
}

int search(List* pList, Element data) {
	if (isNullList(pList)) {
		printf("This list is NULL.\n");
		return 0;
	}

	//하나씩 조회해가면서 똑같은 data가 나오면 1 return

	ListNode* pListNode = pList->top;

	while (pListNode->next != NULL) {
		 if (pListNode->data == data) return 1;
		 pListNode = pListNode->next;
	}

	if (pListNode->data == data) return 1;

	return 0;
}

void pushList(List* pList, Element data) {
	ListNode* NewNode = (ListNode*)malloc(sizeof(ListNode));
	if (NewNode == NULL) {
		printf("Memory allocation failed\n");
		free(pList);
		return;
	}

	NewNode->data = data;
	NewNode->next = NULL;

	if (isNullList(pList)) {
		pList->top = NewNode;
		pList->rear = NewNode;

		pList->count++;
	}
	else {
		if (search(pList, data)) {
			printf("This data is already existed.\n");
			return;
		}

		ListNode* NextNode = pList->top;
		ListNode* PreNode = NULL;

		while (NextNode->data < data) {
			PreNode = NextNode;

			if (PreNode->next == NULL) break;
			NextNode = NextNode->next;
		}

		if (PreNode == NULL) {//가장 첫번째
			NewNode->next = NextNode;
			pList->top = NewNode;
		}
		else{
			if (PreNode->next == NULL) {
				pList->rear = NewNode;
			}

			NewNode->next = PreNode->next;
			PreNode->next = NewNode;
		}

		pList->count++;
	}

	return;
}

Element popList(List* pList, Element data) {
	if (isNullList(pList)) {
		printf("This list is NULL\n");
		return NULL;
	}

	if (!search(pList, data)) {
		printf("This data is not in the list.\n");
		return NULL;
	}

	ListNode* NextNode = pList->top;
	ListNode* PreNode = NULL;

	while (NextNode->data < data && NextNode->next != NULL) {
		PreNode = NextNode;
		NextNode = NextNode->next;
	}

	ListNode* pOldNode = (ListNode*)malloc(sizeof(ListNode));
	Element e = NULL;

	if (PreNode == NULL) {//첫번째
		pOldNode = pList->top;
		pList->top = pOldNode->next;
		e = pOldNode->data;
		free(pOldNode);
	}
	else {//중간
		pOldNode = NextNode;
		PreNode->next = NextNode->next;

		e = pOldNode->data;
		free(pOldNode);

		if (PreNode->next == NULL) {
			pList->rear = PreNode;
		}
	}

	pList->count--;

	return e;
}

void clearList(List* pList) {
	while (!isNullList(pList)) {
		popList(pList, pList->rear->data);
	}

	return;
}

void destroyList(List* pList) {
	clearList(pList);
	free(pList);
	pList = NULL;

	return;
}

