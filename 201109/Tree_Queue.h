#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef TreeNode* factor;

typedef struct qnode {
	factor data;
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

void EnQ(Queue* pQueue, factor data) {
	QueueNode* NewNode = (QueueNode*)malloc(sizeof(QueueNode));
	if (NewNode == NULL) {
		printf("할당 실패\n");
		return;
	}
	NewNode->data = data;
	NewNode->next = NULL;

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

factor DeQ(Queue* pQueue) {

	if (IsNullQ(pQueue)) {
		return NULL;
	}

	factor e = pQueue->front->data;

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

factor QFront(Queue* pQueue) {
	if (IsNullQ(pQueue)) {
		return NULL;
	}

	return pQueue->front->data;
}

factor QRear(Queue* pQueue) {
	if (IsNullQ(pQueue)) {
		return NULL;
	}

	return pQueue->rear->data;
}

void printfQ(Queue* pQueue) {
	QueueNode* tmp = pQueue->front;

	while (1) {
		if (tmp == NULL) break;

		printf("%s ", tmp->data->data);
		tmp = tmp->next;
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