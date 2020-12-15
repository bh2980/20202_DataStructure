#include <stdlib.h>
#include <stdio.h>

typedef enum {
	FALSE,
	TRUE
} Boolean;

typedef char* Element;

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

Boolean IsEmptyStack(Stack* pStack) {
	if (pStack->top < 0) return TRUE;
	else return FALSE;
	//top ���� 0�̸� return TRUE �ƴϸ� FALSE
}

Stack* CreateStack(int size) {
	//stack_header�� �޸� �Ҵ� �� �ʱ�ȭ

	Stack* pStack = (Stack*)malloc(sizeof(Stack));

	pStack->fadd = NULL;
	pStack->size = NULL;
	pStack->top = -1;

	return pStack;
}

void Push(Stack* pStack, Element item) {
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
	if (IsEmptyStack(pStack)) {
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
	if (IsEmptyStack(pStack)) {
		printf("The Stack is Empty.\n");
		return 0;
	}

	//pStack�� ���� ���� �ִ� ���� ������.
	return pStack->fadd->item;
	//return Element
}

int CountStackItem(Stack* pStack) {
	//top+1 �� ����
	return pStack->top + 1;
}

void ClearStack(Stack* pStack) {
	//top�� 0�� �ɶ����� Pop ����.
	while (!IsEmptyStack(pStack)) {
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