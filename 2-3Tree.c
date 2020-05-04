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
        if ((char *) data < root->data[0]) {
            if ((char *) data == root->data[0] || (char *) data == root->data[1]) {
                printf("%d is founded\n", data);
                return data;
            }
            search(root->left, data);
        } else if ((char *) data > root->data[0] && (char *) data < root->data[1]) {
            if ((char *) data == root->data[0] || (char *) data == root->data[1]) {
                printf("%d is founded\n", data);
                return data;
            }
            search(root->middle, data);
        } else if ((char *) data > root->data[1]) {
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
        if ((char *) data < root->data[0]) {
            if ((char *) data == root->data[0]) {
                printf("%d is founded\n", data);
                return data;
            }
            search(root->left, data);
        } else if ((char *) data > root->data[1]) {
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

Node *rightRotate(Node *root) {
    Node *temp = root->left;
    Node *temp1 = temp->right;

    // Perform rotation
    temp->right = root;
    root->left = temp1;

    //  Update heights
    root->height = MAX(findHeight(root->left), findHeight(root->right)) + 1;
    temp->height = MAX(findHeight(temp->left), findHeight(temp->right)) + 1;

    // Return new root
    return temp;
}

Node *leftRotate(Node *root) {
    Node *temp = root->right;
    Node *temp1 = temp->left;

    // Perform rotation
    temp->left = root;
    root->right = temp1;

    //  Update heights
    root->height = MAX(findHeight(root->left), findHeight(root->right)) + 1;
    temp->height = MAX(findHeight(temp->left), findHeight(temp->right)) + 1;

    // Return new root
    return temp;
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
    // IF LEAF IS ROOT
    /*
     make middleKey into a 2-node (which will be the new root)

        make smallKey and largeKey into 2-nodes (which will be the

            children of the new root)

        redistribute children
     */
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

        } else if ((char *) data < root->data[CAP - 3]) {
            if (root->right->data[0] != NULL && root->right->data[1] != NULL) {
                root->left->data[2] = (char *) data;
                root->height = MAX(findHeight(root->left), findHeight(root->right)) + 1;
                if (root->left->data[0] > root->left->data[1] || root->left->data[1] > root->left->data[2])
                    root->left = sortNode(root->left);
                root->left = splitNode(root->left);
            }

        } else if (root->right != NULL)
            root->right = addNode(root->right, data);
    } else if ((char *) data > root->data[0]) {
        if (root->data[CAP - 3] != NULL && root->data[CAP - 2] != NULL && root->data[CAP - 1] == NULL) {
            if ((char *) data > root->data[CAP - 2]) {
                root->data[2] = (char *) addNode(root->right, data)->data[0];
                root->height = MAX(findHeight(root->left), findHeight(root->right)) + 1;
                root = splitNode(root);
                return root;

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
                        root->data[1] = tR->data[0];
                        root->right = tR->right;
                        if (root->right->data[0] != NULL && root->right->data[1] == NULL) {
                            root->right->data[1] = tR->left->data[0];
                            root->right = sortNode(root->right);
                        }
                    } else if (root->data[0] != NULL && root->data[1] != NULL && root->data[2] == NULL) {
                        root->data[2] = tR->data[0];
                        root = sortNode(root);
                        root = splitNode(root);
                    }
                }
            } else if (tR->data[0] != NULL && tR->data[1] != NULL) {
                if (root->right->data[0] != NULL && root->right->data[1] == NULL)
                    root->right->data[1] = root->right->right->data[0];
            }

        }

        while (tL->left) {
            tL = tL->left;

            if (tL->data[0] != NULL && tL->data[1] == NULL) {
                if (diffRNL(root) <= -1) {
                    if (root->data[0] != NULL && root->data[1] == NULL) {
                        root->data[1] = tL->data[0];
                        root->left = tL->left;
                        if (root->left->data[0] != NULL && root->left->data[1] == NULL) {
                            root->left->data[1] = tL->right->data[0];
                            root->left = sortNode(root->left);
                        }
                    } else if (root->data[0] != NULL && root->data[1] != NULL && root->data[2] == NULL) {
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
}

void preOrder(Node *root) {
    if (root != NULL) {
        printf("%s", root->data[0]);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
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


int main(void) {
    clock_t t;
    t = clock();

    Node *root = NULL;

    /* Constructing tree given in the above figure */
    root = addNode(root, 5);
    root = addNode(root, 2);
    sortNode(root);
    root = addNode(root, 6);
    root = addNode(root, 9);
    root = addNode(root, 4);
    sortNode(root);
    // search(root,1);
    root = addNode(root, 10);
    root = checkNodes(root);
    //search(root,1);
    root = addNode(root, 1);
    root = checkNodes(root);
    search(root, 31);
    postOrder(root);



    /* PRINT THE TREE*/
    /*
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
    */

    t = clock() - t;
    double time_taken = ((double) t) / CLOCKS_PER_SEC; // in seconds

    printf("\nExecution Time : %f\n", time_taken);


    return 0;

}
