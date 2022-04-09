#include <stdio.h>
#define N 100
int m[N];
int fib(int n)
{
    if (n <= 1)
        m[n] = 1;
    else
    {
        if (m[n] == 0)
            m[n] = fib(n - 1) + fib(n - 2);
    }
    return m[n];
}
void init()
{
    memset(m, 0, sizeof(int) * N);
}
int main()
{
    init();
    for (int i = 0; i < 10; i++)
        printf("fib[%d] = %d\n", i, fib(i));
}