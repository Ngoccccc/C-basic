#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#define MAX 256

int N;

typedef struct _Price
{
    float giamo;
    float giadong;
} Price;

typedef struct _cophieu
{
    char name[30];
    Price price[10];
    int day;
    float tb;
    struct cophieu *leftChild;
    struct cophieu *rightChild;
} cophieu;

cophieu *root;

cophieu *makecophieu(char *name, float op, float cp)
{
    cophieu *p = (cophieu *)malloc(sizeof(cophieu));
    strcpy(p->name, name);
    p->day = 0;
    p->price[0].giamo = op;
    p->price[0].giadong = cp;
    p->leftChild = NULL;
    p->rightChild = NULL;
    return p;
}

cophieu *insert(cophieu *r, char *name, float op, float cp)
{
    if (r == NULL)
        return makecophieu(name, op, cp);
    int c = strcmp(r->name, name);
    if (c == 0)
    {
        return r;
    }
    else if (c < 0)
    {
        r->rightChild = insert(r->rightChild, name, op, cp);
        return r;
    }
    else
    {
        r->leftChild = insert(r->leftChild, name, op, cp);
        return r;
    }
}

cophieu *findMin(cophieu *r)
{
    if (r == NULL)
    {
        return NULL;
    }
    cophieu *lmin = findMin(r->leftChild);
    if (lmin != NULL)
    {
        return lmin;
    }
    return r;
}

cophieu *findcophieu(cophieu *r, char *name)
{
    if (r == NULL)
        return NULL;
    int c = strcmp(r->name, name);
    if (c == 0)
        return r;
    if (c < 0)
        return findcophieu(r->rightChild, name);
    return findcophieu(r->leftChild, name);
}

void loadFile()
{
    FILE *f = fopen("data.txt", "r");
    if (f == NULL)
        printf("Khong tim thay file data.txt\n");
    root = NULL;
    fscanf(f, "%d", &N);
    char name[30];
    float op;
    float cp;
    for (int i = 0; i < N; i++)
    {
        fscanf(f, "%s %f %f", name, &op, &cp);
        root = insert(root, name, op, cp);
    }
    while (!feof(f))
    {

        fscanf(f, "%s %f %f", name, &op, &cp);
        cophieu *r = findcophieu(root, name);
        r->day++;
        r->price[r->day].giamo = op;
        r->price[r->day].giadong = cp;
    }
    fclose(f);
}

void inOrder(cophieu *r)
{

    if (r == NULL)
        return;
    inOrder(r->leftChild);
    float TB = 0;
    for (int i = 0; i < 10; i++)
    {
        TB += r->price[i].giadong - r->price[i].giamo;
    }
    r->tb = TB / 10;
    printf("%-5s   %8.3f\n", r->name, TB / 10);
    inOrder(r->rightChild);
}

cophieu *delete_cophieu(cophieu *r, char *name)
{
    if (r == NULL)
    {
        return NULL;
    }
    if (strcmp(r->name, name) > 0)
    {
        r->leftChild = delete_cophieu(r->leftChild, name);
    }
    else if (strcmp(r->name, name) < 0)
    {
        r->rightChild = delete_cophieu(r->rightChild, name);
    }
    else
    {
        if (r->leftChild != NULL && r->rightChild != NULL)
        {
            cophieu *tmp = findMin(r->rightChild);
            strcpy(r->name, tmp->name);
            r->rightChild = delete_cophieu(r->rightChild, tmp->name);
        }
        else
        {
            cophieu *tmp = r;
            if (r->leftChild == NULL)
                r = r->rightChild;
            else
                r = r->leftChild;
            free(tmp);
        }
    }
    return r;
}

void main()
{
    char name1[30];
    int chon;
    char name[30];
    do
    {
        system("cls"); // lenh xoa man hinh
        printf("----------MENU----------\n");
        printf("1. Doc file\n");
        printf("2. Tim kiem theo ma chung khoan\n");
        printf("3. Tim kiem chung khoan co xu huong tang\n");
        printf("4. Tim ma so ngay tang lon nhat\n");
        printf("5. Thoat\n");
        printf("Moi ban chon menu: ");
        scanf("%d", &chon);

        switch (chon)
        {
        case 1:
            loadFile();
            printf("%-5s  %-5s   %-5s\n", "Name", "Trung Binh");
            inOrder(root);
            break;
        case 2:

            printf("Nhap ma chung khoan: ");
            fflush(stdin);
            scanf("%s", name);
            cophieu *r = findcophieu(root, name);
            if (r == NULL)
            {
                printf("Khong tim thay ma !!");
            }
            else
            {
                float min = 1000, max = 0;
                for (int i = 0; i < 10; i++)
                {
                    if (r->price[i].giadong < min)
                        min = r->price[i].giadong;
                    if (r->price[i].giadong > max)
                        max = r->price[i].giadong;
                }
                printf("Gia dong cua cao nhat: %.3f\nGia dong cua thap nhat: %.3f\n", max, min);
            }

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:
            printf("Tran Tien Ngoc 20205009\n");
            printf("Ket thuc chuong trinh ");
            break;
        default:
            
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