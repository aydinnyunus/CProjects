#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node *left;
    struct node *right;
    int data;
}Node;

Node *createNode(){
    Node *root = malloc(sizeof(Node));
    root->left = root->right = NULL;
    return root;
}
void add(Node *root, Node *p){
    if(root->data > p->data){
        if(root->left == NULL)
            root->left = p;
        else
            add(root->left, p);
    }
    else if(root->data < p->data){
        if(root->right == NULL)
            root->right = p;
        else
            add(root->right, p);
    }
}

Node *addNode(Node *root,int data){

    Node *new = malloc(sizeof(Node));
    new->left = new->right = NULL;
    new->data = data;

    if(root == NULL)
    {
        root = (Node *) add;
        return root;
    }
    else
        add(root,new);

    return NULL;
}

void preOrder(Node *root){
    if(root != NULL){
        printf("%d ",root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node *root){
    if(root != NULL){
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

void postOrder(Node *root){
    if(root != NULL){
        inOrder(root->left);
        inOrder(root->right);
        printf("%d ", root->data);
    }
}


int main(void)
{

    /* CREATE THE TREE*/
    Node *root = createNode();
    root->data = 14;
    addNode(root,4);
    addNode(root,15);
    addNode(root,3);
    addNode(root,9);
    addNode(root,7);
    addNode(root,9);
    addNode(root,5);
    addNode(root,4);
    addNode(root,5);
    addNode(root,14);
    addNode(root,18);
    addNode(root,16);
    addNode(root,20);
    addNode(root,17);

                /* PRINT THE TREE*/
    printf("PREORDER\n");
    printf("===================\n");
    preOrder(root);
    printf("\n===================");
    printf("\nPOSTORDER\n");
    printf("===================\n");
    postOrder(root);
    printf("\n===================");
    printf("\nINORDER\n");
    printf("===================\n");
    inOrder(root);
    printf("\n===================\n");


    return 0;
}