#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "List_Array.h"
//#include "List_Link.h"

int main(void) {
	
	List* pList = createList(100);
	int n;

	while (1) {
		printf("In (0), Search(1), Out(2), Exit(3) : ");
		scanf("%d", &n);
		while (getchar() != '\n');

		switch (n) {
		case 0:
			printf("In : ");
			scanf("%d", &n);
			while (getchar() != '\n');
			

			pushList(pList, n);
			break;
		case 1:
			if (isNullList(pList)) {
				printf("The list is Null.\n");
				break;
			}

			printf("Search : ");
			scanf("%d", &n);
			while (getchar() != '\n');
			

			if (search(pList, n)) printf("My list has %d.\n", n);
			else printf("My list does not have %d.\n", n);

			break;
		case 2:
			if (isNullList(pList)) {
				printf("The list is Null.\n");
				break;
			}

			printf("Out : ");
			scanf("%d", &n);
			while (getchar() != '\n');
			

			Element e = popList(pList, n);

			if (e != NULL) printf("%d is removed.\n", e);
			else printf("My list does not have %d. Couldn't delete it\n", n);

			break;
		case 3:
			destroyList(pList);

			return 0;
			break;
		default: printf("잘못된 입력입니다.\n");
		}

		printf("\nThe current status of List : ");
		printfList(pList);

		printf("\n");
	}

	return 0;
	
}