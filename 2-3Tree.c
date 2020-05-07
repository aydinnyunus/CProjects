#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CAP 3
#define MAX(a, b) (((a)>(b))?(a):(b)) // If A>B return A else return B

typedef struct node {
    struct node *left;
    struct node *right;
    struct node *middle;
    int height;
    char *data[CAP];
} Node;


int findHeight(Node *root) {
    if (root == NULL)
        return -1;
    return root->height;

}

int search(Node *root, int data) {
    if (root == NULL) {
        printf("%d is not founded\n", data);
        return data;
    }
    if (root->data[0] && root->data[1]) {
        if ((char *) data <= root->data[0]) {
            if ((char *) data == root->data[0] || (char *) data == root->data[1]) {
                printf("%d is founded\n", data);
                return data;
            }
            search(root->left, data);
        } else if ((char *) data >= root->data[0] && (char *) data < root->data[1]) {
            if ((char *) data == root->data[0] || (char *) data == root->data[1]) {
                printf("%d is founded\n", data);
                return data;
            }
            search(root->middle, data);
        } else if ((char *) data >= root->data[1]) {
            if ((char *) data == root->data[0] || (char *) data == root->data[1]) {
                printf("%d is founded\n", data);
                return data;
            }
            search(root->right, data);
        } else {
            printf("%d is founded\n", data);
            return data;
        }
    } else if (root->data[0] && root->data[1] == NULL) {
        if ((char *) data <= root->data[0]) {
            if ((char *) data == root->data[0]) {
                printf("%d is founded\n", data);
                return data;
            }
            search(root->left, data);
        } else if ((char *) data >= root->data[1]) {
            if ((char *) data == root->data[0]) {
                printf("%d is founded\n", data);
                return data;
            }
            search(root->right, data);
        } else {
            {
                printf("%d is founded\n", data);
                return data;
            }
        }
    } else
        return data;
}

Node *searchNode(Node *root, int data) {
    if (root == NULL) {
        printf("%d is not founded\n", data);
        return root;
    }
    if (root->data[0] && root->data[1]) {
        if ((char *) data < root->data[0]) {
            if ((char *) data == root->data[0] || (char *) data == root->data[1]) {
                printf("%d is founded\n", data);
                return root;
            }
            search(root->left, data);
        } else if ((char *) data > root->data[0] && (char *) data < root->data[1]) {
            if ((char *) data == root->data[0] || (char *) data == root->data[1]) {
                printf("%d is founded\n", data);
                return root;
            }
            search(root->middle, data);
        } else if ((char *) data > root->data[1]) {
            if ((char *) data == root->data[0] || (char *) data == root->data[1]) {
                printf("%d is founded\n", data);
                return root;
            }
            search(root->right, data);
        } else {
            printf("%d is founded\n", data);
            return root;
        }
    } else if (root->data[0] && root->data[1] == NULL) {
        if ((char *) data < root->data[0]) {
            if ((char *) data == root->data[0]) {
                printf("%d is founded\n", data);
                return root;
            }
            search(root->left, data);
        } else if ((char *) data > root->data[1]) {
            if ((char *) data == root->data[0]) {
                printf("%d is founded\n", data);
                return root;
            }
            search(root->right, data);
        } else {
            {
                printf("%d is founded\n", data);
                return root;
            }
        }
    } else
        return root;
    return root;
}

int diffRNL(Node *root) {
    if (root == NULL)
        return 0;
    return findHeight(root->left) - findHeight(root->right);
}

Node *createNode(int data) {
    int i = 0;
    Node *root = malloc(sizeof(Node));
    root->left = root->middle = root->right = NULL;

    for (; i < 3; i++) {
        root->data[i] = NULL;
    }

    root->data[CAP - 3] = (char *) data;
    root->height = 1;

    return root;
}

Node *sortNode(Node *root) {
    int a, i, j;
    if (root->data[0] && root->data[1] && root->data[2] &&
        ((root->data[0] > root->data[1]) || (root->data[1] > root->data[2])))
        for (i = 0; i < 3; ++i) {

            for (j = i + 1; j < 3; ++j) {

                if (root->data[i] > root->data[j]) {
                    a = (int) root->data[i];
                    root->data[i] = root->data[j];
                    root->data[j] = (char *) a;

                }

            }

        }
    else if (root->data[0] && root->data[1] && root->data[2] == NULL && root->data[0] > root->data[1])
        for (i = 0; i < 2; ++i) {

            for (j = i + 1; j < 2; ++j) {

                if (root->data[i] > root->data[j]) {
                    a = (int) root->data[i];
                    root->data[i] = root->data[j];
                    root->data[j] = (char *) a;

                }

            }

        }

    return root;
}

Node *splitNode(Node *root) {
    
    if (root->data[0] != NULL && root->data[1] != NULL && root->data[2] != NULL) {
        Node *temp, *temp1, *temp2;
        temp = createNode((int) root->data[1]);
        temp1 = createNode((int) root->data[2]);
        temp2 = createNode((int) root->data[0]);
        temp->right = temp1;
        temp->left = temp2;
        temp->right->right = root->right;
        temp->left->left = root->left;
        temp->height = MAX(findHeight(root->left), findHeight(root->right)) + 1;


        return temp;
    }
    return root;
}
Node *checkNodes(Node *root) {
    if (diffRNL(root) >= 1 || diffRNL(root) <= -1) {
        Node *tR = root;
        Node *tL = root;
        while (tR->right) {
            tR = tR->right;
            if (tR->data[0] != NULL && tR->data[1] == NULL) {
                if (diffRNL(root) >= 1) {
                    if (root->data[0] != NULL && root->data[1] == NULL) {
                        if(tR->left->data[0] != NULL && tR->left->data[1] == NULL && root->data[0] < tR->left->data[0] && root->data[1] > tR->left->data[0]){
                            if(root->middle->data[0] == NULL)
                                root->middle->data[0] = tR->left->data[0];

                            else if(root->middle->data[0] != NULL && root->middle->data[1] == NULL){
                                root->middle->data[1] = tR->left->data[0];
                                root->middle = sortNode(root->middle);
                            }
                        }
                        else if(tR->left->data[0] != NULL && tR->left->data[1] != NULL && root->data[0] < tR->left->data[1] && root->data[1] > tR->left->data[1]){
                            if(root->middle->data[0] == NULL)
                                root->middle->data[0] = tR->left->data[1];

                            else if(root->middle->data[0] != NULL && root->middle->data[1] == NULL){
                                root->middle->data[1] = tR->left->data[1];
                                root->middle = sortNode(root->middle);
                            }
                        }
                        root->data[1] = tR->data[0];
                        root->right = tR->right;
                        if (root->right->data[0] != NULL && root->right->data[1] == NULL) {
                            root->right->data[1] = tR->left->data[0];
                            root->right = sortNode(root->right);
                        }
                    } else if (root->data[0] != NULL && root->data[1] != NULL && root->data[2] == NULL) {
                        if(tL->right->data[0] != NULL && tL->right->data[1] != NULL && root->data[0] < tL->right->data[0] && root->data[1] > tL->right->data[0]){
                            if(root->middle->data[0] == NULL)
                                root->middle->data[0] = tL->data[0];

                            else if(root->middle->data[0] != NULL && root->middle->data[1] == NULL){
                                root->middle->data[1] = tL->data[0];
                                root->middle = sortNode(root->middle);
                            }
                        }
                        else if(tL->left->data[0] != NULL && tL->left->data[1] != NULL && root->data[0] < tL->left->data[1] && root->data[1] > tL->left->data[1]){
                            if(root->middle->data[0] == NULL)
                                root->middle->data[0] = tL->left->data[1];

                            else if(root->middle->data[0] != NULL && root->middle->data[1] == NULL){
                                root->middle->data[1] = tL->data[1];
                                root->middle = sortNode(root->middle);
                            }
                        }
                        root->data[2] = tR->data[0];
                        root = sortNode(root);
                        root = splitNode(root);
                    }
                }
            } else if (tR->data[0] != NULL && tR->data[1] != NULL) {
                if(tR->data[0] != NULL && tR->data[1] != NULL && root->data[0] < tR->data[0] && root->data[1] > tR->data[0]){
                    if(root->middle == NULL){
                        root->middle = createNode((int) tR->data[0]);
                        tR->data[0] = tR->data[1];
                        tR->data[1] = NULL;

                    }

                    else if(root->middle->data[0] != NULL && root->middle->data[1] == NULL){
                        root->middle->data[1] = tR->data[0];
                        root->middle = sortNode(root->middle);
                    }
                }
                else if(tR->data[0] != NULL && tR->data[1] != NULL && root->data[0] < tR->data[1] && root->data[1] > tR->data[1]){
                    if(root->middle->data[0] == NULL)
                        root->middle->data[0] = tR->data[1];

                    else if(root->middle->data[0] != NULL && root->middle->data[1] == NULL){
                        root->middle->data[1] = tR->data[1];
                        root->middle = sortNode(root->middle);
                    }
                }
                if(root->right->right)
                    root->right->data[1] = root->right->right->data[0];

            }

        }

        while (tL->left) {
            tL = tL->left;

            if (tL->data[0] != NULL && tL->data[1] == NULL) {
                if (diffRNL(root) <= -1) {
                    if (root->data[0] != NULL && root->data[1] == NULL) {
                        if(tL->data[0] != NULL && tL->data[1] != NULL && root->data[0] < tL->data[0] && root->data[1] > tL->data[0]){
                            if(root->middle->data[0] == NULL)
                                root->middle->data[0] = tL->data[0];

                            else if(root->middle->data[0] != NULL && root->middle->data[1] == NULL){
                                root->middle->data[1] = tL->data[0];
                                root->middle = sortNode(root->middle);
                            }
                        }
                        else if(tL->data[0] != NULL && tL->data[1] != NULL && root->data[0] < tL->data[1] && root->data[1] > tL->data[1]){
                            if(root->middle->data[0] == NULL)
                                root->middle->data[0] = tL->data[1];

                            else if(root->middle->data[0] != NULL && root->middle->data[1] == NULL){
                                root->middle->data[1] = tL->data[1];
                                root->middle = sortNode(root->middle);
                            }
                        }
                        root->data[1] = tL->data[0];
                        root->left = tL->left;
                        if(root->left)
                            if (root->left->data[0] != NULL && root->left->data[1] == NULL) {
                                root->left->data[1] = tL->right->data[0];
                                root->left = sortNode(root->left);
                            }
                    } else if (root->data[0] != NULL && root->data[1] != NULL && root->data[2] == NULL) {
                        if(tR->data[0] != NULL && tR->data[1] == NULL)
                            if(root->middle)
                                if(root->middle->data[0] != NULL && root->middle->data[1] == NULL){
                                    tR->data[1] = root->middle->data[0];
                                    tR = sortNode(tR);
                                    root->middle = NULL;
                                    if(root->data[0] != NULL && root->data[1] != NULL && root->data[2] == NULL)
                                        if(tR->data[0] != NULL && tR->data[1] != NULL && tR->data[2] == NULL){
                                            tR->data[2] = root->data[1];
                                            root->data[1] = NULL;
                                            tR = sortNode(tR);
                                            tR = splitNode(tR);
                                            root->right = tR;
                                            return root;
                                        }
                                }
                        if(diffRNL(root) > 1 || diffRNL(root) < -1)
                            if(root->data[2])
                                root->data[2] = tL->data[0];
                                root = sortNode(root);
                                root = splitNode(root);
                    }
                }
            } else if (tL->data[0] != NULL && tL->data[1] != NULL) {
                if (root->left->data[0] != NULL && root->left->data[1] == NULL)
                    root->left->data[1] = root->left->left->data[0];
            }


        }

        return root;

    }
    return root;
}
Node *addNode(Node *root, int data) {

    if (root == NULL)
        return (createNode(data));

    if ((char *) data < root->data[0]) {

        if (root->data[CAP - 3] != NULL && root->data[CAP - 2] == NULL && root->data[CAP - 1] == NULL) {
            if (root->left == NULL) {
                root->data[1] = (char *) data;
                root->height = MAX(findHeight(root->left), findHeight(root->right)) + 1;
                root->left = NULL;
            } else {
                if (root->left->data[0] != NULL && root->left->data[1] != NULL) {
                    root->left->data[2] = (char *) data;
                    root->height = MAX(findHeight(root->left), findHeight(root->right)) + 1;
                    if (root->left->data[0] > root->left->data[1] || root->left->data[1] > root->left->data[2])
                        sortNode(root->left);
                    root->left = splitNode(root->left);
                } else if (root->left->data[0] != NULL && root->left->data[1] == NULL) {
                    root->left->data[1] = (char *) data;
                    root->height = MAX(findHeight(root->left), findHeight(root->right)) + 1;
                    if (root->left->data[0] > root->left->data[1] || root->left->data[1] > root->left->data[2])
                        root->left = sortNode(root->left);
                }
            }

        }else if (root->right->data[0] != NULL && root->right->data[1] != NULL) {
                root->left->data[2] = (char *) data;
                root->height = MAX(findHeight(root->left), findHeight(root->right)) + 1;
                if (root->left->data[0] > root->left->data[1] || root->left->data[1] > root->left->data[2])
                    root->left = sortNode(root->left);
                root->left = splitNode(root->left);
            }
        else if(root->left->data[0] != NULL && root->left->data[1] != NULL){
            root->left->data[2] = (char *) data;
            root->height = MAX(findHeight(root->left), findHeight(root->right)) + 1;
            if (root->left->data[0] > root->left->data[1] || root->left->data[1] > root->left->data[2])
                root->left = sortNode(root->left);
            root->left = splitNode(root->left);
        }

        else if (root->right != NULL)
            root->right = addNode(root->right, data);
    } else if ((char *) data > root->data[0]) {
        if (root->data[CAP - 3] != NULL && root->data[CAP - 2] != NULL && root->data[CAP - 1] == NULL) {
            if ((char *) data > root->data[CAP - 2]) {
                root->data[2] = (char *) addNode(root->right, data)->data[0];
                root->height = MAX(findHeight(root->left), findHeight(root->right)) + 1;
                root = sortNode(root);
                root = splitNode(root);
                return checkNodes(root);

            }
        } else if (root->data[CAP - 3] != NULL && root->data[CAP - 2] == NULL && root->data[CAP - 1] == NULL) {
            if ((char *) data > root->data[CAP - 3]) {
                if (root->right == NULL) {
                    root->data[1] = (char *) data;
                    root->height = MAX(findHeight(root->left), findHeight(root->right)) + 1;
                    root->right = NULL;
                } else {
                    if (root->right->data[0] != NULL && root->right->data[1] != NULL) {
                        root->right->data[2] = (char *) data;
                        root->height = MAX(findHeight(root->left), findHeight(root->right)) + 1;
                        if (root->right->data[0] > root->right->data[1] || root->right->data[1] > root->right->data[2])
                            root->right = sortNode(root->right);
                        root->right = splitNode(root->right);
                    } else if (root->right->data[0] != NULL && root->right->data[1] == NULL) {
                        root->right->data[1] = (char *) data;
                        root->height = MAX(findHeight(root->left), findHeight(root->right)) + 1;
                        if (root->right->data[0] > root->right->data[1] || root->right->data[1] > root->right->data[2])
                            root->right = sortNode(root->right);
                    }
                }

            }
        } else if (root->right != NULL)
            root->right = addNode(root->right, data);
    } else if ((char *) data > root->data[0] && (char *) data < root->data[1]) {
        if (root->data[CAP - 3] != NULL && root->data[CAP - 2] == NULL && root->data[CAP - 1] == NULL) {
            if (root->middle == NULL) {
                root->data[2] = (char *) data;
                root->height = MAX(findHeight(root->left), findHeight(root->right)) + 1;
                sortNode(root);
                root->middle = NULL;
            } else {
                if (root->middle->data[0] != NULL && root->middle->data[1] != NULL) {
                    root->middle->data[2] = (char *) data;
                    root->height = MAX(findHeight(root->left), findHeight(root->right)) + 1;
                    if (root->middle->data[0] > root->middle->data[1] || root->middle->data[1] > root->middle->data[2])
                        sortNode(root->left);
                } else if (root->middle->data[0] != NULL && root->middle->data[0] == NULL) {
                    root->left->data[1] = (char *) data;
                    root->height = MAX(findHeight(root->left), findHeight(root->right)) + 1;
                    if (root->left->data[0] > root->middle->data[1] || root->middle->data[1] > root->middle->data[2])
                        sortNode(root->left);
                }
            }
        } else if ((char *) data > root->data[CAP - 3] && (char *) data < root->data[CAP - 2]) {
            root->data[1] = (char *) addNode(root->middle, data)->data[0];
            root->middle = NULL;
            root = splitNode(root);
            return root;
        } else if (root->middle != NULL)
            root->middle = addNode(root->middle, data);
    } else
        return root;

    return checkNodes(root);

}



void preOrder(Node *root) {
    if (root != NULL) {
        if (root->data[0] != NULL && root->data[1] == NULL)
            printf("%d ", root->data[0]);

        else if (root->data[0] != NULL && root->data[1] != NULL && root->data[2] == NULL) {
            preOrder(root->left);
            preOrder(root->right);
            printf("%d %d ", root->data[0], root->data[1]);
        }
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node *root) {
    if (root != NULL) {
        inOrder(root->left);
        if (root->data[0] != NULL && root->data[1] == NULL)
            printf("%d ", root->data[0]);

        else if (root->data[0] != NULL && root->data[1] != NULL && root->data[2] == NULL) {
            inOrder(root->left);
            inOrder(root->right);
            printf("%d %d ", root->data[0], root->data[1]);
        }
        inOrder(root->right);
    }
}

void postOrder(Node *root) {
    if (root != NULL) {
        if (root->data[0] != NULL && root->data[1] == NULL)
            printf("%d ", root->data[0]);

        else if (root->data[0] != NULL && root->data[1] != NULL && root->data[2] == NULL) {
            postOrder(root->left);
            postOrder(root->right);
            printf("%d %d ", root->data[0], root->data[1]);
        }

        postOrder(root->left);
        postOrder(root->right);

    }
}

struct node * minValueNode(struct node* node)
{
    struct node* current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

Node* deleteNode(Node* root, int key)
{
    if (root == NULL) return root;

    if ((char *) key < root->data[0])
        root->left = deleteNode(root->left, key);

    else if ((char *) key > root->data[0])
        root->right = deleteNode(root->right, key);

    else
    {
        if (root->left == NULL)
        {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = minValueNode(root->right);

        root->data[0] = temp->data[0];

        root->right = deleteNode(root->right, (int) temp->data[0]);
    }
    root = checkNodes(root);
    return root;
}


int main(void) {
    clock_t t;
    t = clock();
    int searchNo = 0;

    Node *root = NULL;

    /* Constructing tree given in the above figure */
    root = addNode(root, 5);
    root = addNode(root, 2);
    root = addNode(root, 6);
    root = addNode(root, 9);
    root = addNode(root, 4);
    root = addNode(root, 10);
    root = addNode(root, 1);
    root = deleteNode(root,1);
    searchNo = search(root, 31);
    printf("%d\n", searchNo);



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

    t = clock() - t;
    double time_taken = ((double) t) / CLOCKS_PER_SEC; // in seconds

    printf("\nExecution Time : %.4f\n", time_taken);


    return 0;

}
