#include <stdio.h>
#include <stdlib.h>

unsigned fibonacci(unsigned n, unsigned m)
{
    unsigned a = 0, b = 1;
    while (n--) {
        unsigned c = (a + b) % m;
        a = b;
        b = c;
    }
    return a;
}

int main()
{
    unsigned x, m, res;
    int cnt = scanf("%u%u", &x, &m);
    if (cnt != 2 || m == 0)
        abort();
    res = fibonacci(x, m);
    printf("%u\n", res);
    return 0;
}
