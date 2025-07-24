#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int fs(int x)
{
    int a = 1, b = 1, c = 2, t, last;

    while (c <= x) {
        t = b + c;
        a = b;
        b = c;
        c = t;
    }
    while (c != 1) {
        if (x >= b) {
            x -= b;
            last = b;
        }
        t = b - a;
        c = b;
        b = a;
        a = t;
    }
    return last;
}

int next_turn(int total, int possible)
{
    int last = fs(total);
    if (possible >= last)
        return last;
    return 1;
}

int main()
{
    int n, q, res;

    res = scanf("%d%d", &n, &q);
    if (res != 2)
        abort();

    n = next_turn(n, q);
    printf("%d\n", n);

    return 0;
}
