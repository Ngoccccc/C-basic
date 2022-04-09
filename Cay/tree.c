#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char name[256];
    struct Node *leftMostChild; // pointer to the left-most child
    struct Node *rightSibling;  // pointer to the right sibling
} Node;

Node *root;

Node *makeNode(char *name)
{
    Node *p = (Node *)malloc(sizeof(Node));
    strcpy(p->name, name);
    p->leftMostChild = NULL;
    p->rightSibling = NULL;
    return p;
}

Node *find(Node *r, char *name)
{
    if (r == NULL)
        return NULL;
    if (strcmp(r->name, name) == 0)
        return r;
    Node *p = r->leftMostChild;
    while (p != NULL)
    {
        Node *q = find(p, name);
        if (q != NULL)
            return q;
        p = p->rightSibling;
    }
    if (p == NULL)
        return NULL;
}

// Node *addLast(Node *p, char *name)
// {
//     if (p == NULL)
//         return makeNode(name);
//     p->rightSibling = addLast(p->rightSibling, name);
//     return p;
// }

// void addChild(char *name, char *child)
// {
//     Node *r = find(root, name);
//     if (r == NULL)
//         return;
//     r->leftMostChild = addLast(r->leftMostChild, child);
// }

void addChild(char *name, char *child)
{
    Node *p = find(root, name);
    if (p == NULL)
    {
        printf("\nNot found %s", name);
        return;
    }
    else
    {
        if (p->leftMostChild == NULL)
        {
            p->leftMostChild = makeNode(child);
        }
        else
        {
            Node *q = p->leftMostChild;
            while (q->rightSibling != NULL)
            {
                q = q->rightSibling;
            }
            q->rightSibling = makeNode(child);
        }
    }
}

void processAddChild()
{
    char name[256];
    printf("\nName: ");
    scanf("%s", name);
    char child[256];
    printf("\nChild: ");
    scanf("%s", child);
    addChild(name, child);
}

void printTree(Node *r)
{
    if (r == NULL)
        return;
    printf("%s: ", r->name);
    Node *p = r->leftMostChild;
    while (p != NULL)
    {
        printf("%s ", p->name);
        p = p->rightSibling;
    }
    printf("\n");
    p = r->leftMostChild;
    while (p != NULL)
    {
        if (p->leftMostChild != NULL)
        {
            printTree(p);
        }
        p = p->rightSibling;
    }
}

void printTreeF(Node *r, FILE *f)
{
    if (r == NULL)
        return;
    fprintf(f, "%s ", r->name);
    Node *p = r->leftMostChild;
    while (p != NULL)
    {
        fprintf(f, "%s ", p->name);
        p = p->rightSibling;
    }
    fprintf(f, " $\n");
    p = r->leftMostChild;
    while (p != NULL)
    {
        if (p->leftMostChild != NULL)
        {
            printTreeF(p, f);
        }
        p = p->rightSibling;
    }
}

void processFind()
{
    char name[256];
    printf("\nName: ");
    scanf("%s", name);
    Node *p = find(root, name);
    if (p == NULL)
        printf("Not Found %s\n", name);
    else
        printf("Found %s\n", name);
}

void processFindChildren()
{
    char name[256];
    printf("\nName: ");
    scanf("%s", name);
    Node *p = find(root, name);
    if (p == NULL)
        printf("Not Found %s\n", name);
    else
    {
        printf("Found %s with children: ", name);
        Node *q = p->leftMostChild;
        while (q != NULL)
        {
            printf("%s ", q->name);
            q = q->rightSibling;
        }
    }
    printf("\n");
}

int height(Node *p)
{
    if (p == NULL)
        return 0;
    int maxH = 0;
    Node *q = p->leftMostChild;
    while (q != NULL)
    {
        int h = height(q);
        maxH = maxH < h ? h : maxH;
        q = q->rightSibling;
    }
    return maxH + 1;
}

void processHeight()
{
    char name[256];
    printf("\nName: ");
    scanf("%s", name);
    Node *p = find(root, name);
    if (p == NULL)
        printf("Not Found %s\n", name);
    else
    {
        printf("Found %s having height = %d\n", name, height(p));
    }
}

int count(Node *r)
{
    if (r == NULL)
        return 0;
    int cnt = 1;
    Node *q = r->leftMostChild;
    while (q != NULL)
    {
        cnt += count(q);
        q = q->rightSibling;
    }
    return cnt;
}

void processCount()
{
    printf("Number of members is %d\n", count(root));
}

void processStore()
{
    char filename[256];
    printf("\nFilename: ");
    scanf("%s", filename);
    FILE *f = fopen(filename, "w");
    printTreeF(root, f);
    fprintf(f, "$$");
    fclose(f);
}

void freeTree(Node *r)
{
    if (r == NULL)
        return;
    Node *p = r->leftMostChild;
    while (p != NULL)
    {
        Node *sp = p->rightSibling;
        freeTree(p);
        p = sp;
    }
    printf("free node %s\n", r->name);
    free(r);
    r = NULL;
}

void loadFileTree(FILE *f)
{
    char buff[256];
    int left = 0;
    fscanf(f, "%s", buff);
    root = makeNode(buff);
    Node *p = root;
    while (feof(f) != EOF)
    {
        fscanf(f, "%s", buff);
        if (strcmp(buff, "$") == 0)
        {
            left = 0;
            fscanf(f, "\n%s", buff);
            if (strcmp(buff, "$$") == 0)
                break;
            p = find(root, buff);
        }
        else
        {
            if (left == 0)
            {
                left = 1;
                p->leftMostChild = makeNode(buff);
                p = p->leftMostChild;
            }
            else
            {
                p->rightSibling = makeNode(buff);
                p = p->rightSibling;
            }
        }
    }
}

void processLoad()
{
    char filename[256];
    printf("\nFilename: ");
    scanf("%s", filename);
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("\nCan't open file");
        fclose(f);
        return;
    }
    loadFileTree(f);
    fclose(f);
}

void processPrint()
{
    printf("\nTree:-----------------\n");
    printTree(root);
}

void main()
{
    while (1)
    {
        char cmd[256];
        printf("\n1.Load\n2.Print\n3.Find\n4.FindChildren\n5.Height\n6.Count\n7.AddChild\n8.Store\n9.Quit");
        printf("\nEnter number: ");
        scanf("%s", cmd);
        if (strcmp(cmd, "9") == 0)
            break;
        else if (strcmp(cmd, "1") == 0) // OK
            processLoad();
        else if (strcmp(cmd, "2") == 0) // OK
            processPrint();
        else if (strcmp(cmd, "3") == 0) // OK
            processFind();
        else if (strcmp(cmd, "4") == 0) // OK
            processFindChildren();
        else if (strcmp(cmd, "5") == 0) // OK
            processHeight();
        else if (strcmp(cmd, "6") == 0) // OK
            processCount();
        else if (strcmp(cmd, "7") == 0) // OK
            processAddChild();
        else if (strcmp(cmd, "8") == 0) // OK
            processStore();
    }
    freeTree(root);
}