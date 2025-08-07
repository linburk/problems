#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int asint(float x)
{
    int ret;
    memcpy(&ret, &x, sizeof(int));
    return ret;
}

float asfloat(int x)
{
    float ret;
    memcpy(&ret, &x, sizeof(float));
    return ret;
}

int inverse(int x)
{
    for (int i = 1; i < 23; i += 2)
        x ^= 1 << i;
    return x;
}

int main()
{
    int   err;
    float f;
    int   i;
    err = scanf("%f", &f);
    if (err != 1)
        abort();
    i = asint(f);
    i = inverse(i);
    f = asfloat(i);
    printf("%.5f\n", f);
}
