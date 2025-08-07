#include <fenv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ffrac(float x)
{
    int i, xi, ret = 0;
    memcpy(&xi, &x, sizeof(float));
    ret |= xi & 0x7FFFFF;
    return ret;
}

int fexp(float x)
{
    int i, xi, ret = 0;
    memcpy(&xi, &x, sizeof(float));
    ret |= xi >> 23 & 0xFF;
    return ret;
}

int main()
{
    int   err;
    int   p, q;
    float res1, res2;
    err = scanf("%d%d", &p, &q);
    p = abs(p), q = abs(q);
    if (err != 2)
        abort();
    fesetround(FE_DOWNWARD);
    res1 = (float)p / q;
    fesetround(FE_UPWARD);
    res2 = (float)p / q;
    printf("0x%x 0x%x", fexp(res1), ffrac(res1));
    if (res1 != res2)
        printf(" 0x%x 0x%x\n", fexp(res2), ffrac(res2));
    else
        printf("\n");
    return 0;
}
