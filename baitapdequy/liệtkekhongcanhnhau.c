#include <stdio.h>

int x[3] = {-1, -1, -1,};
int k = 2;
int n = 3;
int count = 0;

void ghinhan()
{
    for (int i = 0; i < k; i++)
        printf("% d", x[i]);
    printf("\n");
    count++;
}

int UCV(int v, int i)
{
    if (i == 0)
        return 1;
    if (v - x[i - 1] > 1)
        return 1;
    return 0;
}

int in(int i)
{
    for (int v = 1; v <= n; v++)
    {
        if (UCV(v, i) == 1)
        {
            x[i] = v;
            if (i == k - 1)
                ghinhan();
            else
                in(i + 1);
        }
    }
}

int main()
{
    in(0);
    printf("Count: %d", count);
}