#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "Ad_Matrix3.h"

int main(void) {
	Graph* pGraph = createFileGraph(1);
	//���⼺ ���� : 1, ���� : 0
	if (!pGraph) {
		printf("Create Failed\n");
		return 0;
	}

	shortPath(pGraph);

	destroyGraph(pGraph);

	return 0;
}