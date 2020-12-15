#include <stdlib.h>
#include <stdio.h>

typedef enum {
	FALSE,
	TRUE
} Boolean;

typedef char* Element;

typedef struct stack_node {
	Element item;

	struct stack_node* next;
}StackNode;

typedef struct stack_header {
	StackNode* fadd;

	int size;
	int top;
}Stack;

Stack* CreateStack(int size) {
	Stack* pStack = (Stack*)malloc(sizeof(Stack));

	pStack->fadd = NULL;
	pStack->size = size;
	pStack->top = -1;

	return pStack;
}


void Push(Stack* pStack, Element item) {
	if (pStack->size == pStack->top + 1) {
		printf("The Stack is Full.\n");
		return;
	}

	StackNode* nStack = (StackNode*)malloc(sizeof(StackNode));

	if (nStack == NULL) {
		printf("Memory allcation is failed.\n");
		free(pStack);
		return;
	}

	nStack->next = pStack->fadd;
	pStack->fadd = nStack;
	nStack->item = item;

	pStack->top++;
}

Element Pop(Stack* pStack) {
	if (pStack->top < 0) {
		printf("The Stack is Empty.\n");
		return 0;
	}

	Element e = pStack->fadd->item;
	StackNode* pOldNode = pStack->fadd;
	pStack->fadd = pStack->fadd->next;
	free(pOldNode);

	pStack->top--;

	return e;
}

Element Top(Stack* pStack) {
	if (pStack->top < 0) {
		printf("The Stack is Empty.\n");
		return 0;
	}

	return pStack->fadd->item;
}

Boolean IsFullStack(Stack* pStack) {
	if (pStack->size == pStack->top + 1) return TRUE;
	else return FALSE;
}

Boolean IsEmptyStack(Stack* pStack) {
	if (pStack->top < 0) return TRUE;
	else return FALSE;
}

int CountStackItem(Stack* pStack) {
	return pStack->top + 1;
}

void ClearStack(Stack* pStack) {
	while (pStack->top >= 0) {
		Pop(pStack);
	}
}

void Destory(Stack* pStack) {
	ClearStack(pStack);
	free(pStack);
}