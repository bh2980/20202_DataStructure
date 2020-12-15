#include <stdio.h>
#include <stdlib.h>
#include "Ad_Queue.h"

 /*
 Stack?�� vertex�� ����.
 meatrix�� 0, 1 ǥ��?

 �� Node�� ������ �˾ƾ� �Ѵ�.
 �ϴ� ��ü������ �ѹ� �Ⱦ ���� �ٸ� ��尡 �� ����� �˾Ƴ�.

 �� ���鿡 ���ؼ� matrix�� �������ϴµ�...?
 �̰� ��� �����ұ�

 ��� nXn �迭�� ����. -> �޴� ���� X...?
 �ϴ� nXn �迭�� ����� ���ڿ� ���ĺ��� ��ġ. -> �����ڵ� ���� ���?

 ���ĺ��� ��� ���ڷ� ó�� A = 65
 -> ��� ���°� �ʿ䰡 ����.

 Vertex Vector -> ��¥�� �ڷῡ�� ���ӵ� ���ĺ��� ���Ƿ� 65���� �ִ밪�� ������ int
 
 vertex ����
 matrix �ּ�

 Adjacency matrix
 : 

 vertex�� ������ ��� ���ұ��?
 �װ� �����Լ��� �˾Ƽ� ���ٰſ���.
 ->�Է� �Լ��� ������� ���� �޶����� ��
 ����ȿ� ���Խ��Ѿ���.
 */

typedef char Element;

typedef struct {
	int vNum;//�� ����� ����
	int** arr;//Adjacency
	short direct;//���⼺ ���� 0 : ����, 1 : ����.
	Element root;
}Graph;

Graph* createGraph(int nodeNum, short direct, Element root);
void addNode(Element to, Element add, Graph* pGraph);
void destroyGraph(Graph* pGraph);

int vertexNum(char* filename) {
	char ch, tmp;
	FILE* fp = fopen(filename, "r");
	if (!fp) {
		printf("Open Filed\n");
		return 0;
	}

	ch = getc(fp);

	while ((tmp = getc(fp)) != EOF) {
		if (ch < tmp) {
			ch = tmp;
		}
	}

	fclose(fp);

	return ch - 64;
}

Graph* createFileGraph(short direct) {
	char ch, add;

	char filename[100];
	printf("File name if a graph : ");
	gets(filename);

	FILE* fp = fopen(filename, "r");
	if (!fp) {
		printf("Open Filed\n");
		return 0;
	}

	ch = getc(fp);//root ����

	Graph* pGraph = createGraph(vertexNum(filename), direct, ch);
	getc(fp);

	int cn = fscanf(fp, "%c %c\n", &ch, &add);

	while (cn > 0) {//��� �Է�
		addNode(ch, add, pGraph);
		cn = fscanf(fp, "%c %c\n", &ch, &add);
	}

	fclose(fp);

	return pGraph;
}

Graph* createGraph(int nodeNum, short direct, Element root) {
	Graph* pGraph = (Graph*)malloc(sizeof(Graph));
	if (!pGraph) {//graph�� NULL�̶��
		printf("malloc failed\n");
		return NULL;
	}

	pGraph->vNum = nodeNum;

	pGraph->direct = direct;

	pGraph->root = root;

	pGraph->arr = (int**)calloc(pGraph->vNum, sizeof(int**));
	if (!pGraph->arr) {
		printf("malloc failed\n");
		destroyGraph(pGraph);
		return NULL;
	}

	for (int i = 0; i < pGraph->vNum; i++) {
		pGraph->arr[i] = (int*)calloc(pGraph->vNum, sizeof(int*));
		if (!pGraph->arr[i]) {
			printf("malloc failed\n");
			destroyGraph(pGraph);
			return NULL;
		}
	}

	return pGraph;
}

void addNode(Element to, Element add, Graph* pGraph) {
	int into = to - 65;
	int inadd = add - 65;

	pGraph->arr[into][inadd] = 1;
	if (!pGraph->direct) {//���⼺�� ���ٸ�
		pGraph->arr[inadd][into] = 1;
	}

	return;
}

void destroyGraph(Graph* pGraph) {
	for (int i = 0; i < pGraph->vNum; i++) {
		free(pGraph->arr[i]);
	}

	free(pGraph->arr);
	free(pGraph);

	return;
}

void depthFisrtTraversal(int root, int** arr, int size) {//���� �������ΰ� �׷���
	/*
	* 0, arr, 8
	�׷����� ��Ʈ������ �����ؼ� ����� ���� ���� �켱���� ȣ���ϴ� �Լ�.
	����Լ� style
	for���� �����鼭 ���� 0���� ũ�ٸ� �ش� ���� ȣ��
	ȣ�� �� j�� �������� ���� ��� �� -1 ����.
	return ���� j = 9�� �Ǹ� return
	*/

	int i = 0;

	printf("%c ", root+65);
	for (; i < size; i++) {
		if (arr[root][i] > 0) {
			for (int j = 0; j < size; j++) {
				arr[j][i] *= -1;
			}
			depthFisrtTraversal(i, arr, size);
		}
	}
	if (i == 9) return;

	return;
}

void dftGraph(Graph* pGraph) {
	int root2 = pGraph->root - 65;
	depthFisrtTraversal(root2, pGraph->arr, pGraph->vNum);

	for (int i=0; i < pGraph->vNum; i++) {
		for (int j = 0; j < pGraph->vNum; j++) {
			pGraph->arr[i][j] *= -1;
		}
	}

	return;
}

void bftGraph(Graph* pGraph) {
	int root2 = pGraph->root - 65;
	Queue* pQueue = CreateQueue(100);

	EnQ(pQueue, root2);

	while(!IsNullQ(pQueue)) {
		int i = DeQ(pQueue);

		printf("%c ", i + 65);
		for (int j = 0; j < pGraph->vNum; j++) {
			if (pGraph->arr[i][j] > 0) {
				EnQ(pQueue, j);
				for (int k = 0; k < pGraph->vNum; k++) {
					pGraph->arr[k][j] *= -1;
				}
			}
		}
	}

	for (int i = 0; i < pGraph->vNum; i++) {
		for (int j = 0; j < pGraph->vNum; j++) {
			pGraph->arr[i][j] *= -1;
		}
	}

	DestroyQ(pQueue);

	return;
}

void printfMatrix(Graph* pGraph) {
	for (int i = 0; i < pGraph->vNum; i++) {
		printf("%-3c", i + 65);
	}

	printf("\n");

	for (int i = 0; i < pGraph->vNum; i++) {
		for (int j = 0; j < pGraph->vNum; j++) {
			printf("%-3d", pGraph->arr[i][j]);
		}
		printf("%c\n", i + 65);
	}
	printf("\n");

	return;
}

void whatTheGraph(Graph* pGraph) {
	for (int i = 0; i < pGraph->vNum; i++) {
		printf("%c : ", i + 65);
		for (int j = 0; j < pGraph->vNum; j++) {
			if (pGraph->arr[i][j]) printf("%c ", j + 65);
		}
		printf("\n");
	}

	printf("\n");

	return;
}