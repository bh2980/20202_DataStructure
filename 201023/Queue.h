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

int IsNullQueue(Queue* pQueue) {
	if (pQueue->cnt == 0)  return 1;
	else return 0;
}

void EnQueue(Queue* pQueue, Element data) {
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

	if (IsNullQueue(pQueue)) {
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

Element DeQueue(Queue* pQueue) {

	if (IsNullQueue(pQueue)) {
		return NULL;
	}

	Element e = pQueue->front->data;

	QueueNode* OldNode = (QueueNode*)malloc(sizeof(QueueNode));
	if (OldNode == NULL) {
		printf("할당 실패\n");
		return NULL;
	}

	if (IsNullQueue(pQueue)) {
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
	if (IsNullQueue(pQueue)) {
		return NULL;
	}

	return pQueue->front->data;
}

Element QRear(Queue* pQueue) {
	if (IsNullQueue(pQueue)) {
		return NULL;
	}

	return pQueue->rear->data;
}

void ClearQueue(Queue* pQueue) {
	while (!IsNullQueue(pQueue)) {
		DeQueue(pQueue);
	}

	return;
}

void DestroyQ(Queue* pQueue) {
	ClearQueue(pQueue);
	free(pQueue);

	pQueue = NULL;

	return;
}

void printQ(Queue* pQueue){

  Queue* tmp = CreateQueue(100);
  Queue* tmp2 = CreateQueue(100);

  while(!IsNullQueue(pQueue)){
    Element e = DeQueue(pQueue);

    EnQueue(tmp, e);
    EnQueue(tmp2, e);
  }

  while(!IsNullQueue(tmp2)){
    EnQueue(pQueue, DeQueue(tmp2));
  }

  while(!IsNullQueue(tmp)){
    printf("%s ", DeQueue(tmp));
  }

  return;
}