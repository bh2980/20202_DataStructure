#include <stdlib.h>
#include <stdio.h>

typedef enum {
	FALSE,
	TRUE
} Boolean;

typedef void* Element;

typedef struct stack_node {
	//Element ����
	Element item;

	//next stack �ּҰ�
	struct stack_node* next;
	//���� StackNode��� �̸��� �������� �ʾƼ�
}StackNode;

typedef struct stack_header {
	//ó�� stack �ּҰ�
	StackNode* fadd;

	//size ��
	int size;

	//top �� : ����
	int top;
}Stack;

Stack* CreateStack(int size) {
	//stack_header�� �޸� �Ҵ� �� �ʱ�ȭ

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

	//Push�Ҷ����� �޸� �Ҵ�.
	StackNode* nStack = (StackNode*)malloc(sizeof(StackNode));

	if (nStack == NULL) {
		printf("Memory allcation is failed.\n");
		free(pStack);
		return;
	}

	nStack->next = pStack->fadd;
	pStack->fadd = nStack; //nStack�� item+next�� ������ �Ҵ��, nStack�� �� item�� �ּҰ��� �ǹ�
	nStack->item = item;

	pStack->top++;
}

Element Pop(Stack* pStack) {
	//��������� ����
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

	//return ���� Element�� ����
}

Element Top(Stack* pStack) {
	if (pStack->top < 0) {
		printf("The Stack is Empty.\n");
		return 0;
	}

	//pStack�� ���� ���� �ִ� ���� ������.
	return pStack->fadd->item;
	//return Element
}

Boolean IsFullStack(Stack* pStack) {
	if (pStack->size == pStack->top + 1) return TRUE;
	else return FALSE;
	//size�� top �� ���ؼ� ������ TRUE �ٸ��� FALSE ����
}

Boolean IsEmptyStack(Stack* pStack) {
	if (pStack->top < 0) return TRUE;
	else return FALSE;
	//top ���� 0�̸� return TRUE �ƴϸ� FALSE
}

int CountStackItem(Stack* pStack) {
	//top+1 �� ����
	return pStack->top + 1;
}

void ClearStack(Stack* pStack) {
	//top�� 0�� �ɶ����� Pop ����.
	while (pStack->top >= 0) {
		Pop(pStack);
	}
}

void Destory(Stack* pStack) {
	ClearStack(pStack);
	free(pStack);

	//free �����־����. + �����Ҵ�Ȱ� �� free
	//������ free
	//����ü ���ο� stack �迭 free
}