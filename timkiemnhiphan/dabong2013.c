#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct _a
{
    char name[10];
    int score;
    struct Node *leftChild;
    struct Node *rightChild;
} Node;

Node *root;

Node *makeNode(char *name, int score)
{
    Node *p = (Node *)malloc(sizeof(Node));
    strcpy(p->name, name);
    p->score = score;
    p->leftChild = NULL;
    p->rightChild = NULL;
    return p;
}

Node *insert(Node *r, char *name, int score)
{
    if (r == NULL)
        return makeNode(name, score);
    int c = strcmp(r->name, name);
    if (c == 0) // không insert được nếu tên trùng nhau
    {
        r->score += score;
        return r;
    }
    else if (c < 0) // nếu r->name < name thì add node vừa insert vào rightChild
    {
        r->rightChild = insert(r->rightChild, name, score);
        return r;
    }
    else // nếu r->name > name thì add node vừa insert vào leftChild
    {
        r->leftChild = insert(r->leftChild, name, score);
        return r;
    }
}

void Load()
{
    FILE *f = fopen("dabong.txt", "r");
    root = NULL;

    char name1[10];
    char name2[10];
    int doi1, doi2;
    while (!feof(f))
    {
        fscanf(f, "%s %s %d %d", name1, name2, &doi1, &doi2);
        if (doi1 > doi2)
        {
            root = insert(root, name1, 3);
            root = insert(root, name2, 0);
        }
        else if (doi1 < doi2)
        {
            root = insert(root, name1, 0);
            root = insert(root, name2, 3);
        }
        else
        {
            root = insert(root, name1, 1);
            root = insert(root, name2, 1);
        }
    }
}

void inOrder(Node *r)
{
    if (r != NULL)
    {
        inOrder(r->leftChild);
        printf("%s %d\n", r->name, r->score);
        inOrder(r->rightChild);
    }
}

void search_name(Node *r, char *name)
{

    if (r != NULL)
    {
        if (strcmp(r->name, name) == 0)
        {
            printf("%s %d\n", r->name, r->score);
        }
        search_name(r->leftChild, name);
        search_name(r->rightChild, name);
    }
}

Node *findMin(Node *r)
{
    if (r == NULL)
        return NULL;
    Node *lmin = findMin(r->leftChild);
    if (lmin != NULL)
        return lmin;
}

Node *remove_Teams(Node *r, char *name)
{
    if (r == NULL)
        return NULL;
    int c = strcmp(r->name, name);
    if (c > 0)
        r->leftChild = remove_Teams(r->leftChild, name);
    else if (c < 0)
        r->rightChild = remove_Teams(r->rightChild, name);
    else
    {
        if (r->leftChild != NULL && r->rightChild != NULL) // có cả 2 con
        {
            Node *tmp = findMin(r->rightChild); // tìm con trái nhất của cây con phải
            strcpy(r->name, tmp->name);
            r->rightChild = remove_Teams(r->rightChild, tmp->name);
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

void *remove_xuonghang(Node *r, int X)
{
    if (r == NULL)
        return;
    remove_xuonghang(r->leftChild, X);
    if (r->score < X)
    {
        printf("%s\n", r->name);
        root = remove_Teams(root, r->name);
    }
    remove_xuonghang(r->rightChild, X);
}

void team()
{
    int x;
    printf("Nhap so diem xuong hang: ");
    scanf("%d", &x);
    printf("Cac doi bong xuong hang: ");
    remove_xuonghang(root, x);
    printf("Cac doi con lai la:");
    inOrder(root);
}

void inOrderF(Node *r,FILE *f)
{
    if (r != NULL)
    {
        inOrderF(r->leftChild,f);
        fprintf(f,"%s %d\n", r->name, r->score);
        inOrderF(r->rightChild,f);
    }
}

void Store()
{
    FILE *f = fopen("cuoimua.txt", "w");
    inOrderF(root,f);
    fclose(f);
}

void main()
{
    int diem;
    char name[10];
    int chon;
    do
    {
        system("cls"); // lenh xoa man hinh
        printf("----------MENU----------\n");
        printf("1. Tao cay\n");
        printf("2. Ket qua\n");
        printf("3. Tim kiem\n");
        printf("4. Xuong hang\n");
        printf("5. Xuat file\n");
        printf("Moi ban chon menu: ");
        scanf("%d", &chon);

        switch (chon)
        {
        case 1:
            Load();
            break;
        case 2:
            inOrder(root);
            break;
        case 3:

            printf("Nhap ten can tim: ");
            scanf("%s", name);
            search_name(root, name);
            break;
        case 4:
            team();
            break;
        case 5:
            Store();
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

    } while (chon != 5);
}