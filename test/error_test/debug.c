#include <stdio.h>
int test(int a)
{
    if (1)
    {
        int a = 1;
        {
            int a, b;
            printf("%d %d ", a, b);
        }
    }
    return a;
}

int main()
{

    printf("%d", test(5));
}