#include <stdio.h>
int n = 4;
int x[10];
void printSolution()
{
    for (int k = 1; k <= n; k++)
        printf("%d", x[k]);
    printf("\n");
}
int check(int v, int k)
{
    // kiểm tra xem v có thể gán được
    // cho x[k] không
    for (int i = 1; i <= k - 1; i++)
    {
        if (x[i] == v)
            return 0;
        if (x[i] + i == v + k)
            return 0;
        if (x[i] - i == v - k)
            return 0;
    }
    return 1;
}
void TRY(int k)
{
    for (int v = 1; v <= n; v++)
    {
        if (check(v, k))
        {
            x[k] = v;
            if (k == n)
                printSolution();
            else
                TRY(k + 1);
        }
    }
}
void main()
{
    TRY(1);
}
