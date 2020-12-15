#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* Element;

typedef struct q {
	Element* queue;
	//ť
	int size;
	//ť�� ���
	int front;
	//ť�� ��
	int rear;
	//ť�� ��
}Queue;

Queue* CreateQueue(int size) {
	Queue* pQueue = (Queue*)malloc(sizeof(Queue));
	//Queue��ŭ�� size�� �޸𸮿� �Ҵ��� �Ŀ� �� �ּҸ� pQueue�� ����

	if (pQueue == NULL) {
		printf("�Ҵ� ����\n");
		return NULL;
	}//�Ҵ� ����

	pQueue->queue = (Element*)malloc(sizeof(Element) * size + 1);
	//��ĭ ��ĭ ���� size+1ĭ ����

	pQueue->size = size + 1;
	pQueue->front = 0;
	pQueue->rear = 0;

	return pQueue;
}

int IsFullQ(Queue* pQueue) {
	if ((pQueue->rear + 1) % (pQueue->size) == pQueue->front) {
		return 1;
	}
	else return 0;
}

int IsNullQ(Queue* pQueue) {
	if (pQueue->front == pQueue->rear) {
		return 1;
	}
	else return 0;
}

void EnQ(Queue* pQueue, Element data) {
	if (IsFullQ(pQueue)) {
		printf("This queue is FULL.\n");
		return;
	}

	char* newData = (char*)malloc(sizeof(Element));
	if (newData == NULL) {
		printf("�Ҵ� ����\n");
		return;
	}
	strcpy(newData, data);

	pQueue->rear = (pQueue->rear + 1) % (pQueue->size);
	pQueue->queue[pQueue->rear] = newData;
	printf("pQueue[%d] : %s\n", pQueue->rear, data);

	return;
}

Element DeQ(Queue* pQueue) {
	if (IsNullQ(pQueue)) {
		printf("This queue is EMPTY\n");
		return NULL;
	}

	pQueue->front = (pQueue->front + 1) % (pQueue->size);
	//printf("Now front : %d\n", pQueue->front);
	Element e = pQueue->queue[pQueue->front];

	return e;
}

Element QFront(Queue* pQueue) {
	if (IsNullQ(pQueue)) {
		return NULL;
	}

	return pQueue->queue[pQueue->front + 1];
}

Element QRear(Queue* pQueue) {
	if (IsNullQ(pQueue)) {
		return NULL;
	}

	return pQueue->queue[pQueue->rear];
}

void printfQ(Queue* pQueue) {
	if (IsNullQ(pQueue)) return;

	int n = pQueue->front, order = 1;

	do {
		n++;

		printf("%s%d", pQueue->queue[n % pQueue->size], order++);

		if (n % pQueue->size != pQueue->rear) printf(", ");

	} while ((n % pQueue->size) != pQueue->rear);

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