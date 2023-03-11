//Kamile Samusiovaite - AVL binary tree
#include <stdio.h>
#include <stdlib.h>
#include "file.h"

//A function that calculates the height of a binary tree
int height(Node *node){
    if (node != NULL){
    	return (*node).height;
	}	
    return 0;
}
 
//A function that finds the maximum of two integers
int max(int firstMember, int secondMember){
	if(firstMember > secondMember){
		return firstMember;
	}
    return secondMember;
}
 
//Function which get balance factor of node node
int getBalance(Node *node){
	int balance; 
    if (node != NULL){
    	balance = height((*node).left) - height((*node).right);
    	return balance;
	}
	return 0;
}

//A function that assigns initial values
Node* newNode(int element){
    Node* node = (Node*) malloc(sizeof(Node));
    (*node).element = element;
    (*node).left = NULL;
    (*node).right = NULL;
    (*node).height = 1;  
    return node;
}
 
/*A function to right rotate subtree rooted with b.
The function performs rotation, renews height 
and returns a new root.*/
Node *rightRotate(Node *b){
    Node *a = (*b).left;
    Node *T2 = (*a).right;
 
    (*a).right = b;
    (*b).left = T2;
 
    (*b).height = max(height((*b).left), height((*b).right))+1;
    (*a).height = max(height((*a).left), height((*a).right))+1;
 
    return a;
}
 

/*A function to left rotate subtree rooted with a.
The function performs rotation, renews height 
and returns a new root.*/
Node *leftRotate(Node *a){
    Node *b = (*a).right;
    Node *T2 = (*b).left;
 
    (*b).left = a;
    (*a).right = T2;
 
    (*a).height = max(height((*a).left), height((*a).right)) + 1;
    (*b).height = max(height((*b).left), height((*b).right)) + 1;
 
    return b;
}

//The recursive function is for inserting a new element.
Node* insertElement(Node* node, int element){
    if (node == NULL){
    	return(newNode(element));
	}
    if (element < (*node).element){
    	(*node).left  = insertElement((*node).left, element);
	}    
    else if (element > (*node).element){
    	(*node).right = insertElement((*node).right, element);
	} 
    else{
		return node; //No duplication of the same elements is allowed.
  	}
 
    (*node).height = max(height((*node).left), height((*node).right)) + 1;
 
    //We get a new balance so that the tree does not go in one direction
    int balance = getBalance(node);
    
    return balanceTree(node, balance);
}

//A function that finds the smallest value in a tree
Node* minValueNode(Node* node){
    Node* current = node;
 
    while((*current).left != NULL){
    	current = (*current).left;
	}

    return current;
}

//A recursive function that allows you to remove the desired item
Node* deleteNode(Node* node, int element){
    if (node == NULL){
    	return node;
	}
	//Checks which side contains the item you want to remove
    if ( element < (*node).element ){
    	(*node).left = deleteNode((*node).left, element);
	}

    else if(element > (*node).element){
    	(*node).right = deleteNode((*node).right, element);
	}
        
    else{
        if(((*node).left == NULL) || ((*node).right == NULL)){
        	Node *temp;
        	
 			if((*node).left){
 				temp = (*node).left;
			}
			else{
				temp = (*node).right;
			}
 			
            if (temp == NULL){
                temp = node;
                node = NULL;
            }
            
            else{
            	*node = *temp; 
            	free(temp);            
        	}
        }
        else{
            Node* temp = minValueNode((*node).right);
            (*node).element = (*temp).element;
            (*node).right = deleteNode((*node).right, (*temp).element);
        }
    }
 
    if (node == NULL){
    	return node;
	}

    (*node).height = max(height((*node).left), height((*node).right)) + 1;
  	//We get a new balance so that the tree does not go in one direction
    int balance = getBalance(node);
 	
 	return balanceTree(node, balance);
}

//A function that balances a tree in 4 ways
Node* balanceTree(Node* node, int balance){
    // Left Left Case
    if (balance > 1 && getBalance((*node).left) >= 0){
    	return rightRotate(node);
	}
        
    // Left Right Case
    if (balance > 1 && getBalance((*node).left) < 0){
        (*node).left =  leftRotate((*node).left);
        return rightRotate(node);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance((*node).right) <= 0){
    	 return leftRotate(node);
	}
       
    // Right Left Case
    if (balance < -1 && getBalance((*node).right) > 0){
        (*node).right = rightRotate((*node).right);
        return leftRotate(node);
    }
 
    return node;
}

//Function for tree printing
void preOrder(Node *treeRoot){
    if(treeRoot != NULL){
        printf("%d ", (*treeRoot).element);
        preOrder((*treeRoot).left);
        preOrder((*treeRoot).right);
    }
}

