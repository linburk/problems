#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

long long binary_pow(long long x, unsigned long long p, unsigned long long mod)
{
    long long res = 1;
    for (; p > 0; p >>= 1) {
        if (p & 1)
            res = res * x % mod;
        x = x * x % mod;
    }
    return res;
}

long long spow(long long x, unsigned long long p, unsigned long long mod)
{
    long long res;
    res = x;
    for (int i = 1; i < p - 1; ++i) {
        res = binary_pow(x, res, LLONG_MAX);
    }
    if (p > 1) {
        res = binary_pow(x, res, mod);
    } else {
        res %= mod;
    }
    return res;
}

int main()
{
    unsigned long long x, p, mod;
    int cnt = scanf("%llu%llu%llu", &x, &p, &mod);
    if (cnt != 3 || mod == 0)
        abort();
    printf("%lld\n", spow(x, p, mod));
    return 0;
}
