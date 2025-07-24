#include <stdio.h>
#include <stdlib.h>

void to_fs(unsigned x)
{
    unsigned a = 1, b = 1, c = 2, t;
    while (c <= x) {
        t = b + c;
        a = b;
        b = c;
        c = t;
    }
    while (c != 1) {
        printf("%d", x >= b);
        if (x >= b)
            x -= b;
        t = b - a;
        c = b;
        b = a;
        a = t;
    }
}

int main()
{
    unsigned n;
    int cnt = scanf("%u", &n);
    if (cnt != 1)
        abort();
    to_fs(n);
}
