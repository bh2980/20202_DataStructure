#include <stdio.h>
#include "Queue.h"
#include "Stack.h"

char* toOcta(int n);
int toDemical(Queue* pQueue);
int search(Queue* pQueue, int n);

int main(void){

	Queue* pQueue = CreateQueue(100);
	int n = 0;

  while(1){
    printf("Insert(0), Search(1), Delete(2), Exit(3) : ");
    scanf("%d", &n);

    switch(n){
      case 0 :
        printf("\nDecimal : ");
        scanf("%d", &n);

        if(n<0){
          printf("\n음수는 변환할 수 없습니다.\n");
          return 0;
        }

        char* octan = (char*)malloc(sizeof(char*));
        EnQueue(pQueue, toOcta(n));

        break;

      case 1 :
        if(IsNullQueue(pQueue)){
          printf("\nThis Queue is NULL. Push the number first\n");
          return 0;
        }

        printf("\nDecimal : ");
        scanf("%d", &n);
        if(search(pQueue, n)) printf("\n%d [%s] is in Queue.\n", n, toOcta(n));
        else printf("\n%d [%s] is not in Queue.\n", n, toOcta(n));

        break;

      case 2 :
        if(IsNullQueue(pQueue)){
          printf("\nThis Queue is NULL. Push the number first\n");
          return 0;
        }

        printf("\n%d [%s] is dequeued\n", toDemical(pQueue), DeQueue(pQueue));
        break;

      case 3 :
      printf("\n");
        return 0;

      default:
        printf("잘못된 입력입니다.\n");
        return 0;
    }

    printf("Queue List : ");

    printQ(pQueue);
    printf("(%d)\n\n", pQueue->cnt);
  }

  DestroyQ(pQueue);
  pQueue = NULL;
  
	return 0;
}

char* toOcta(int n) {
	Stack* tmp = CreateStack(100);

	char* ch = (char*)malloc(sizeof(char*));
	*ch = NULL;

	do {
		switch(n%8){
		case 0 :
			Push(tmp, "0");
			break;
		case 1 :
			Push(tmp, "1");
			break;
		case 2 :
			Push(tmp, "2");
			break;
		case 3 :
			Push(tmp, "3");
			break;
		case 4 :
			Push(tmp, "4");
			break;
		case 5 :
			Push(tmp, "5");
			break;
		case 6 :
			Push(tmp, "6");
			break;
		case 7 :
			Push(tmp, "7");
			break;
		}

		n /= 8;

	} while (n != 0);

	while (!IsEmptyStack(tmp)) {
		strcat(ch, Pop(tmp));
	}

	Destory(tmp);
	tmp = NULL;

	return ch;
}

int toDemical(Queue* pQueue) {
	int n = 0;

	char ch[100] = { '\0' };
	strcpy(ch, QFront(pQueue));

  int j=1;

	for(int i = strlen(ch)-1; i >= 0; i--){
    n += j*(ch[i]-48);
    j *= 8;
  }

	return n;
}

int search(Queue* pQueue, int n){
  char* ch = toOcta(n);

  if(strcmp(ch, QFront(pQueue)) == 0) return 1;

  if(strcmp(ch, QRear(pQueue)) == 0) return 1;
  else return 0;
}