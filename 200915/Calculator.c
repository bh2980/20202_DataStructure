#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //isdigit
#include "Stack_Array.h"
//#include "Stack_Link.h"

int prio(char* string);

Stack* getToken(char* equ);
int isValid(Stack* myStack);
void toPostfix(Stack* myStack);
int calStack(Stack* myStack);

void printfStack(Stack* myStack);
void revStack(Stack* myStack);
void copyStack(Stack* to, Stack* from);


int main(void) {
	char* equ = malloc(sizeof(char*));
	Stack* equStack = CreateStack(50);

	printf("Arithmetic Expression : ");
	
	gets(equ);

	printf("Input : %s\n", equ);

	equStack = getToken(equ);

	revStack(equStack);

	if(isValid(equStack) != 0) return 0;

	toPostfix(equStack);

	revStack(equStack);

	printf("Post : ");
	printfStack(equStack);

	printf("\nResult : ");
	printf("%d\n", calStack(equStack));

	Destory(equStack);
	equStack = NULL;

	return 0;
}

int prio(char* string) {
	if (isdigit(string[0])) {
		return 0;
	}
	else {
		switch (string[0]) {
		case '+':
			return 1;
			break;
		case '-':
			return 1;
			break;
		case '%':
			return 3;
			break;
		case '*':
			return 3;
			break;
		case '(':
			return 5;
			break;
		case ')':
			return 6;
			break;
		default: return -1;
		}
	}
}


Stack* getToken(char* equ) {
	Stack* equStack = CreateStack(50);

	int i = 0, count = 0;
	int length = strlen(equ);

	for (; i < length; i++) {
		if (i == length - 1 && isdigit(equ[i])) {//i가 마지막까지 갔으면서 마지막 글자가 숫자라면
			Push(equStack, equ + count);
		}

		if (!isdigit(equ[i])) {//숫자가 아니라면
			char tmp = equ[i];
			equ[i] = NULL;

			if (i != count) {
				Push(equStack, equ + count);//equ+count부터 NULL까지 넣음
			}

			if (tmp != ' ') {//기호가 빈칸이 아니면
				char* oper = malloc(sizeof(char*));
				oper[0] = tmp;
				oper[1] = NULL;

				//printf("2 : %s PUSH\n", oper);
				Push(equStack, oper);
			}

			count = i + 1;
		}
	}

	return equStack;
}

int isValid(Stack* myStack) {
	//괄호 체크

	int test = 0;
	Stack* cStack = CreateStack(50);
	copyStack(cStack, myStack);

	Element e;

	while (!IsEmptyStack(cStack)) {
		Element e = Pop(cStack);
		if (prio(e) == 5) {
			test++;
		}
		else if (prio(e) == 6) {
			test--;
			if (test < 0) {
				goto A;
			}
		}
		else if (prio(e) == -1) {
			printf("Error : Check the symbol in the equation! Olny can use +-*%()");
			return 3;
		}
	}

	if (test != 0) {
	A:
		printf("Error : Check the pairs of Parenthesis!");
		return 1;
	}

	//이항 체크

	copyStack(cStack, myStack);

	revStack(cStack);

	if (prio(Top(cStack)) < 6 && prio(Top(cStack)) > 0) {//마지막이 연산자
		goto B;
	}

	revStack(cStack);

	e = Pop(cStack);
	Element e2;

	while (!IsEmptyStack(cStack)) {
		e2 = Pop(cStack);

		if (prio(e) > 0 && prio(e2) > 0) {//둘다 기호
			if (prio(e) < 5 && prio(e2) < 5) goto B;

			if (prio(e) == 5) {
				if (prio(e2) < 5 || prio(e2) == 6) {
				B:
					printf("Error : Check the binary expression!");
					return 2;
				}
			}

			if (prio(e2) == 6) {
				if (prio(e) < 6) {
					goto B;
				}
			}
		}
		else if (prio(e) == 0 && prio(e2) == 0) {//둘다 숫자
			goto B;
		}
		else {//둘 중 하나만 숫자
			if (prio(e2) == 5 || prio(e) == 6) goto B;
		}

		e = e2;
	}

	Destory(cStack);

	return 0;
}

void toPostfix(Stack* myStack) {
	Stack* postfix = CreateStack(50);
	Stack* operator = CreateStack(50);

	while (!IsEmptyStack(myStack)) {
	START:

		if (prio(Top(myStack)) == 0) {//숫자는 넣고본다
			Push(postfix, Pop(myStack));
		}
		else {//기호라면
			if (IsEmptyStack(operator)) {//operator가 비어있이면 일단 넣는다
				Push(operator, Pop(myStack));
				goto START;
			}

			if (prio(Top(myStack)) == 6) {// 닫는 괄호가 나오면 myStack에서 뺀 다음
				Pop(myStack);
				while (prio(Top(operator)) != 5) {//operator에서 여는 괄호가 나올 때까지 돌린다
					Push(postfix, Pop(operator));
				}
				Pop(operator);//여는괄호 제거
			}
			else {
				if (prio(Top(operator)) >= prio(Top(myStack))) {
					if (prio(Top(operator)) == 5) {
						Push(operator, Pop(myStack));
					}
					else {//(*+
						while (!IsEmptyStack(operator) && prio(Top(operator)) >= prio(Top(myStack))) {
							if (prio(Top(operator)) == 5) break;

							Push(postfix, Pop(operator));
						}
						Push(operator, Pop(myStack));
					}
				}
				else {//prio(Top(operator)) < prio(Top(myStack)
					Push(operator, Pop(myStack));
				}
			}
		}
	}

	while (!IsEmptyStack(operator)) {
		Push(postfix, Pop(operator));
	}

	copyStack(myStack, postfix);
}

int calStack(Stack* myStack) {
	Stack* tmp = CreateStack(50);

	while (!IsEmptyStack(myStack)) {
		if (prio(Top(myStack)) == 0) {
			Push(tmp, atoi(Pop(myStack)));
		}
		else {
			int n1 = Pop(tmp);
			int n2 = Pop(tmp);

			char* chartmp = Pop(myStack);
			switch (chartmp[0]) {
			case '+':
				Push(tmp, n2 + n1);
				break;
			case '-':
				Push(tmp, n2 - n1);
				break;
			case '*':
				Push(tmp, n2 * n1);
				break;
			case '%':
				if (n1 == 0) {
					printf("[E] 0으로 나눌 수 없습니다.");
				}
				Push(tmp, n2 % n1);
				break;
			}
		}
	}

	return Pop(tmp);
}


void printfStack(Stack* myStack) {
	Stack* tmp = CreateStack(50);
	copyStack(tmp, myStack);

	while (!IsEmptyStack(tmp)) {
		printf("%s ", Pop(tmp));
	}

	Destory(tmp);

	return;
}

void revStack(Stack* myStack) {
	Stack* tmp = CreateStack(50);
	Stack* tmp2 = CreateStack(50);

	while (!IsEmptyStack(myStack)) {
		Push(tmp, Pop(myStack));
	}

	while (!IsEmptyStack(tmp)) {
		Push(tmp2, Pop(tmp));
	}

	while (!IsEmptyStack(tmp2)) {
		Push(myStack, Pop(tmp2));
	}

	Destory(tmp);
	Destory(tmp2);
}

void copyStack(Stack* to, Stack* from) {
	Stack* tmp = CreateStack(50);

	while (!IsEmptyStack(from)) {
		Element e = Pop(from);
		Push(tmp, e);
		Push(to, e);
	}

	while (!IsEmptyStack(tmp)) {
		Push(from, Pop(tmp));
	}

	revStack(to);

	Destory(tmp);
}