#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rpc.h>

/*  MUSIC PLAYER IN C
 *
 * Look my Github Account for Projects about Machine Learning,Cyber Security,Python...
 * Other Projects : https://github.com/aydinnyunus
 *
 *
 */
struct Player *head = NULL;

struct Player{
    char *link;
    struct Player *next;
    struct Player *previous;
};

struct Player *createNewNode (char *link){
    struct Player *newNode = NULL;
    newNode = malloc(sizeof(struct Player));
    if (newNode != NULL)
    {
        newNode->next = NULL;
        newNode->previous = NULL;
        newNode->link = malloc(strlen(link) + 20);
        strcpy(newNode->link, link);
        printf("Created New Person at %p\n", newNode);
    } else{
        printf("FAIL");
    }

    return newNode;
}

void printMusic(){
    if (head==NULL)
        printf("List is Empty\n");
    else{
        printf("Link : %s\n",head->link);
        printf("----------------------\n");
    }

}

void insertAtTail(struct Player *current,char *link) {
    struct Player* temp = head;
    struct Player* newNode = createNewNode(link);

    if(head == NULL) {
        head = newNode;
        current = head;
        return;
    }
    while(temp->next != NULL) temp = temp->next; // Go To last Node
    temp->next = newNode;
    newNode->previous = temp;
}

void cleanList(){
    struct Player *next;
    while(head)
    {
        next = head->next;
        printf("Cleaning %s..",head->link);
        free(head);
        head = next;
    }

}

void printList(){
    printf("List :\n");
    struct Player *temp;
    temp = head;
    if(temp == NULL)
        printf("List is empty !");
    else
        while(temp){
            printf("----------------------\n");
            printMusic();
            temp = temp->next;
        }

}



int main() {

    struct Player *current = head;

    char nick[100];
    char *link=malloc(2000 * sizeof(char)) ;


    x:
    while(1){
        printf("Enter a command or value (Q For Quit)");
        printf("\n----------------------\n");
        fgets(nick,64,stdin);
        if(strcmp("q\n",nick) == 0)
        {
            printf("Quitting..\n");
            break;
        }
        else if(strcmp("next\n",nick) == 0)
        {
            current = head->next;
            printf("Next Link..\n");
            ShellExecute(NULL, "open",current->link, NULL, NULL, SW_SHOWNORMAL);
            printf("\n----------------------\n");
        }
        else if(strcmp("curr\n",nick) == 0)
        {
            if(current->next == NULL){
                printf("You are in last !");
                goto x;
            }
            printf("Open Link..\n");
            ShellExecute(NULL, "open",current->link, NULL, NULL, SW_SHOWNORMAL);
            printf("\n----------------------\n");

        }
        else if(strcmp("prev\n",nick) == 0)
        {
            if(current->previous == NULL){
                printf("You are in first !");
                goto x;
            }
            current = current->previous;
            printf("Previous Link..\n");
            ShellExecute(NULL, "open",current->link, NULL, NULL, SW_SHOWNORMAL);
            printf("\n----------------------\n");

        }
        else if(strcmp("print\n",nick) == 0)
        {
            printf("Printing..\n");
            printList();
        }
        else if(sscanf(nick,"%999s", link) != 0)
        {
            printf("Adding %s..\n",link);
            insertAtTail(current,link);
        }
    }

    cleanList();


    return 0;
}
