#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Stack_Array.h"
//#include "Stack_Link.h"

int main(void) {
	int n, ori;
	Stack* pStack = CreateStack(50);

	printf("Enter a number : ");
	scanf("%d", &n);

	ori = n;

	while (n / 2 != 0){
		Push(pStack, n % 2);
		n /= 2;
	}

	Push(pStack, n);

	printf("The binary number of %d: ", ori);
	while (pStack->top >= 0) {
		printf("%d", Pop(pStack));
	}

	Destory(pStack);
	pStack = NULL;

	return 0;
}