#include <stdio.h>
#include <stdlib.h>

unsigned period(unsigned long long m)
{
    unsigned long long a = 0, b = 1, c;
    unsigned res = 0;
    if (m < 2)
        return m;
    do {
        c = (a + b) % m;
        a = b;
        b = c;
        ++res;
    } while (a != 0 || b != 1);
    return res;
}

unsigned long long fibonacci(unsigned n, unsigned long long m)
{
    unsigned long long a = 0, b = 1, c;
    while (n--) {
        c = (a + b) % m;
        a = b;
        b = c;
    }
    return a;
}

int main()
{
    unsigned long long x, m, f;
    unsigned p;
    int cnt = scanf("%llu%llu", &x, &m);
    if (cnt != 2 || m == 0)
        abort();
    p = period(m);
    if (p == 0)
        abort();
    x %= p;
    f = fibonacci(x, m);
    printf("%llu %u\n", f, p);
    return 0;
}
