#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {
	char input[100], * inputp = input;
	int number[20], j = 0;

	printf("input :\n");

	for (int k = 0; k < 2; k++) {
		gets(input);

		number[0 + j] = atoi(input);

		for (int i = 0; i < strlen(input); i++) {
			/*한 번에 10개씩 추출, j값을 전역 변수로 설정해서 루프 탈출해도 기억하도록 유지
			총 20개를 채움.*/

			if (input[i] == ',') {
				j++;

				number[j] = atoi(input + i + 1);
			}

			//한 줄 당 최대 10개만 인식
			if (j == 9 || j == 19) break;
		}
		j++;
	}

	if (j != 20) {//j가 20이 아니면 개수 부족 종료
		printf("You should input 20 numbers in total\n");
		return 1;
	}

	for (int i = 1; i < 20; i++) {//오름차순 체크
		if (number[i - 1] > number[i] && i != 10) {
			printf("The input numbers are not in ascending order\n");
			return 2;
		}
	}

	for (int i = 0; i < 20; i++) {//전체 오름차순 배열
		for (int j = i; j < 20; j++) {

			if (number[i] > number[j]) {
				int temp = number[i];

				number[i] = number[j];
				number[j] = temp;
			}
		}
	}

	printf("output :\n");
	for (int i = 0; i < 20; i++) {
		//출력할 때 같은 숫자가 존재하면 빼기
		if (number[i] != number[i + 1]) {
			if (i == 19) printf("%d", number[i]);
			else printf("%d, ", number[i]);
		}
	}
	printf("\n");

	return 0;
}