#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

long long llabs(long long x) { return x < 0 ? -x : x; }

long long gcd(long long x, long long y)
{
    long long q;
    x = llabs(x), y = llabs(y);
    for (q = x % y; q != 0; q = x % y) {
        x = y;
        y = q;
    }
    return y;
}

int main()
{
    long long x, y;
    int cnt = scanf("%lld%lld", &x, &y);
    if (cnt != 2)
        abort();
    long long res = gcd(x, y);
    printf("%lld", res);
    return 0;
}
