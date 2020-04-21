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

struct node* search(struct node *root, int x)
{
    if(root == NULL || root->data == x)
        return root;

    else if(x > root->data)
        return search(root->right, x);

    else
        return search(root->left,x);
}

struct node* find_minimum(struct node *root)
{
    if(root == NULL)
        return NULL;

    else if(root->left != NULL)
        return find_minimum(root->left);

    return root;
}

struct node* delete(struct node *root, int x)
{
    if(root==NULL)
        return NULL;

    if (x > root->data)
        root->right = delete(root->right, x);

    else if(x < root->data)
        root->left = delete(root->left, x);

    else
    {
        if(root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }

        else if(root->left == NULL || root->right == NULL)
        {
            struct node *temp;

            if(root->left == NULL)
                temp = root->right;

            else
                temp = root->left;

            free(root);
            return temp;
        }

        else
        {
            struct node *temp = find_minimum(root->right);
            root->data = temp->data;
            root->right = delete(root->right, temp->data);
        }
    }
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
        root = (Node *) new;
        return root;
    }
    else
        add(root,new);

    return NULL;
}

// DLR
void preOrder(Node *root){
    if(root != NULL){
        printf("%d ",root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

//LDR
void inOrder(Node *root){
    if(root != NULL){
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

//LRD
void postOrder(Node *root){
    if(root != NULL){
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}


int main(void)
{
    int search_number = 35;

    /* CREATE THE TREE*/
    Node *root = createNode();
    Node *temp;
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

    printf("\n\nMinimum Data : %d\n",find_minimum(root)->data);

    if(search(root, search_number))
        printf("Founded Data : %d\n\n",search(root, 15)->data);

    else
        printf("%d Does not exists\n", search_number);

    delete(root, 5);
    delete(root, 5);
    delete(root, 16);
    delete(root, 14);

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
