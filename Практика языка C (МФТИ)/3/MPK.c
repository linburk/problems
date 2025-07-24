#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int multiply(int const* restrict, int const* restrict, int*, int);

int main()
{
    int tmp;
    int n, m, size;
    int *a = NULL, *b = NULL;
    int* res = NULL;
    tmp = scanf("%d%d", &n, &m);
    if (tmp != 2 || n <= 0 || m <= 0)
        abort();
    size = 1 << (sizeof(int) * CHAR_BIT - __builtin_clz(n < m ? m : n)); // ceil to 2^x
    a = calloc(size, sizeof(int));
    if (a == NULL)
        abort();
    b = calloc(size, sizeof(int));
    if (b == NULL)
        goto free_and_abort;
    res = calloc(2 * size, sizeof(int));
    if (res == NULL)
        goto free_and_abort;
    for (int i = 0; i < n; ++i) {
        tmp = scanf("%d", &a[i]);
        if (tmp != 1)
            goto free_and_abort;
    }
    for (int i = 0; i < m; ++i) {
        tmp = scanf("%d", &b[i]);
        if (tmp != 1)
            goto free_and_abort;
    }
    tmp = multiply(a, b, res, size);
    if (tmp == -1)
        goto free_and_abort;
    tmp = n + m;
    while (tmp > 0 && res[tmp - 1] == 0)
        --tmp;
    for (int i = 0; i < tmp; ++i)
        printf("%d ", res[i]);
    printf("\n");
    free(a);
    free(b);
    free(res);
    return 0;
free_and_abort:
    free(a);
    free(b);
    free(res);
    abort();
}

int multiply(int const* restrict a, int const* restrict b, int* res, int n)
{
    if (n <= 64) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res[i + j] += a[i] * b[j];
            }
        }
        return 0;
    } else {
        int mid = n / 2;
        int* btmp = NULL;
        int* E = NULL;
        btmp = aligned_alloc(64, n * sizeof(int));
        if (btmp == NULL)
            goto free_and_fail;
        E = aligned_alloc(64, n * sizeof(int));
        if (E == NULL)
            goto free_and_fail;
        memset(btmp, 0, n * sizeof(unsigned));
        memset(E, 0, n * sizeof(unsigned));
        int* atmp = btmp + mid;
        for (int i = 0; i < mid; i++) {
            atmp[i] = a[i] + a[i + mid];
            btmp[i] = b[i] + b[i + mid];
        }
        multiply(atmp, btmp, E, mid);
        multiply(a + 0, b + 0, res, mid);
        multiply(a + mid, b + mid, res + n, mid);
        for (int i = 0; i < mid; i++) {
            int const tmp = res[i + mid];
            res[i + mid] += E[i] - res[i] - res[i + 2 * mid];
            res[i + 2 * mid] += E[i + mid] - tmp - res[i + 3 * mid];
        }
        free(btmp);
        free(E);
        return 0;
    free_and_fail:
        free(btmp);
        free(E);
        return -1;
    }
}
