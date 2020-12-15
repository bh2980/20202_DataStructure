#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//#include "Ad_Matrix3.h"

//#include "Ad_Matrix.h"
#include "Ad_List.h"

int main(void) {
	Graph* pGraph = createFileGraph(0);
	//���⼺ ���� : 1, ���� : 0
	if (!pGraph) {
		printf("Create Failed\n");
		return 0;
	}

	printf("\nThe graph is :\n");
	whatTheGraph(pGraph);

	/*
	
	//�� �Լ����� Ad_Matrix3.h���� �۵�

	printf("Minimum spanning tree :\n");
	minSTree(pGraph);

	printf("Shortest path from %c :\n", pGraph->root);
	shortPath(pGraph);

	*/

	//������ �Լ����� Ad_Matrix.h, Ad_List.h���� �۵�

	printf("Depth FIrst Traversal : ");
	dftGraph(pGraph);
	printf("\n");
	
	printf("Breath FIrst Traversal : ");
	bftGraph(pGraph);

	destroyGraph(pGraph);

	return 0;
}