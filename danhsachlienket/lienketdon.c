#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_L 256
typedef struct Profile
{
    char name[MAX_L];
    char email[MAX_L];
    struct Profile *next;
} Profile;

Profile *first, *last;

Profile *makeProfile(char *name, char *email)
{
    Profile *node = malloc(sizeof(Profile));
    strcpy(node->name, name);
    strcpy(node->email, email);
    node->next = NULL;
    return node;
}

void initList()
{
    first = NULL;
    last = NULL;
}

int listEmpty()
{
    return first == NULL && last == NULL;
}

void insertLast(char *name, char *email)
{
    Profile *profile = makeProfile(name, email);
    if (listEmpty())
    {
        first = profile;
        last = profile;
    }
    else
    {
        last->next = profile;
        last = profile;
    }
}

void printList()
{
    for (Profile *p = first; p != NULL; p = p->next)
    {
        printf("%s , %s \n", p->name, p->email);
    }
}

void removeProfile(char *name)
{
    if (listEmpty())
    {
        printf("List Empty !!!!\n");
    }
    else
    {
        Profile *p = first;
        Profile *prev = NULL;
        while (strcmp(p->name, name) != 0)
        {
            prev = p;
            p = p->next;
        }
        if (p == NULL)
        {
            printf("Not Found student %s\n", name);
        }
        else if (p == first)
        {
            first = first->next;
            free(p);
        }
        else
        {
            prev->next = p->next;
            free(p);
        }
    }
}

void load(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        printf("Load data -> file not found\n");
    while (!feof(f))
    {
        char name[256], email[256];
        fscanf(f, "%s%s", name, email);
        insertLast(name, email);
    }
    fclose(f);
}

void processFind()
{
    char name[256];
    scanf("%s", name);
    Profile *profile = NULL;
    for (Profile *p = first; p != NULL; p = p->next)
    {
        if (strcmp(p->name, name) == 0)
        {
            profile = p;
            break;
        }
    }
    if (profile == NULL)
    {
        printf("NOT FOUND profile %s\n", name);
    }
    else
    {
        printf("FOUND profile %s, %s\n", profile->name, profile->email);
    }
}

void processLoad()
{
    char filename[256];
    scanf("%s", filename);
    load(filename);
}
void processStore()
{
    char filename[256];
    scanf("%s", filename);
    FILE *f = fopen(filename, "w");
    for (Profile *p = first; p != NULL; p = p->next)
    {
        fprintf(f, "%s %s", p->name, p->email);
        if (p->next != NULL)
            fprintf(f, "\n");
    }
    fclose(f);
}

void processInsert()
{
    char name[256], email[256];
    scanf("%s%s", name, email);
    insertLast(name, email);
}
void processRemove()
{
    char name[256];
    scanf("%s", name);
    removeProfile(name);
}

int main()
{
    int choice;
    initList();
    for (;;)
    {
        printf("\n1. Insers\n2. Print\n3. Search.\n4. Remove \n5. Store \n6. Load \n7. Quit");
        printf("\nEnter(1~7):");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            processInsert();
            printf("\nDone!!");
            break;
        case 2:
            printList();
            printf("\nDone!!");
            break;
        case 3:
            processFind();
            printf("\nDone!!");
            break;
        case 4:
            processRemove();
            printf("\nDone!!");
            break;
        case 5:
            processStore();
            printf("\nDone!!");
            break;
        case 6:
            processLoad();
            printf("\nDone!!");
            break;
        default:
            return 1;
        }
    }
}