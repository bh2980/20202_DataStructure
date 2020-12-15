#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Binary_Tree.h"

int main(void) {
	int i = 0;
	char input[100] = { 0 };

	printf("Input a string : ");
	gets(input);

	TreeNode* root = CreateTree(NULL, input[i++], NULL);

	while (i < strlen(input)) {
		Insert(root, input[i++]);
	}

	printf("\nPre-order : ");
	Preorder(root);
	printf("\n\nIn-order : ");
	Inorder(root);
	printf("\n\nPost-order : ");
	Postorder(root);
	printf("\n\nBreadth First : ");
	BreathFirst(root);
	printf("\n");

	DestroyTree(root);

	return 0;
}