#include <stdio.h>

int n = 8;
int X[] = {-1, -1, -1, -1, -1, -1, -1, -1};
int count = 0;

void ghinhan()
{
    for (int i = 1; i <= n; ++i)
    {
        if (X[i] != 0)
        {
            printf("%d ", X[i]);
        }
    }
    printf("\n");
    count++;
}

int UCV(int v, int k)
{
    int sum = 0;
    for (int i = 1; i < k; ++i)
    {
        sum += X[i];
    }
    if (sum + v > n)
        return 0;
    if (v >= X[k - 1])
        return 1;
    return 0;
}

int check()
{
    int VT = 0;
    for (int i = 1; i <= n; ++i)
    {
        VT += X[i];
    }
    if (n == VT)
        return 1;
    return 0;
}

void giaipt(int k)
{
    for (int v = 0; v < n; ++v)
    {
        if (UCV(v, k) == 1)
        {
            X[k] = v;
            if (k == n)
            {
                if (check() == 1)
                    ghinhan();
            }
            else
                giaipt(k + 1);
        }
    }
}

int main()
{
    giaipt(1);
    printf("Count: %d", count);
}