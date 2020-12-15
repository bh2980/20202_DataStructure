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
void addNode(Element to, Element add, int weight, Graph* pGraph);
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
	int weight;

	char filename[100];
	printf("File name if a graph : ");
	gets(filename);

	FILE* fp = fopen(filename, "r");
	if (!fp) {
		printf("Open Filed\n");
		return NULL;
	}

  //new root ����
  printf("Source vertex : ");
  scanf("%c", &ch);

	Graph* pGraph = createGraph(vertexNum(filename), direct, ch);

	int cn = fscanf(fp, "%c %c %d\n", &ch, &add, &weight);

	while (cn > 0) {//��� �Է�
		addNode(ch, add, weight, pGraph);
		cn = fscanf(fp, "%c %c %d\n", &ch, &add, &weight);
	}

	fclose(fp);

	printf("\n");

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

void addNode(Element to, Element add, int weight, Graph* pGraph) {
	int into = to - 65;
	int inadd = add - 65;

	pGraph->arr[into][inadd] = weight;
	if (!pGraph->direct) {//���⼺�� ���ٸ�
		pGraph->arr[inadd][into] = weight;
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

	printf("%c ", root + 65);
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

	for (int i = 0; i < pGraph->vNum; i++) {
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

	while (!IsNullQ(pQueue)) {
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
			if (pGraph->arr[i][j]) printf("%c (%d) ", j + 65, pGraph->arr[i][j]);
		}
		printf("\n");
	}

	printf("\n");

	return;
}

void makeMin(int** matrix, int row, int size, int* minpath) {
	for (int i = 0; i < size; i++) {
		if (matrix[row][i] < minpath[0] && matrix[row][i] > 0) {
			minpath[0] = matrix[row][i];
			minpath[1] = row;
			minpath[2] = i;
		}

		if (matrix[row][i] < 0) {
			makeMin(matrix, i, size, minpath);
		}
	}

	return;
}

void minSTree(Graph* pGraph) {
	//mintree�� ���Ե� ���� -
	//���Ե��� �ʾ����� ���� ���� 0
	//root�� ���� �����鼭 ���� ���� �� -�� �ٲ� -> i, j�� �����ϸ� ����
	//root�� ���� ���� ��, ���� ���� ij�� �����ϰ� root�� �࿡�� -���� vertex�� �����鼭 ���� ���� ij ����

	/*
	�Լ��� ����� ���� �޾Ƽ� ������ ��ĵ�Ѵ�.
	�̶� ���� ���� ���� �����Ѵ�. -> �� �Լ����� �����͸� ���� �׸��� �Ѱ��ش�. ���������� ������Ʈ
	-1���� ���� ������ ������ �ش� ������ ������ ������ �ϴ� ���� �ٽ� ȣ���Ѵ�.
	*/

	int** matrix = (int**)calloc(pGraph->vNum, sizeof(int**));
	if (!matrix) {
		printf("malloc failed\n");
		destroyGraph(pGraph);
		return;
	}

	for (int i = 0; i < pGraph->vNum; i++) {
		matrix[i] = (int*)calloc(pGraph->vNum, sizeof(int*));
		if (!matrix[i]) {
			printf("malloc failed\n");
			destroyGraph(pGraph);
			return;
		}
	}

	for (int i = 0; i < pGraph->vNum; i++) {
		for (int j = 0; j < pGraph->vNum; j++) {
			matrix[i][j] = pGraph->arr[i][j];
		}
	}

	for (int j = 0; j < pGraph->vNum; j++) {
		if (matrix[j][pGraph->root - 65] > 0) matrix[j][pGraph->root - 65] = 0;
	}

	int vnodenum = 1;

	//�ʱ⼳��

	int* minpath = (int*)malloc(sizeof(int) * 3);

	while (vnodenum < pGraph->vNum) {
		minpath[0] = 1000;
		minpath[1] = 0;
		minpath[2] = 0;

		makeMin(matrix, pGraph->root - 65, pGraph->vNum, minpath);

		matrix[minpath[1]][minpath[2]] *= -1;

		for (int j = 0; j < pGraph->vNum; j++) {
			if (matrix[j][minpath[2]] > 0) matrix[j][minpath[2]] = 0;
		}

		vnodenum++;

		printf("%c %c (%d)\n", minpath[1] + 65, minpath[2] + 65, minpath[0]);
	}

	printf("\n");

	free(minpath);

	return;
}

void shortPath(Graph* pGraph) {
	int** matrix = (int**)calloc(pGraph->vNum, sizeof(int**));
	if (!matrix) {
		printf("malloc failed\n");
		destroyGraph(pGraph);
		return;
	}

	for (int i = 0; i < pGraph->vNum; i++) {
		matrix[i] = (int*)calloc(pGraph->vNum, sizeof(int*));
		if (!matrix[i]) {
			printf("malloc failed\n");
			destroyGraph(pGraph);
			return;
		}
	}

	for (int i = 0; i < pGraph->vNum; i++) {
		for (int j = 0; j < pGraph->vNum; j++) {
			if (!pGraph->arr[i][j]) matrix[i][j] = 1000;
			else matrix[i][j] = pGraph->arr[i][j];
		}
	}


	int* fromroot = (int*)calloc(pGraph->vNum, sizeof(int));
	int* weight = (int*)calloc(pGraph->vNum, sizeof(int));

	fromroot[pGraph->root - 65] = 1;
	for (int i = 0; i < pGraph->vNum; i++) {
		if (i != pGraph->root - 65) {
			weight[i] = matrix[pGraph->root - 65][i];
		}
	}

  int* last = (int*)calloc(pGraph->vNum, sizeof(int));

  printf("%-2s %-4s %-4s\n", "v", "d[v]", "p[v]");

	for (int i = 0; i < pGraph->vNum; i++) {
		if (i != pGraph->root - 65) {
			if(weight[i] == 1000) printf("%-2c %-4c %-4c\n", i + 65, ' ', last[i]+65);
			else printf("%-2c %-4d %-4c\n", i + 65, weight[i], last[i]+65);
		}
	}

	printf("\n");

	/*
	�ʱ⼳��

	��� ������ ���� �迭�� �ΰ� �����
	��Ʈ ��Ʈ�� ���� 1, 0���� ���� ��

	*/

	/*
	�� �� node�� �����س��ƾ���.
	������ node�� ���� adjency�� ���� ������ fromroot�� T�� �ٲ۴�.

	for���� �������鼭 F��� weight�� ���� ������ ���Ѵ�.
	�̶�

	(������ node�� �� + ������ ���κ��� adjency�� ��)

	��

	(weight�� �� ����� ��)

	�� ���Ͽ� �� ���� ������ ������Ʈ�Ѵ�.

	for���� �� ��������
	������ node�� ���� adjency�� ���� ������ fromroot�� T�� �ٲ۴�

	*/

	int num = 1, lastnode = pGraph->root - 65;

	int min = 100, i = pGraph->root - 65;

	while (num < pGraph->vNum) {

		min = 100;

		for (int j = 0; j < pGraph->vNum; j++) {
			if ((matrix[lastnode][j] <= min) && fromroot[j] == 0) {
				min = matrix[lastnode][j];
				i = j;
        last[j] = lastnode;
			}
		}

		fromroot[i] = 1;
		lastnode = i;
		num++;

		for (int j = 0; j < pGraph->vNum; j++) {
			if (fromroot[j] == 0) {
				if (weight[j] > weight[i] + matrix[i][j]) {
					weight[j] = weight[i] + matrix[i][j];
				}
			}
		}

    printf("%-2s %-4s %-4s\n", "v", "d[v]", "p[v]");

		for (int i = 0; i < pGraph->vNum; i++) {
			if (i != pGraph->root - 65) {
        if(weight[i] == 1000) printf("%-2c %-4c %-4c\n", i + 65, ' ', last[i]+65);
				else printf("%-2c %-4d %-4c\n", i + 65, weight[i], last[i]+65);
			}
		}
		printf("\n");
	}

	return;
}