#include <stdio.h>
#include <stdlib.h>

int is_prime(int n)
{
    if (n < 2)
        return 0;
    for (int i = 2; i * i <= n; ++i) {
        if ((n % i) == 0)
            return 0;
    }
    return 1;
}

int main()
{
    int n, res = 1, cnt = 0;
    int scanned = scanf("%d", &n);
    if (scanned != 1 || n < 1)
        abort();
    do {
        ++res;
        cnt += is_prime(res);
    } while (cnt < n);
    printf("%d\n", res);
    return 0;
}
