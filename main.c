#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person{
    int age;
    struct Person *next;
};

struct Person *createNewPerson (int age){
    struct Person *newPerson = NULL;
    newPerson = malloc(sizeof(struct Person));
    if (newPerson != NULL)
    {
        newPerson->next = NULL;
        newPerson->age = age;
        printf("Created New Person at %p\n",newPerson);
    } else{
        printf("FAIL");
    }

    return newPerson;
};

void printPerson(struct Person *person,char *comment){
    if (person==NULL)
        printf("%s is NULL\n",comment);
    else{
        printf("%s : Age : %d\nAddress : %p\nNext : %p\n",comment,person->age,person,person->next);
        printf("----------------------\n");
    }

}

void cleanList(struct Person *list){
    struct Person *next;
    while(list)
    {
        next = list->next;
        printf("Cleaning %d..",list->age);
        free(list);
        list = next;
    }

}

void printList(struct Person *list){
    printf("List :\n");
    struct Person *temp;
    temp = list;
    if(temp == NULL)
        printf("List is empty !");
    else
        while(temp){
            printPerson(temp,"Temp");
            temp = temp->next;
        }

}



int main() {
    struct Person *first = NULL;
    struct Person *others = NULL;

    char nick[100];
    int age;

    while(1){
        printf("Enter a command or value (Q For Quit)");
        fgets(nick,64,stdin);
        if(strcmp("q\n",nick) == 0)
        {
            printf("Quitting..\n");
            break;
        }
        else if(strcmp("print\n",nick) == 0)
        {
            printf("Printing..\n");
            printList(first);
        }
        else if(sscanf(nick,"%d", &age) != 0)
        {
            printf("Adding %d..\n",age);
            if(first == NULL)
            {
                first = createNewPerson(age);
                if(first != NULL)
                {
                    others = first;
                }
            } else{
                others->next = createNewPerson(age);
                if(others->next != NULL)
                    others = others->next;
            }
        }
    }

    cleanList(first);
    first = NULL;
    others = NULL;

    return 0;
}
