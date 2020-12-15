#include <stdlib.h>
#include <stdio.h>

typedef enum {
	FALSE,
	TRUE
} Boolean;

typedef void* Element;

typedef struct {
	//값이 들어가는 공간인 스택 배열의 첫번째 주소값 포인터 변수 -> 동적 할당으로 할당
	//배열의 크기
	//현재 칸

	Element* stack; //이중포인터
	int size;
	int top;
}Stack;

Stack* CreateStack(int size) {
	//Stack 구조체를 하나 만들어서 배열 포인터에 배열 할당
	Stack* pStack = (Stack*)malloc(sizeof(Stack));

	//malloc만 사용하면 메모리를 할당해줄 뿐 그 메모리가 어떤 자료값인지는 알려주지 않음 
	//-> (Stack*)처럼 어떤 자료형이 들어가는지 알려주어야함.

	if (pStack == NULL) {
		printf("Memory allocation is failed. : pStack");
		return 0;
	}

	//stack 만들기
	pStack->stack = (Element*)malloc(sizeof(Element) * size);//Element크기만큼의 메모리를 size 개수만큼 할당
	if (pStack->stack == NULL) {
		printf("Memory allocation is failed. : pStack->stack");
		free(pStack);
		return 0;
	}

	//size 저장
	pStack->size = size;

	//현재 칸 초기화
	pStack->top = -1;

	return pStack;
}

void Push(Stack* pStack, Element item) {
	//꽉차면 넣으면 안되니까 에러
	if (pStack->size == pStack->top + 1) {
		printf("The Stack is Full.\n");

		return;
	}

	//pStack에 Element를 넣음.
	pStack->stack[++pStack->top] = item;

	//넣으면 칸수 하나 +
	//포인터를 배열처럼 사용 가능.
}

Element Pop(Stack* pStack) {
	//비어있으면 에러
	if (pStack->top < 0) {
		printf("The Stack is Empty.\n");
		return 0;
	}

	//pStack에서 가장 위에 위치한 값 꺼내기
	//현재 칸수 --
	return pStack->stack[pStack->top--];

	//return 꺼낸 Element값 리턴
}

Element Top(Stack* pStack) {
	if (pStack->top < 0) {
		printf("The Stack is Empty.\n");
		return 0;
	}

	//pStack의 가장 위에 있는 값을 보여줌.
	return pStack->stack[pStack->top];
	//return Element
}

void Destory(Stack* pStack) {
	if (pStack->stack != NULL) free(pStack->stack);

	free(pStack);
	//free 시켜주어야함. + 동적할당된건 다 free
	//구조제 free
	//구조체 내부에 stack 배열 free
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
	//top 값 리턴
	return pStack->top;
}

void ClearStack(Stack* pStack) {
	//top이 0이 될때까지 Pop 실행.
	while (pStack->top >= 0) {
		Pop(pStack);
	}
}