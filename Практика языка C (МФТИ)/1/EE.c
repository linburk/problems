#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

long long gcd(long long a, long long b, long long* x, long long* y)
{
    if (a == 0) {
        *x = 0;
        *y = 1;
        if (b < 0) {
            b = -b;
            *y = -1;
        }
        return b;
    }
    long long q;
    long long x1, y1;
    long long d = gcd(b % a, a, &x1, &y1);
    *x = y1 - b / a * x1;
    *y = x1;
    return d;
}

int main()
{
    long long a, b, x, y;
    int cnt = scanf("%lld%lld", &a, &b);
    if (cnt != 2)
        abort();
    long long d = gcd(a, b, &x, &y);
    printf("%lld %lld %lld\n", x, y, d);
}
