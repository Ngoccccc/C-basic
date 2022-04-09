#include <stdio.h>
#include <string.h>
void move(int n, char A, char B, char C)
{
    if (n == 1)
    {
        printf("Move 1 disk from %c to %c \n", A, B);
    }
    else
    {
        move(n - 1, A, C, B);
        move(1, A, B, C);
        move(n - 1, C, B, A);
    }
}
void main()
{
    int n = 3;
    move(n, 'A', 'B', 'C');
}