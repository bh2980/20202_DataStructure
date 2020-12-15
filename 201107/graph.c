#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//#include "Ad_Matrix3.h"

//#include "Ad_Matrix.h"
#include "Ad_List.h"

int main(void) {
	Graph* pGraph = createFileGraph(0);
	//방향성 있음 : 1, 없음 : 0
	if (!pGraph) {
		printf("Create Failed\n");
		return 0;
	}

	printf("\nThe graph is :\n");
	whatTheGraph(pGraph);

	/*
	
	//이 함수들은 Ad_Matrix3.h에서 작동

	printf("Minimum spanning tree :\n");
	minSTree(pGraph);

	printf("Shortest path from %c :\n", pGraph->root);
	shortPath(pGraph);

	*/

	//이하의 함수들은 Ad_Matrix.h, Ad_List.h에서 작동

	printf("Depth FIrst Traversal : ");
	dftGraph(pGraph);
	printf("\n");
	
	printf("Breath FIrst Traversal : ");
	bftGraph(pGraph);

	destroyGraph(pGraph);

	return 0;
}