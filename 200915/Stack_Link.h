#include <stdlib.h>
#include <stdio.h>

typedef enum {
	FALSE,
	TRUE
} Boolean;

typedef void* Element;

typedef struct stack_node {
	//Element 저장
	Element item;

	//next stack 주소값
	struct stack_node* next;
	//아직 StackNode라는 이름이 정해지지 않아서
}StackNode;

typedef struct stack_header {
	//처음 stack 주소값
	StackNode* fadd;

	//size 값
	int size;

	//top 값 : 개수
	int top;
}Stack;

Stack* CreateStack(int size) {
	//stack_header에 메모리 할당 및 초기화

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

	//Push할때마다 메모리 할당.
	StackNode* nStack = (StackNode*)malloc(sizeof(StackNode));

	if (nStack == NULL) {
		printf("Memory allcation is failed.\n");
		free(pStack);
		return;
	}

	nStack->next = pStack->fadd;
	pStack->fadd = nStack; //nStack은 item+next의 순서로 할당됨, nStack이 곧 item의 주소값을 의미
	nStack->item = item;

	pStack->top++;
}

Element Pop(Stack* pStack) {
	//비어있으면 에러
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

	//return 꺼낸 Element값 리턴
}

Element Top(Stack* pStack) {
	if (pStack->top < 0) {
		printf("The Stack is Empty.\n");
		return 0;
	}

	//pStack의 가장 위에 있는 값을 보여줌.
	return pStack->fadd->item;
	//return Element
}

Boolean IsFullStack(Stack* pStack) {
	if (pStack->size == pStack->top + 1) return TRUE;
	else return FALSE;
	//size와 top 값 비교해서 같으면 TRUE 다르면 FALSE 리턴
}

Boolean IsEmptyStack(Stack* pStack) {
	if (pStack->top < 0) return TRUE;
	else return FALSE;
	//top 값이 0이면 return TRUE 아니면 FALSE
}

int CountStackItem(Stack* pStack) {
	//top+1 값 리턴
	return pStack->top + 1;
}

void ClearStack(Stack* pStack) {
	//top이 0이 될때까지 Pop 실행.
	while (pStack->top >= 0) {
		Pop(pStack);
	}
}

void Destory(Stack* pStack) {
	ClearStack(pStack);
	free(pStack);

	//free 시켜주어야함. + 동적할당된건 다 free
	//구조제 free
	//구조체 내부에 stack 배열 free
}