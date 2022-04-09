#include <stdio.h>

int m[20][20];
int C(int k, int n)
{
    if (k == 0 || k == n)
        m[k][n] = 1;
    else
    {
        if (m[k][n] < 0)
        {
            m[k][n] = C(k - 1, n - 1) + C(k, n - 1);
        }
    }
    return m[k][n];
}
int main()
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            m[i][j] = -1;
        }
    }
    printf("%d\n", C(5, 10));
}