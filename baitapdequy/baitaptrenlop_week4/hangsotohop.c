#include <stdio.h>
int C(int k, int n)
{
    if (k == 0 || k == n)
        return 1;
    int C1 = C(k - 1, n - 1);
    int C2 = C(k, n - 1);
    return C1 + C2;
}
int main()
{
    printf("to hop: %d\n", C(4, 4));
    return 0;
}