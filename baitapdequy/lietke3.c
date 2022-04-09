#include <stdio.h>

int x[8] = {-10,-10,-1, -1, -1, -1, -1, -1};
int k = 4;
int n = 8;
int count = 0;

void printSolution()
{
    for (int i = 2; i < k + 2; i++)
        printf("% d", x[i]);
    printf("\n");
    count++;
}

int UCV(int v, int i)
{   
    if ((v - x[i - 1] == 1 &&  v - x[i-2] == 2)||( v <= x[i-1] ))
        return 0;
    else if((v > x[i - 1]))
        return 1;
}

int TRY(int i)
{
    for (int v = 1; v <= n; v++)
    {
        if (UCV(v, i) == 1)
        {
            x[i] = v;
            if (i == (k + 1))
                printSolution();
            else
                TRY(i + 1);
        }
    }
}

int main()
{
    TRY(2);
    printf("Count: %d", count);
}