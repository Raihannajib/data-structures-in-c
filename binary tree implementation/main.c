#include <stdio.h>
#include <stdlib.h>
#define COUNT 10

typedef struct Node{
    int data;
    struct Node *left;
    struct Node *right;
}Node;

Node* newNode( int data ){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

Node* insert(Node* root,int K){

    if( root == NULL){
        root = newNode(K);
        return root;
    }
    if(K < root->data){
        root->left = insert(root->left, K);
    }else if(K > root->data){
        root->right = insert(root->right,K);
    }
    return root;
}

void showPrefix(Node* tree){
    if(tree != NULL){
        printf("%d\n",tree->data);
        showPrefix(tree->left);
        showPrefix(tree->right);
    }
}

void showPostfix(Node* tree){
    if(tree != NULL){
        showPostfix(tree->left);
        showPostfix(tree->right);
        printf("%d\n",tree->data);
    }
}

void showInfix(Node* tree){
    int Count =0;
    if(tree != NULL){

        Count+=COUNT;
        showInfix(tree->left);
        for (int i = COUNT; i <Count ; i++) {
            printf(" "
                   "");
        }
        printf("%d\n",tree->data);
        showInfix(tree->right);
    }
}


Node* findMin(Node* tree) {
    if (tree == NULL){
        return tree;
    }else if(tree->left != NULL){
        return findMin(tree->left);
    }
    return tree;
}

int findMax(Node* tree){
    if(tree->right == NULL){
        return tree->data;
    }else{
        return findMax(tree->right);
    }
}



int search(Node* root , int data){
    if(root == NULL){
        return -1;
    }else if(data == root->data){
        return 1;
    }else if (data < root->data){
        return  search(root->left,data) ;
    }else{
        return search(root->right,data);
    }

}

void liberer(Node* tree){
    if(tree != NULL ){
        liberer(tree->left);
        liberer(tree->right);
        free(tree);
    }
    tree = NULL;
}

Node* delete(Node* tree ,int data ){
    if(tree == NULL){
        return tree;
    }else if(tree->right == NULL && tree->left == NULL){
        free(tree);
        return NULL;
    }else if(tree->left == NULL || tree->right == NULL){
        Node* temp = (Node*)malloc(sizeof(Node));
        temp->data = tree->data;
        if(tree->left == NULL){
            temp = tree->right;
        }else{
            temp = tree->left;
        }
        free(tree);
        return temp;
    }else{
        Node* tempp = findMin(tree->right);
        tree->data = tempp->data;
        tree->right = delete(tree->right,tempp->data);
    }
    return tree;
}



int main() {

    Node* tree = NULL;
    int nodesNum = 0;
    int x =0;
    int X=0;
    int i =0;

    printf("how elements you wanna insert ?\n");
    scanf("%d",&nodesNum);
    for (int j = 0; j < nodesNum ; ++j) {
        printf("element ?\n");
        scanf("%d",&X);
        tree = insert(tree,X);
    }


    //showPrefix(tree);
   // printf("\n");
    showInfix(tree);
    printf("\n");
    //showPostfix(tree);

    printf(" element you wanna find ?\n");
    scanf("%d",&x);
    i = search(tree,2);
    switch(i){
        case 1:
            printf("fount");
            break;
        case -1:
            printf("not found");
    }

    liberer(tree);


    return 0;
}