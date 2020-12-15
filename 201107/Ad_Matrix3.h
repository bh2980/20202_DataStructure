#include <stdio.h>
#include <stdlib.h>
#include "Ad_Queue.h"

/*
Stack?에 vertex를 넣음.
meatrix에 0, 1 표시?

총 Node의 개수를 알아야 한다.
일단 전체적으로 한번 훑어서 서로 다른 노드가 총 몇개인지 알아냄.

이 노드들에 대해서 matrix를 만들어야하는데...?
이걸 어떻게 구현할까

노드 nXn 배열을 만듬. -> 메뉴 지정 X...?
일단 nXn 배열을 만들고 숫자와 알파벳을 매치. -> 유니코드 관계 사용?

알파벳을 모두 숫자로 처리 A = 65
-> 노드 형태가 필요가 없다.

Vertex Vector -> 어짜피 자료에는 연속된 알파벳이 오므로 65부터 최대값을 가지는 int

vertex 개수
matrix 주소

Adjacency matrix
:

vertex의 개수를 어떻게 정할까요?
그건 메인함수가 알아서 해줄거에요.
->입력 함수도 헤더파일 따라서 달라지는 듯
헤더안에 포함시켜야함.
*/

typedef char Element;

typedef struct {
	int vNum;//총 노드의 개수
	int** arr;//Adjacency
	short direct;//방향성 여부 0 : 없음, 1 : 있음.
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

	ch = getc(fp);//root 설정

	Graph* pGraph = createGraph(vertexNum(filename), direct, ch);
	getc(fp);

	int cn = fscanf(fp, "%c %c %d\n", &ch, &add, &weight);

	while (cn > 0) {//노드 입력
		addNode(ch, add, weight, pGraph);
		cn = fscanf(fp, "%c %c %d\n", &ch, &add, &weight);
	}

	fclose(fp);

	return pGraph;
}

Graph* createGraph(int nodeNum, short direct, Element root) {
	Graph* pGraph = (Graph*)malloc(sizeof(Graph));
	if (!pGraph) {//graph가 NULL이라면
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
	if (!pGraph->direct) {//방향성이 없다면
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

void depthFisrtTraversal(int root, int** arr, int size) {//이중 포인터인가 그렇다
	/*
	* 0, arr, 8
	그래프의 루트값에서 시작해서 행렬을 따라 깊이 우선으로 호출하는 함수.
	재귀함수 style
	for문을 돌리면서 값이 0보다 크다면 해당 열을 호출
	호출 시 j를 기준으로 열의 모든 값 -1 곱함.
	return 조건 j = 9가 되면 return
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
	//mintree에 포함된 열은 -
	//포함되지 않았지만 같은 노드는 0
	//root의 행을 훑으면서 가장 작은 수 -로 바꿈 -> i, j를 저장하며 진행
	//root의 행을 훑은 후, 가장 작은 ij값 저장하고 root의 행에서 -값인 vertex를 훑으면서 가장 작은 ij 저장

	/*
	함수는 행렬을 행을 받아서 끝까지 스캔한다.
	이때 가장 작은 수를 저장한다. -> 원 함수에서 포인터를 통해 그릇을 넘겨준다. 지속적으로 업데이트
	-1보다 작은 성분이 나오면 해당 성분의 열값을 행으로 하는 행을 다시 호출한다.
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

	//초기설정

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

	for (int i = 0; i < pGraph->vNum; i++) {
		if (i != pGraph->root - 65) {
			printf("%c %c : %d\n", pGraph->root, i + 65, weight[i]);
		}
	}

	printf("\n");

	/*
	초기설정

	노드 개수와 같은 배열을 두개 만들어
	루트 노트의 값을 1, 0으로 조절 후

	*/

	/*
	최 앞 node를 저장해놓아야함.
	저장한 node로 부터 adjency가 가장 작은걸 fromroot를 T로 바꾼다.

	for문을 돌려가면서 F라면 weight의 같은 성분을 비교한다.
	이때

	(저장한 node의 값 + 저장한 노드로부터 adjency의 값)

	과

	(weight의 그 노드의 값)

	을 비교하여 더 작은 쪽으로 업데이트한다.

	for문을 다 돌았으면
	저장한 node로 부터 adjency가 가장 작은걸 fromroot를 T로 바꾼다

	*/

	int num = 1, lastnode = pGraph->root - 65;

	int min = 100, i = pGraph->root - 65;

	while (num < pGraph->vNum) {

		min = 100;

		for (int j = 0; j < pGraph->vNum; j++) {
			if ((matrix[lastnode][j] <= min) && fromroot[j] == 0) {
				min = matrix[lastnode][j];
				i = j;
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

		for (int i = 0; i < pGraph->vNum; i++) {
			if (i != pGraph->root - 65) {
				printf("%c %c : %d\n", pGraph->root, i + 65, weight[i]);
			}
		}
		printf("\n");
	}

	return;
}