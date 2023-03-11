//Kamile Samusiovaite - AVL binary tree

#ifndef FILE_H
#define FILE_H

#define DATA_TYPE int //specified data type

//Binary tree structure
typedef struct Node{
    int element; 					
    struct Node *left;
    struct Node *right;
    int height;
} Node;

//Function prototypes
int height( Node *node);

int max(int firstMember, int secondMember);

int getBalance( Node* node);

Node* newNode(int element);

Node* rightRotate( Node* b);

Node* leftRotate( Node* a);

Node* insertElement( Node* node, int element);

Node* deleteNode( Node* node, int element);

void preOrder( Node* treeRoot);

Node* balanceTree(Node* node, int balance);

Node * minValueNode( Node* node);

#endif
