#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#define MAX_L 256
#define MAX 100000
typedef struct Node
{
    char name[256];
    char email[256];
    struct Node *leftChild;
    struct Node *rightChild;
} Node;
Node *root;

Node *makeNode(char *name, char *email)
{
    Node *p = (Node *)malloc(sizeof(Node));
    strcpy(p->name, name);
    strcpy(p->email, email);
    p->leftChild = NULL;
    p->rightChild = NULL;
    return p;
}
Node *insert(Node *r, char *name, char *email)
{
    if (r == NULL)
        return makeNode(name, email);
    int c = strcmp(r->name, name);
    if (c == 0) // không insert được nếu tên trùng nhau
    {
        printf("Student %s exists, do not insert\n", name);
        return r;
    }
    else if (c < 0) // nếu r->name < name thì add node vừa insert vào rightChild
    {
        r->rightChild = insert(r->rightChild, name, email);
        return r;
    }
    else // nếu r->name > name thì add node vừa insert vào leftChild
    {
        r->leftChild = insert(r->leftChild, name, email);
        return r;
    }
}

Node *find(Node *r, char *name)
{
    if (r == NULL)
        return NULL;
    int c = strcmp(r->name, name);
    if (c == 0)
        return r;
    if (c < 0)
        return find(r->rightChild, name); // nếu r->name < name thì tìm kiếm ở phía con phải
    return find(r->leftChild, name); // nếu r->name > name thì tìm kiếm ở phía con trái
}
Node *findMin(Node *r)  // tìm con trái nhất ( nhỏ nhất )
{
    if (r == NULL)
        return NULL;
    Node *lmin = findMin(r->leftChild);
    if (lmin != NULL)
        return lmin;
    return r;
}

Node *removeStudent(Node *r, char *name)
{
    if (r == NULL)
        return NULL;
    int c = strcmp(r->name, name);
    if (c > 0)
        r->leftChild = removeStudent(r->leftChild, name);
    else if (c < 0)
        r->rightChild = removeStudent(r->rightChild, name);
    else
    {
        if (r->leftChild != NULL && r->rightChild != NULL) // có cả 2 con
        {
            Node *tmp = findMin(r->rightChild);  // tìm con trái nhất của cây con phải
            strcpy(r->name, tmp->name);
            strcpy(r->email, tmp->email);
            r->rightChild = removeStudent(r->rightChild, tmp->name);
        }
        else
        {
            Node *tmp = r;
            if (r->leftChild == NULL)
                r = r->rightChild;
            else
                r = r->leftChild;
            free(tmp);
        }
    }
    return r;
}

void freeTree(Node *r)
{
    if (r == NULL)
        return;
    freeTree(r->leftChild);
    freeTree(r->rightChild);
    free(r);
}
void load(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        printf("Load data -> file not found\n");
    root = NULL;
    while (!feof(f))
    {
        char name[256], email[256];
        fscanf(f, "%s%s", name, email);
        root = insert(root, name, email);
    }
    fclose(f);
}

void inOrder(Node *r)
{
    if (r == NULL)
        return;
    inOrder(r->leftChild);
    printf("%s, %s\n", r->name, r->email);
    inOrder(r->rightChild);
}
void inOrderF(Node *r, FILE *f)
{
    if (r == NULL)
        return;
    inOrderF(r->leftChild, f);
    fprintf(f, "%s %s\n", r->name, r->email);
    inOrderF(r->rightChild, f);
}


void processLoad(){
    char filename[256];
    printf("File name: ");
    scanf("%s", filename);
    load(filename);
}
 
void processFind(){
    char name[256];
    Node *p = (Node *)malloc(sizeof(Node));
    printf("Ten can tim kiem: ");
    scanf("%s", name);
    p=find(root,name);
    if(p ==NULL){
        printf("Not found student %s\n", name);
    }
    else
    {
        printf("Found student %s , email %s \n", p->name, p->email);
    }
}



void printList()
{
    inOrder(root);
    printf("\n");
}

void processStore()
{   
    char filename[256];
    printf("File name: ");
    scanf("%s", filename);
    FILE *f = fopen(filename, "w");
    inOrderF(root, f);
    fclose(f);
}

void processInsert()
{   
    char name[256], email[256];
    printf("Nhap ten va email muon insert: ");
    scanf("%s%s", name, email);
    root = insert(root, name, email);
}

void processRemove()
{
    char name[256];
    printf("Nhap ten muon xoa: ");
    scanf("%s", name);
    root = removeStudent(root, name);
}

void main()
{
    int chon;
    do
    {
        system("cls"); // lenh xoa man hinh
        printf("----------MENU----------\n");
        printf("1. Load\n");
        printf("2. Print\n");
        printf("3. Find\n");
        printf("4. Insert\n");
        printf("5. Remove\n");
        printf("6. Store\n");
        printf("7. Quit\n");
        printf("Moi ban chon menu: ");
        scanf("%d", &chon);

        switch (chon)
        {
        case 1:
            processLoad();

            break;
        case 2:
            printList();
            break;
        case 3:
            processFind();
            break;
        case 4:
            processInsert();
            break;
        case 5:
            processRemove();
            break;
        case 6:
            processStore();
            break;
        default:
            printf("Ket thuc chuong trinh ");
            break;
        }

        printf("Ban co muon tiep tuc khong? (Nhap y/n)");
        char c;
        fflush(stdin);
        scanf("%c", &c);
        if (c == 'y')
        {
            chon = -1;
        }
        else
        {
            printf("Tam biet!");
        }

    } while (chon != 7);
}