#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void* Element;

typedef struct tree {
	Element data;
	struct tree* left;
	struct tree* right;
}TreeNode;

typedef struct bst{
  int (*compare)(Element a, Element b);
  int (*print)(Element a);
  TreeNode* root;
  int nodenum;
}BSTree;

#include "Tree_Queue.h"

int compareString(Element a, Element b){
  if(strlen(a) == strlen(b)){//���̰� ���� ���
    return 0;
  }
  else if(strlen(a) > strlen(b)){//a�� b���� ���̰� ū ���
    return 1;
  }
  else return -1; //a�� b���� ���̰� ª�� ���
}

void printString(Element a){
  printf("%s ", a);
}

TreeNode* CreateTree(TreeNode* left, Element data, TreeNode* right) {
	TreeNode* NewNode = (TreeNode*)malloc(sizeof(TreeNode));
	if (NewNode == NULL) {
		printf("�Ҵ� ����\n");
		return NULL;
	}

	NewNode->data = (Element)malloc(sizeof(Element));
	if (NewNode->data == NULL) {
		printf("�Ҵ� ����\n");
		return NULL;
	}

	NewNode->data = data;
	NewNode->left = left;
	NewNode->right = right;

	return NewNode;
}

BSTree* createBSTree(TreeNode* root, int (*compare)(Element a, Element b), int (*print)(Element a)){
  BSTree* NewBST = (BSTree*)malloc(sizeof(BSTree));
  if(!NewBST){
    printf("malloc failed\n");
    return NULL;
  }

  NewBST->compare = compare;
  NewBST->print = print;
  NewBST->root = CreateTree(NULL, root, NULL);
  NewBST->nodenum = 0;

  return NewBST;
}

int IsFullNode(TreeNode* node) {
	if (node->left != NULL && node->right != NULL) return 1;
	else return 0;
}

int IsNullNode(TreeNode* node) {
	if (node->left == NULL && node->right == NULL) return 1;
	else return 0;
}

void InsertRe(TreeNode* root, Element data, int (*compare)(Element a, Element b)){
  int swit = compare(root->data, data);

  switch(swit){
    case 0: //���� ��
    printf("The same length string is already included\n");
    break;

    case 1:
    //root->data�� data���� ū ���
    //printf("%s > %s", root->data, data);
    if(!root->left){
      root->left = CreateTree(NULL, data, NULL);
    }
    else InsertRe(root->left, data, compare);
    break;

    case -1:
    //printf("%s < %s", root->data, data);
    if(!root->right) {
      root->right = CreateTree(NULL, data, NULL);
    }
    else InsertRe(root->right, data, compare);
    break;
  }

  return;
}

void Insert(BSTree* bst, Element data) {
  Element* tmp = (Element*)malloc(sizeof(Element));
  strcpy(tmp, data);

  if(bst->nodenum == 0){
    bst->root->data = tmp;
  }
  else {
    InsertRe(bst->root, tmp, bst->compare);
  }

  bst->nodenum++;

	return;
}

void DestroyTree(BSTree* bst) {
  TreeNode* root = bst->root;

	if (!IsNullNode(root)) {
		if (root->left != NULL) DestroyTree(root->left);
		if (root->right != NULL) DestroyTree(root->right);
		free(root);
	}
	else {
		free(root);
	}

  free(bst);

  return;
}

int Search(BSTree* bst){
  //���� �� �༮�� ����Ʈ
  //root->right�� ���� �� ���� ������.
  //�װ� ����Ʈ
  TreeNode* root = bst->root;

  while(root->right){
    root = root->right;
  }

  printf("The longest stirng : ");
  bst->print(root->data);
  printf("\n");
  
}

void inorderal(TreeNode* root, int (*print)(Element a)) {
	if (root == NULL) return;

	inorderal(root->left, print);
	print(root->data);
	inorderal(root->right, print);

	return;
}

void Inorder(BSTree* bst){
  inorderal(bst->root, bst->print);

  return;
}