#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Stack_Array.h"
//#include "Stack_Link.h"

int main(void) {
	int n;
	Stack* pStack = CreateStack(50);

	while (1) {
		printf("Enter a number: <Ctrl+d> to stop: ");
		if (scanf("%d", &n) <= 0) break; //scanf 함수는 입력된 개수 값을 반환

		Push(pStack, n);
	}

	if (pStack->top >= 0) {
		printf("\nThe List of numbers reversed : \n");

		while (pStack->top >= 0) {
			printf("%d\n", Pop(pStack));
		}
	}
	else Pop(pStack);

	Destory(pStack);
	pStack = NULL;

	return 0;
}