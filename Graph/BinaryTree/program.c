//Kamile Samusiovaite - AVL binary tree
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "file.c"

//Main function with menu
int main(){
	struct Node *treeRoot = NULL;
	printf("Hello! Please select a number from the list: \n \n");
	int runningProgram = 1, count = 0, element;
	char choice;

	while(runningProgram){
		printf("Menu: \n");
		printf("1. Create a binary tree. \n");
		printf("2. Print a binary tree. \n");
		printf("3. Insert a new element in the binary tree. \n");
		printf("4. Delete an element from the binary tree. \n");
		printf("5. Find out how many leaves a binary tree has. \n");
		printf("6. Destroy the binary tree. \n");
		printf("7. Check if the tree is destroyed. \n");
		printf("8. Complete the program. \n\n");
		scanf(" %c", &choice);
		
		switch(choice){
			case '1':
				printf("Please enter how many elements will be in the binary tree? \n");
				scanf("%d", &count);
				for (int i = 0; i < count; ++i){
					printf("Please enter %d element.\n", i + 1);
					scanf("%d", &element);
					treeRoot = insertElement(treeRoot, element);
				}
				break;	
				
			case '2': 
				printf("Preorder traversal of the constructed AVL tree is \n");
				preOrder(treeRoot);
				printf("\n\n");
				break;
			
			case '3':
				printf("Please enter a new element to insert into the binary tree: \n");
				scanf("%d", &element);
				treeRoot = insertElement(treeRoot, element);
				++count;
				break;
				
			case '4':
				printf("Please enter the element you want to delete from the binary tree: \n");
				scanf("%d", &element);
				treeRoot = deleteNode(treeRoot, element);
				--count;
				break;
			
			case '5':
				printf("The number of leaves is: %d", count);
				printf("\n\n");
				break;
				
			case '6':	
				treeRoot = NULL; 
				count = 0;
				break; 
			
			case '7':
				if(treeRoot == NULL){
					printf("The tree is destroyed. \n");
				}
				else{
					printf("The tree exist. \n");
				}
				printf("\n\n");
				break;
				
			case '8':
				runningProgram = 0;
				break;
	
			default:
				printf("Bad input.");
				break;
		}
	}
	printf("The program has successfully completed its work. \n");

	return 0;
 
}
