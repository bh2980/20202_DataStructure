#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Stack_Link.h"

/*
����ġ ������ ����

Push��

toBinary
int�� �Է� �ް� 2�� �����鼭 �������� ���� string "1", "0"�� stack�� �ְ�
Pop���� ���鼭 string�� ���ļ� �� string�� ��ȯ�ϴ� �Լ�
//�ٷ� Push?

Pop��

toDemical
String�� Pop�� ���� ���� ���� �ְ� �� String�� ���̸� ����ؼ�
for�� ������鼭 �迭ó�� index�� �������� �о 2�� i�¸�ŭ ���� ���� int�� ����
�� int ���� ��ȯ

Exit ��
��

Stack Stat�� ���� ���� ����ġ�� �ۿ� ��ġ
printStack �Լ� ���� count+1

printfStack
�迭 �ϳ� �����ؼ� ������ ���� ��� �� Destroy
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
				printf("������ �Է��� �� �����ϴ�.\n\n");
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
			printf("�ùٸ� �Է��� �ƴմϴ�.\n\n");
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