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
			/*�� ���� 10���� ����, j���� ���� ������ �����ؼ� ���� Ż���ص� ����ϵ��� ����
			�� 20���� ä��.*/

			if (input[i] == ',') {
				j++;

				number[j] = atoi(input + i + 1);
			}

			//�� �� �� �ִ� 10���� �ν�
			if (j == 9 || j == 19) break;
		}
		j++;
	}

	if (j != 20) {//j�� 20�� �ƴϸ� ���� ���� ����
		printf("You should input 20 numbers in total\n");
		return 1;
	}

	for (int i = 1; i < 20; i++) {//�������� üũ
		if (number[i - 1] > number[i] && i != 10) {
			printf("The input numbers are not in ascending order\n");
			return 2;
		}
	}

	for (int i = 0; i < 20; i++) {//��ü �������� �迭
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
		//����� �� ���� ���ڰ� �����ϸ� ����
		if (number[i] != number[i + 1]) {
			if (i == 19) printf("%d", number[i]);
			else printf("%d, ", number[i]);
		}
	}
	printf("\n");

	return 0;
}