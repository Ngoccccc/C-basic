#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
int x[9][9] = {-1};
void printSolution()
{
    for (int i = 0; i <= 8; i++)
    {
        for (int j = 0; j <= 8; j++)
        {
            printf(" %d ", x[i][j]);
        }
        printf("\n");
    }
}

bool check(int v, int r, int c)
{
    for (int i = 0; i <= r - 1; i++)
        if (x[i][c] == v)
            return false;
    for (int j = 0; j <= c - 1; j++)
        if (x[r][j] == v)
            return false;
    int I = r / 3;
    int J = c / 3;
    int i = r - 3 * I;
    int j = c - 3 * J;
    for (int i1 = 0; i1 <= i - 1; i1++)
        for (int j1 = 0; j1 <= 2; j1++)
            if (x[3 * I + i1][3 * J + j1] == v)
                return false;
    for (int j1 = 0; j1 <= j - 1; j1++)
        if (x[3 * I + i][3 * J + j1] == v)
            return false;
    return true;
}
void TRY(int r, int c)
{
    for (int v = 1; v <= 9; v++)
    {
        if (check(v, r, c))
        {
            x[r][c] = v;
            if (r == 8 && c == 8)
            {
                printSolution();
                exit(0);
            }
            else
            {
                if (c == 8)
                    TRY(r + 1, 0);
                else
                    TRY(r, c + 1);
            }
        }
    }
}
void main()
{
    TRY(0, 0);
}