#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

long long gcd(long long x, long long y)
{
    long long q;
    for (q = x % y; q != 0; q = x % y) {
        printf("%lld ", x / y);
        x = y;
        y = q;
    }
    printf("%lld\n", x / y);
    return y;
}

int main()
{
    long long x, y;
    int cnt = scanf("%lld%lld", &x, &y);
    if (cnt != 2 || y == 0)
        abort();
    gcd(x, y);
}
