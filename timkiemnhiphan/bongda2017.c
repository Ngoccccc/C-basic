#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define MAX_LEN 50
typedef struct bongda
{
    char name[MAX_LEN];
    int score;
    int lose;
    int id;
    int win;
    struct bongda *next;
} bongda;
bongda *first, *last;

int n;
int List[MAX_LEN][MAX_LEN];
bongda *makeNode(char *name, int score, int lose, int win, int id)
{
    bongda *node = (bongda *)malloc(sizeof(bongda));
    strcpy(node->name, name);
    node->score = score;
    node->lose = lose;
    node->id = id;
    node->win = win;
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

void insertLast(char *name, int score, int lose, int win, int id)
{
    bongda *s = makeNode(name, score, lose, win, id);
    if (listEmpty())
    {
        first = s;
        last = s;
    }
    else
    {
        last->next = s;
        last = s;
    }
}

void processPrint()
{
    printf("%10s %20s %10s %10s %10s\n", "id", "Ten doi bong", "Diem", "Sobanthang", "Sobanthua");
    for (bongda *p = first; p != NULL; p = p->next)
        printf("%10d %20s %10d %10d %10d\n", p->id, p->name, p->score, p->win, p->lose);
}

void loadFileText(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Load data -> file not found\n");
        exit(0);
    }
    int tuoi;
    char name[MAX_LEN];
    int id;
    fscanf(f, "%d", &n);
    for (int i = 0; i < n; i++)
    {
        fscanf(f, "%d\t", &id);
        fscanf(f, "%[^\n]\n", name);
        insertLast(name, 0, 0, 0, id);
    }
    int k = n / 2;
    for (int i = 0; i < n - 1; i++)
    {
        char tenvong[MAX_LEN];
        fscanf(f, "%[^\n]\n", tenvong);
        for (int j = 0; j < n; j++)
        {
            fscanf(f, "%d\t%d\n", &List[i][j], &List[i][j + 1]);
            j++;
        }
    }

    fclose(f);
}

void removeTeams(char *name)
{
    if (listEmpty())
        printf("\nList empty!!");
    else
    {
        bongda *p = first;
        bongda *prev = NULL;
        while (strcmp(p->name, name) != 0)
        {
            prev = p;
            p = p->next;
        }
        if (p == NULL)
        {
            printf("NOT FOUND bongda %s\n", name);
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

void processFindbyId(int id)
{
    if (listEmpty())
        printf("\nList empty!!");
    else
    {
        bongda *p = first;
        for (; p != NULL; p = p->next)
        {
            if (p->id == id)
            {
                printf("%s", p->name);
                break;
            }
        }
    }
}

void printSchedule()
{

    for (int i = 0; i < n - 1; i++)
    {
        printf("Vong %d\n", i + 1);
        for (int j = 0; j < n; j++)
        {
            // printf("%d ", List[i][j]);
            processFindbyId(List[i][j]);
            printf("-");
            processFindbyId(List[i][j + 1]);
            printf("\n");
            j++;
        }
    }
}
void updatebyId(int id, int a, int b)
{
    int check = a - b;
    if (listEmpty())
        printf("\nList empty!!");
    else
    {
        bongda *p = first;
        for (; p != NULL; p = p->next)
        {
            if (p->id == id)
            {
                if (check > 0)
                {
                    p->win += 1;
                    p->score += 3;
                }
                else if (check == 0)
                {
                    p->score += 1;
                }
                else
                    p->lose += 1;
                break;
            }
        }
    }
}

void updateResults()
{
    for (int i = 0; i < n - 1; i++)
    {
        printf("Vong %d\n", i + 1);
        for (int j = 0; j < n; j++)
        {
            // printf("%d ", List[i][j]);
            processFindbyId(List[i][j]);
            printf("-");
            processFindbyId(List[i][j + 1]);
            printf(":");
            int a, b;

            scanf("%d - %d", &a, &b);
            updatebyId(List[i][j], a, b);
            updatebyId(List[i][j + 1], b, a);
            j++;
        }
    }
}
void processStatistics()
{
    int check = 0, count = 0;
    if (listEmpty())
        printf("\nList empty!!");
    else
    {
        char name[MAX_LEN];
        int check = 1000;
        bongda *p = first;
        for (; p != NULL; p = p->next)
        {
            if (p->score < check)
            {
                check = p->score;
            }
        }
        printf("\nCac doi co diem thap nhat la:\n");
        printf("%10s %20s %10s %10s %10s\n", "id", "Ten doi bong", "Diem", "Sobanthang", "Sobanthua");
        p = first;
        for (; p != NULL; p = p->next)
        {
            if (p->score == check)
            {
                strcpy(name, p->name);
                printf("%10d %20s %10d %10d %10d\n", p->id, p->name, p->score, p->win, p->lose);
                removeTeams(name);
            }
        }
        printf("\n Cac doi con lai la:\n");
        processPrint();
    }
}


void processLoad()
{
    initList();
    char filename[MAX_LEN];
    printf("Enter name file:");
    scanf("%s", filename);
    loadFileText(filename);
}


void freeNode()
{
    bongda *p = first;
    while (p != NULL)
    {
        bongda *node = p;
        p = p->next;
        free(node);
    }
}
int main()
{
    processLoad();
    int choice;
    int flag;
    do
    {
        system("cls");
        printf("===================\n");
        printf("CHUONG TRINH TRUY VET COVID19\n");
        printf("1. In thong tin cac doi bong\n");
        printf("2. In thong tin lich thi dau\n");
        printf("3. Cap nhat vong dau\n");
        printf("4. Thong ke\n");
        printf("5. Thoat\n");
        printf("===================\n");
        printf("Nhap lua chon cua ban:");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            processPrint();
            flag = 1;
            printf("Bam phim bat ki de ve menu!");
            getch();
            break;
        case 2:

            printSchedule();
            printf("Bam phim bat ki de ve menu!");
            getch();
            break;
        case 3:
            updateResults();
            processPrint();
            printf("Bam phim bat ki de ve menu!");
            getch();
            break;
        case 4:
            processStatistics();
            printf("\nBam phim bat ki de ve menu!");
            getch();
            break;

        case 5:
            freeNode();
            return 0;

        default:
            printf("\n Khong co chuc nang nay!");
            break;
        }
    } while (choice != 5);
}