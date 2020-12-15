#include <stdio.h>
#include <stdlib.h>
#include "BinarySearchTree.h"

int main(void){
  char input[100];
  int n = -1;

  BSTree* bstree = createBSTree(NULL, compareString, printString);

  while(1){
    printf("Choose Add(0), Search(1), Delete(2), Stop(3) : ");
    scanf("%d", &n);
    getchar();

    switch(n){
      case 0 : //insert
      printf("Input : ");
      gets(input);
      Insert(bstree, input);

      break;

      case 1: //search the longest compareString
      Search(bstree);
      break;

      case 2 : //Delete
      break;

      case 3 : //Stop
      return 0;
      break;
    }

    printf("Traversal : ");
    Inorder(bstree);
    printf("\n\n");
  }

  return 0;
}