#include <stdlib.h>
#include <stdio.h>

typedef enum {
	FALSE,
	TRUE
} Boolean;

typedef void* Element;

typedef struct {
	//���� ���� ������ ���� �迭�� ù��° �ּҰ� ������ ���� -> ���� �Ҵ����� �Ҵ�
	//�迭�� ũ��
	//���� ĭ

	Element* stack; //����������
	int size;
	int top;
}Stack;

Stack* CreateStack(int size) {
	//Stack ����ü�� �ϳ� ���� �迭 �����Ϳ� �迭 �Ҵ�
	Stack* pStack = (Stack*)malloc(sizeof(Stack));

	//malloc�� ����ϸ� �޸𸮸� �Ҵ����� �� �� �޸𸮰� � �ڷᰪ������ �˷����� ���� 
	//-> (Stack*)ó�� � �ڷ����� ������ �˷��־����.

	if (pStack == NULL) {
		printf("Memory allocation is failed. : pStack");
		return 0;
	}

	//stack �����
	pStack->stack = (Element*)malloc(sizeof(Element) * size);//Elementũ�⸸ŭ�� �޸𸮸� size ������ŭ �Ҵ�
	if (pStack->stack == NULL) {
		printf("Memory allocation is failed. : pStack->stack");
		free(pStack);
		return 0;
	}

	//size ����
	pStack->size = size;

	//���� ĭ �ʱ�ȭ
	pStack->top = -1;

	return pStack;
}

void Push(Stack* pStack, Element item) {
	//������ ������ �ȵǴϱ� ����
	if (pStack->size == pStack->top + 1) {
		printf("The Stack is Full.\n");

		return;
	}

	//pStack�� Element�� ����.
	pStack->stack[++pStack->top] = item;

	//������ ĭ�� �ϳ� +
	//�����͸� �迭ó�� ��� ����.
}

Element Pop(Stack* pStack) {
	//��������� ����
	if (pStack->top < 0) {
		printf("The Stack is Empty.\n");
		return 0;
	}

	//pStack���� ���� ���� ��ġ�� �� ������
	//���� ĭ�� --
	return pStack->stack[pStack->top--];

	//return ���� Element�� ����
}

Element Top(Stack* pStack) {
	if (pStack->top < 0) {
		printf("The Stack is Empty.\n");
		return 0;
	}

	//pStack�� ���� ���� �ִ� ���� ������.
	return pStack->stack[pStack->top];
	//return Element
}

void Destory(Stack* pStack) {
	if (pStack->stack != NULL) free(pStack->stack);

	free(pStack);
	//free �����־����. + �����Ҵ�Ȱ� �� free
	//������ free
	//����ü ���ο� stack �迭 free
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
	//top �� ����
	return pStack->top;
}

void ClearStack(Stack* pStack) {
	//top�� 0�� �ɶ����� Pop ����.
	while (pStack->top >= 0) {
		Pop(pStack);
	}
}