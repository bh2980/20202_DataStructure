#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[5];
	int age, math, english, history;
} student;

student* sort_student();
void print_student();

int main(void) {

	FILE* fp;
	int option, cnt=0;
	student * stp = NULL;
	char filename[15];

	printf("==============================\n");
	while (1) {

		printf("1) Insert\n");
		printf("2) Sort\n");
		printf("3) Quit\n");
		printf("Select a menu : ");
		scanf("%d", &option);
		while (getchar() != '\n');
		

		switch (option) {
		case 1:
			stp = malloc(sizeof(student));
			option = 0;

			printf("File name : ");
			scanf("%s", &filename);

			if ((fp = fopen(filename, "r")) == NULL) {
				printf("Result : There is no %s in the folder. Problem terminates\n", &filename);
				printf("==============================\n");
				return 1; //파일 없음 에러
			}

			while (1) {
				int check = 0;

				check = fscanf(fp, "%s %d %d %d %d", (stp + option)->name, &(stp + option)->age, &(stp + option)->math, &(stp + option)->english, &(stp + option)->history);

				if (check == 0 || check == EOF) break;

				if (((stp + option)->age) <= 0) {
					printf("Reuslt : The age cannot be a negative number. Problem terminates\n");
					printf("==============================\n");
					return 2; //음수 나이
				}
				else if ((stp + option)->math < 0 || (stp + option)->math > 100
					|| (stp + option)->english < 0 || (stp + option)->english > 100
					|| (stp + option)->history < 0 || (stp + option)->history > 100) {
					printf("Reuslt : The score of a subject cannot be under 0 or over 100. Problem terminates\n");
					printf("==============================\n");
					return 3; //점수 에러
				}

				option++;
				stp = realloc(stp, sizeof(student) * (option + 1));
			}

			cnt = option;

			fclose(fp);
			print_student(stp, 1, cnt);
			printf("\n");

			break;

		case 2:
			if (stp == NULL) {
				printf("Result : There is no data to be sorted. Problem terminates\n");
				printf("==============================\n");
				return 4;//정렬 데이터 없음
			}

			printf("1) Name\n");
			printf("2) Age\n");
			printf("3) Math\n");
			printf("4) English\n");
			printf("5) History\n");
			printf("Choose the field to sort by : ");
			scanf("%d", &option);

			print_student(sort_student(stp, option, cnt), option, cnt);
			printf("\n");
			break;

		case 3:
			free(stp);
			printf("\n=============================");
			return 0;
		}
	}
}

student * sort_student(student* stp, int sort, int cnt) {
	student tmp, *cpy = malloc(sizeof(student)*cnt);

	for (int i = 0; i < cnt; i++) {
		*(cpy + i) = *(stp + i);
	}

	switch (sort) {
	case 1://name
		for (int i = 0; i < cnt; i++) {
			for (int j = 0; j < cnt; j++) {
				if (strcmp((cpy + i)->name, (cpy + j)->name) < 0) {
					tmp = *(cpy + i);
					*(cpy + i) = *(cpy + j);
					*(cpy + j) = tmp;
				};
			}
		}
		return(cpy);
		break;

	case 2://age
		for (int i = 0; i < cnt; i++) {
			for (int j = 0; j < cnt; j++) {
				if ((cpy + i)->age < (cpy + j)->age) {
					tmp = *(cpy + i);
					*(cpy + i) = *(cpy + j);
					*(cpy + j) = tmp;
				};
			}
		}
		return(cpy);
		break;

	case 3://math
		for (int i = 0; i < cnt; i++) {
			for (int j = 0; j < cnt; j++) {
				if ((cpy + i)->math < (cpy + j)->math) {
					tmp = *(cpy + i);
					*(cpy + i) = *(cpy + j);
					*(cpy + j) = tmp;
				};
			}
		}
		return(cpy);
		break;

	case 4://english
		for (int i = 0; i < cnt; i++) {
			for (int j = 0; j < cnt; j++) {
				if ((cpy + i)->english < (cpy + j)->english) {
					tmp = *(cpy + i);
					*(cpy + i) = *(cpy + j);
					*(cpy + j) = tmp;
				};
			}
		}
		return(cpy);
		break;
	case 5://history
		for (int i = 0; i < cnt; i++) {
			for (int j = 0; j < cnt; j++) {
				if ((cpy + i)->history < (cpy + j)->history) {
					tmp = *(cpy + i);
					*(cpy + i) = *(cpy + j);
					*(cpy + j) = tmp;
				};
			}
		}
		return(cpy);
		break;
	default : printf("You can choose in the number of the list.\n");
	}
}

void print_student(student* stp, int sort, int cnt) {

	switch (sort) {
	case 1:
		printf("Result : \nNo Name Age Math English History\n");
		for (int i = 0; i < cnt; i++) {
			printf("%d %s %d %d %d %d\n", i+1, (stp + i)->name, (stp + i)->age, (stp + i)->math, (stp + i)->english, (stp + i)->history);
		}
		break;
	case 2:
		printf("Result : \nNo Age Name Math English History\n");
		for (int i = 0; i < cnt; i++) {
			printf("%d %d %s %d %d %d\n",i+1, (stp + i)->age, (stp + i)->name, (stp + i)->math, (stp + i)->english, (stp + i)->history);
		}
		break;
	case 3:
		printf("Result : \nNo Math Name Age English History\n");
		for (int i = 0; i < cnt; i++) {
			printf("%d %d %s %d %d %d\n", i + 1, (stp + i)->math, (stp + i)->name, (stp + i)->age, (stp + i)->english, (stp + i)->history);
		}
		break;
	case 4:
		printf("Result : \nNo English Name Age Math History\n");
		for (int i = 0; i < cnt; i++) {
			printf("%d %d %s %d %d %d\n", i+1, (stp + i)->english, (stp + i)->name, (stp + i)->age, (stp + i)->math, (stp + i)->history);
		}
		break;
	case 5:
		printf("Result : \nNo History Name Age Math English\n");
		for (int i = 0; i < cnt; i++) {
			printf("%d %d %s %d %d %d\n", i+1, (stp + i)->history, (stp + i)->name, (stp + i)->age, (stp + i)->math, (stp + i)->english);
		}
		break;
	}
}