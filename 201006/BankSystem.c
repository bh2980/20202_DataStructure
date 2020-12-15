#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include "Queue_Array.h"
#include "Queue_Link.h"

int main(void) {
	Queue* pQ = CreateQueue(3);
	int n = 0;
	char customer[100];

	while (1) {
		printf("In (0), Out (1), exit (2) : ");
		scanf("%d", &n);
		getchar();
		switch (n) {
		case 0:
			printf("Customer : ");
			gets(customer);
			EnQ(pQ, customer);
			break;
		case 1:
			if (IsNullQ(pQ)) {
				printf("This queue is EMPTY.\n");
			}
			else {
				printf("Customer dequeued : %s\n", DeQ(pQ));
			}
			break;
		case 2:
			return 0;
			break;
		default:
			printf("올바른 입력이 아닙니다.\n");
		}

		printf("The current status of Queue : (");
		printfQ(pQ);
		printf(")\n\n");
	}

	return 0;
}