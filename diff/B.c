#include <gmp.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

char s[100001];
unsigned long prec = 332300;

int main()
{
    int n, k;
    mpf_t x;
    mpf_t t1;
    mpf_t t2;
    mpf_init2(x, prec);
    mpf_init2(t1, prec);
    mpf_init2(t2, prec);
    mpf_set_si(x, n);
    scanf("%d %d", &n, &k);
    for (int i = 0; i < 200; ++i)
    {
        mpf_set(t1, x);
        mpf_pow_ui(t1, t1, 3);
        mpf_sub_ui(t1, t1, n);
        // f(x) = x^3 - s = 0

        mpf_set(t2, x);
        mpf_pow_ui(t2, t2, 2);
        mpf_mul_ui(t2, t2, 3);
        // f`(x) = 3x^2

        mpf_div(t1, t1, t2);
        // f(x) / f`(x)

        mpf_sub(x, x, t1);
        // xn = xn-1 - f(xn-1) / f`(xn-1)
    }
    mp_exp_t e;
    mpf_get_str(s, &e, 10, k + 3, x);
    for (int i = 0; i < e; ++i)
    {
        printf("%c", s[i]);
    }
    printf(".");
    for (int i = e; i < e + k; ++i)
    {
        printf("%c", s[i]);
    }
    mpf_clear(x);
    mpf_clear(t1);
    mpf_clear(t2);
}
