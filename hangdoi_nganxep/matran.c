#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct Node
{
    int row, col;        // chỉ số hang và cột của trạng thái hiện tại
    int step;            // số bước di chuyển để đi từ trạng thái xuất phát đến trạng thái hiện tại
    struct Node *next;   // con trỏ đến phần tử tiếp theo trong hàng đợi
    struct Node *parent; // con trỏ trỏ đến trạng thái sinh ra trạng thái hiện tại
} Node;

Node *head, *tail;
Node *listNode[MAX * MAX]; // mảng lưu các phần tử được cấp phát động, để giải phóng BN
int szList = 0;            // số phần tử của listNode
int A[MAX][MAX];
int n, m;
int r0, c0;
int visited[MAX][MAX];
const int dr[4] = {1, -1, 0, 0};
const int dc[4] = {0, 0, 1, -1};
Node *finalNode;

void setupA()
{
    for (int i = 0; i < MAX; ++i)
    {
        for (int j = 0; j < MAX; j++)
        {
            A[i][j] = 0;
        }
    }
}

Node *makeNode(int row, int col, int step, Node *parent)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->row = row;
    node->col = col;
    node->next = NULL;
    node->parent = parent;
    node->step = step;
    return node;
}

void initQueue()
{
    head = NULL;
    tail = NULL;
}

int queueEmpty()
{
    return head == NULL && tail == NULL;
}

void pushQueue(Node *node)
{
    if (queueEmpty())
    {
        head = node;
        tail = node;
    }
    else
    {
        tail->next = node;
        tail = node;
    }
}

Node *popQueue()
{
    if (queueEmpty())
        return NULL;
    Node *node = head;
    head = node->next;
    if (head == NULL)
        tail = NULL;
    return node;
}

void input()
{
    setupA();
    FILE *f = fopen("maze.txt", "r");
    fscanf(f, "%d%d%d%d", &n, &m, &r0, &c0);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            fscanf(f, "%d", &A[i][j]);
        }
    }
    fclose(f);
}

int legal(int row, int col)
{
    return A[row][col] == 0 && !visited[row][col];
}

int target(int row, int col)
{
    return row < 1 || row > n || col < 1 || col > m;
}

void finalize()
{
    for (int i = 0; i < szList; i++)
    {
        free(listNode[i]);
    }
}

void addList(Node *node)
{ // them phan tu vao listNode de thuc hien giai phong bo nho
    listNode[szList] = node;
    szList++;
}

int main()
{
    printf("MAZE\n");
    input();
    for (int r = 1; r <= n; r++)
        for (int c = 1; c <= m; c++)
            visited[r][c] = 0;
    initQueue();
    Node *startNode = makeNode(r0, c0, 0, NULL);
    addList(startNode);
    pushQueue(startNode);
    visited[r0][c0] = 1;
    while (!queueEmpty())
    {
        Node *node = popQueue();
        printf("POP (%d,%d)\n", node->row, node->col);
        for (int k = 0; k < 4; k++)
        {
            int nr = node->row + dr[k];
            int nc = node->col + dc[k];
            if (legal(nr, nc))
            {
                visited[nr][nc] = 1;
                Node *newNode = makeNode(nr, nc, node->step + 1, node);
                addList(newNode);
                if (target(nr, nc))
                {
                    finalNode = newNode;
                    break;
                }
                else
                    pushQueue(newNode);
            }
        }
        if (finalNode != NULL)
            break; // found solution
    }
    Node *s = finalNode;
    printf("\nSo buoc di: %d\n", s->step);
    s = s->parent;
    while (s != NULL)
    {
        printf("(%d,%d) ", s->row, s->col);
        s = s->parent;
    }
    finalize();
}