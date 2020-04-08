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
struct Person *head = NULL;

struct Person{
    char *link;
    struct Person *next;
    struct Person *previous;
};

struct Person *createNewPerson (char *link){
    struct Person *newPerson = NULL;
    newPerson = malloc(sizeof(struct Person));
    if (newPerson != NULL)
    {
        newPerson->next = NULL;
        newPerson->previous = NULL;
        newPerson->link = malloc(strlen(link) + 20);
        strcpy(newPerson->link,link);
        printf("Created New Person at %p\n",newPerson);
    } else{
        printf("FAIL");
    }

    return newPerson;
}

void printPerson(){
    if (head==NULL)
        printf("List is Empty\n");
    else{
        printf("Link : %s\n",head->link);
        printf("----------------------\n");
    }

}

void InsertAtTail(char *link) {
    struct Person* temp = head;
    struct Person* newNode = createNewPerson(link);

    if(head == NULL) {
        head = newNode;
        return;
    }
    while(temp->next != NULL) temp = temp->next; // Go To last Node
    temp->next = newNode;
    newNode->previous = temp;
}

void cleanList(){
    struct Person *next;
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
    struct Person *temp;
    temp = head;
    if(temp == NULL)
        printf("List is empty !");
    else
        while(temp){
            printf("----------------------\n");
            printPerson();
            temp = temp->next;
        }

}



int main() {

    struct Person *current = head;

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
            InsertAtTail(link);
            current = head;
        }
    }

    cleanList();


    return 0;
}
