#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* Element;

typedef struct qnode {
	Element data;
	struct qnode* next;
}QueueNode;

typedef struct q {
	QueueNode* front;
	QueueNode* rear;
	int cnt;
}Queue;

Queue* CreateQueue(int size) {
	Queue* pQueue = (Queue*)malloc(sizeof(Queue));
	if (pQueue == NULL) {
		printf("할당 실패\n");
		return NULL;
	}

	pQueue->front = NULL;
	pQueue->rear = NULL;
	pQueue->cnt = 0;

	return pQueue;
}

int IsNullQ(Queue* pQueue) {
	if (pQueue->cnt == 0)  return 1;
	else return 0;
}

void EnQ(Queue* pQueue, Element data) {
	char* NewData = (char*)malloc(sizeof(char*));
	if (NewData == NULL) {
		printf("할당 실패\n");
		return;
	}
	strcpy(NewData, data);

	QueueNode* NewNode = (QueueNode*)malloc(sizeof(QueueNode));
	if (NewNode == NULL) {
		printf("할당 실패\n");
		return;
	}
	NewNode->data = NewData;

	if (IsNullQ(pQueue)) {
		pQueue->front = NewNode;
		pQueue->rear = NewNode;
	}
	else {
		pQueue->rear->next = NewNode;
		pQueue->rear = NewNode;
	}

	pQueue->cnt++;

	return;
}

Element DeQ(Queue* pQueue) {

	if (IsNullQ(pQueue)) {
		return NULL;
	}

	Element e = pQueue->front->data;

	QueueNode* OldNode = (QueueNode*)malloc(sizeof(QueueNode));
	if (OldNode == NULL) {
		printf("할당 실패\n");
		return NULL;
	}

	if (IsNullQ(pQueue)) {
		free(pQueue->front);
		pQueue->front = NULL;
		pQueue->rear = NULL;
	}
	else {
		OldNode->next = pQueue->front;
		pQueue->front = OldNode->next->next;

		free(OldNode->next);
		free(OldNode);
		OldNode->next = NULL;
		OldNode = NULL;
	}

	pQueue->cnt--;

	return e;
}

Element QFront(Queue* pQueue) {
	if (IsNullQ(pQueue)) {
		return NULL;
	}

	return pQueue->front->data;
}

Element QRear(Queue* pQueue) {
	if (IsNullQ(pQueue)) {
		return NULL;
	}

	return pQueue->rear->data;
}

void printfQ(Queue* pQueue) {

	Queue* tmp = CreateQueue(100);
	if (tmp == NULL) {
		printf("할당 실패\n");
		return;
	}
	Queue* tmp2 = CreateQueue(100);
	if (tmp2 == NULL) {
		printf("할당 실패\n");
		return;
	}
	int order = 1;

	while (!IsNullQ(pQueue)) {

		Element e = DeQ(pQueue);
		EnQ(tmp, e);
		EnQ(tmp2, e);
	}

	while (!IsNullQ(tmp2)) {
		EnQ(pQueue, DeQ(tmp2));
	}

	while (!IsNullQ(tmp)) {
		printf("%s%d", DeQ(tmp), order++);
		if (tmp->cnt != 0) printf(", ");
	}

	return;
}

void ClearQ(Queue* pQueue) {
	while (!IsNullQ(pQueue)) {
		DeQ(pQueue);
	}

	return;
}

void DestroyQ(Queue* pQueue) {
	ClearQ(pQueue);
	free(pQueue);

	pQueue = NULL;

	return;
}