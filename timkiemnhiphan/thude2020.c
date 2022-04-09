#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <windows.h>
typedef struct Node
{
    char address[256];
    int gio,phut;
    struct Node *next;
} Node;

Node *first;
Node *last;

void initList()
{
    first = NULL;
    last = NULL;
}

int listEmpty()
{
    return first == NULL && last == NULL;
}

void insertLast(char *address, int gio, int phut){
    Node *p = (Node *)malloc(sizeof(Node));
    strcpy(p->address, address);
    p->gio = gio;
    p->phut = phut;
    p->next = NULL;
    if (listEmpty())
    {
        first = p;
        last = p;
    }
    else
    {
        last->next = p;
        last = p;
    }
}


void load(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        printf("Load data -> file not found\n");
    while (!feof(f))
    {
        char address[256];
        int gio,phut;
        fscanf(f, "%s%d%d", address, &gio, &phut);
        insertLast(address, gio, phut);
    }
    fclose(f);
}

void processLoad()
{
    char filename[256];
    scanf("%s", filename);
    load(filename);
}

void printList(){
    Node *p = first;
    printf("%-50s %-10s %-10s\n","Dia diem","gio","phut");
    while (p != NULL)
    {   
        
        printf("%-50s %-10d %-10d\n", p->address, p->gio, p->phut);
        p = p->next;
    }
}

void searchAddress(){
    char address[256];
    printf("Address: ");
    scanf("%s", address);
    Node *p = first;
    while (p != NULL)
    {
        if (strcmp(p->address, address) == 0)
        {
           
            printf("%d:%d\n", p->gio, p->phut);
        
        }
        p = p->next;
    }
    printf("Not found\n");
}

void searchTime(){
    int gio,phut;
    printf("Gio: ");
    scanf("%d", &gio);
    printf("Phut: ");
    scanf("%d", &phut);
    Node *p = first;
    while (p != NULL)
    {
        if (p->gio == gio && p->phut == phut)
        {   
            
            printf("%s\n", p->address);
           
        }
        p = p->next;
    }
    printf("Not found\n");
}

void check_address(){
    char address[256];
    int gio,phut;
    printf("Address: ");
    scanf("%s", address);
    printf("Gio:");
    scanf("%d",&gio);
    printf("Phut:");
    scanf("%d",&phut);
    Node *p = first;
    while (p != NULL)
    {
        if (strcmp(p->address, address) == 0)
        {
            if(gio<p->gio){
                printf("Ban co nguy co mac Covid");
            }
            else if(gio==p->gio){
                if(phut<p->phut){
                    printf("Ban co nguy co mac Covid");
                }
            }
            else{
                printf("Ban khong co nguy co mac Covid");
            }
        }
        p = p->next;
    }
    
}

void main()
{
    int chon;
    do
    {
        system("cls"); // lenh xoa man hinh
        printf("----------MENU----------\n");
        printf("1. Nap file log lịch su di chuyen\n");
        printf("2. In ra lich su di chuyen\n");
        printf("3. Tim kiem lich su theo dia diem\n");
        printf("4. Tim kiem lich su theo thoi gian\n");
        printf("5. Kiem tra truy vet moi nhat\n");
        printf("6. Quit\n");
        printf("Moi chon menu:");
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
            searchAddress();
            break;
        case 4:
            searchTime();
            break;
        case 5:
           check_address();
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

    } while (chon != 6);
}
