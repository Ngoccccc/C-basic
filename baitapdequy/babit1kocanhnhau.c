#include <stdio.h>

int x[8] = {-10, -10, -1, -1, -1, -1, -1, -1};

int n = 6;
int count = 0;

void ghinhan()
{
    for (int i = 2; i < n + 2; i++)
        printf("% d", x[i]);
    printf("\n");
    count++;
}

int UCV(int i, int k)
{
    if ((i + x[k - 1] + x[k - 2] == 3))
        return 0;

    return 1;
}

void Indaynhiphan(int k)
{
    int i;
    for (i = 0; i < 2; i++)
    {

        if (UCV(i, k) == 1)
        {
            x[k] = i;
            if (k == (n + 1))
            {
                ghinhan();
            }

            else
                Indaynhiphan(k + 1);
        }
    }
}

int main()
{
    Indaynhiphan(2);
    printf("Count: %d", count);
}