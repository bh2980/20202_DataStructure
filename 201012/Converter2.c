#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Stack_Link.h"

/*
스위치 문으로 구현

Push시

toBinary
int로 입력 받고 2로 나누면서 나머지에 따라 string "1", "0"을 stack에 넣고
Pop으로 빼면서 string에 합쳐서 이 string을 반환하는 함수
//바로 Push?

Pop시

toDemical
String에 Pop을 통해 꺼낸 수를 넣고 이 String의 길이를 계산해서
for문 돌려사면서 배열처럼 index를 역순으로 읽어서 2의 i승만큼 곱한 값을 int에 누적
이 int 값을 반환

Exit 시
끝

Stack Stat는 따로 만들어서 스위치문 밖에 배치
printStack 함수 쓰고 count+1

printfStack
배열 하나 복사해서 끝날때 까지 출력 후 Destroy
*/

void printfStack(Stack* pStack) {
	Stack* tmp = CreateStack(100);
	Stack* tmp2 = CreateStack(100);
	Element e;

	while (!IsEmptyStack(pStack)) {
		e = Pop(pStack);
		Push(tmp, e);
		Push(tmp2, e);
	}

	while (!IsEmptyStack(tmp2)) {
		Push(pStack, Pop(tmp2));
	}

	while (!IsEmptyStack(tmp)) {
		Push(tmp2, Pop(tmp));
	}

	while (!IsEmptyStack(tmp2)) {
		printf("%s ", Pop(tmp2));
	}

	Destory(tmp);
	Destory(tmp2);
	tmp = NULL;
	tmp2 = NULL;

	return;
}

char* toBinary(int n) {
	Stack* tmp = CreateStack(100);

	char* ch = (char*)malloc(sizeof(char*));
	*ch = NULL;

	do {
		if (n % 2 == 1) {
			Push(tmp, "1");
		}
		else {
			Push(tmp, "0");
		}

		n /= 2;

	} while (n != 0);

	while (!IsEmptyStack(tmp)) {
		strcat(ch, Pop(tmp));
	}

	Destory(tmp);
	tmp = NULL;

	return ch;
}

int toDemical(Stack* pStack) {
	int n = 0;

	char ch[100] = { '\0' };
	strcpy(ch, Top(pStack));
	for (int i = strlen(ch) - 1; i >= 0; i--) {
		if (ch[i] == '1') {
			n += (int)pow(2, strlen(ch) - 1 - i);
		}
	}

	return n;
}

int main(void) {
	int n;
	Stack* pStack = CreateStack(100);
	char* ch;

	while (1) {
		A:
		printf("Push (0), Pop (1), Exit(2) : ");
		scanf("%d", &n);

		switch (n) {
		case 0:
			printf("Push : ");
			scanf("%d", &n);

			if (n < 0) {
				printf("음수는 입력할 수 없습니다.\n\n");
				goto A;
			}

			ch = toBinary(n);

			Push(pStack, ch);

			break;
		case 1:
			if (IsEmptyStack(pStack)) {
				printf("The Stack is Empty. Can't pop from it.\n");
				return 0;
			}

			n = toDemical(pStack);

			printf("Pop : %d (%s)\n", n, Pop(pStack));

			break;
		case 2:
			return 0;
			break;
		default:
			printf("올바른 입력이 아닙니다.\n\n");
			goto A;
		}

		printf("STACK Stat : ");
		printfStack(pStack);
		printf("(%d)\n\n", pStack->top + 1);
	}

	Destory(pStack);
	pStack = NULL;

	return 0;
}