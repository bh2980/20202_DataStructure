#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Complete Binary Tree이므로 임의로 노드 배정 불가

typedef char Element;

typedef struct tree {
	Element* data;
	struct tree* left;
	struct tree* right;
}TreeNode;

#include "Tree_Queue.h"

TreeNode* CreateTree(TreeNode* left, Element* data, TreeNode* right) {
	TreeNode* NewNode = (TreeNode*)malloc(sizeof(TreeNode));
	if (NewNode == NULL) {
		printf("할당 실패\n");
		return NULL;
	}

	NewNode->data = (Element*)malloc(sizeof(Element*));
	if (NewNode->data == NULL) {
		printf("할당 실패\n");
		return NULL;
	}

	NewNode->data = data;
	NewNode->left = left;
	NewNode->right = right;

	return NewNode;
}

int IsFullNode(TreeNode* node) {
	if (node->left != NULL && node->right != NULL) return 1;
	else return 0;
}

int IsNullNode(TreeNode* node) {
	if (node->left == NULL && node->right == NULL) return 1;
	else return 0;
}

void Insert(TreeNode* root, Element* data) {
	Queue* pQueue = CreateQueue(100);

	//큐에 노드를 넣는다
	EnQ(pQueue, root);

	while (1) {
		root = DeQ(pQueue);
		if (IsFullNode(root)) {//Queue에서 뺀 노드가 FullNode라면
			//자식들을 Queue에 넣는다.
			EnQ(pQueue, root->left);
			EnQ(pQueue, root->right);
		}
		else {//한칸이라도 비었다면 노드추가하고 while 탈출
			if (IsNullNode(root)) root->left = CreateTree(NULL, data, NULL);
			else root->right = CreateTree(NULL, data, NULL);

			break;
		}
	}
	//FullNode가 아니라면 그 노드에 노드를 추가한다.

	DestroyQ(pQueue);

	return;
}

void DestroyTree(TreeNode* root) {
	if (!IsNullNode(root)) {
		if(root->left != NULL) DestroyTree(root->left);
		if (root->right != NULL) DestroyTree(root->right);
		free(root);
		return;
	}
	else {
		free(root);
		return;
	}
}

int Search(TreeNode* root, Element* data) {
	Queue* pQueue = CreateQueue(100);

	EnQ(pQueue, root);

	while (1) {
		if (pQueue->cnt == 0) break;

		root = DeQ(pQueue);
		if (root->data == data) return 1;

		if (!IsNullNode(root)) {
			EnQ(pQueue, root->left);
			if (root->right) EnQ(pQueue, root->right);
		}
	}

	DestroyQ(pQueue);

	return 0;
}

void Inorder(TreeNode* root) {
	if (root == NULL) return;

	Inorder(root->left);
	printf("%c", root->data);
	Inorder(root->right);

	return;
}

void Preorder(TreeNode* root) {
	if (root == NULL) return;

	printf("%c", root->data);
	Preorder(root->left);
	Preorder(root->right);

	return;
}

void Postorder(TreeNode* root) {
	if (root == NULL) return;

	Postorder(root->left);
	Postorder(root->right);
	printf("%c", root->data);

	return;
}

void BreathFirst(TreeNode* root) {
	Queue* pQueue = CreateQueue(100);

	EnQ(pQueue, root);

	while (1) {
		if (pQueue->cnt == 0) break;

		root = DeQ(pQueue);
		printf("%c", root->data);

		if (!IsNullNode(root)) {
			EnQ(pQueue, root->left);
			if (root->right) EnQ(pQueue, root->right);
		}
	}

	DestroyQ(pQueue);

	return;
}