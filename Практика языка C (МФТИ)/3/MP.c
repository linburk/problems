#include <stdio.h>
#include <stdlib.h>

long long* multiply(int*, int, int*, int);

int main()
{
    int tmp;
    int n, m;
    int *a = NULL, *b = NULL;
    long long* res = NULL;
    tmp = scanf("%d%d", &n, &m);
    if (tmp != 2 || n <= 0 || m <= 0)
        abort();
    a = calloc(n, sizeof(int));
    if (a == NULL)
        goto free_and_abort;
    b = calloc(m, sizeof(int));
    if (b == NULL)
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
    res = multiply(a, n, b, m);
    if (res == NULL)
        goto free_and_abort;
    tmp = n + m;
    while (tmp > 0 && res[tmp - 1] == 0)
        --tmp;
    for (int i = 0; i < tmp; ++i)
        printf("%lld ", res[i]);
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

long long* multiply(int* a, int n, int* b, int m)
{
    long long* res = NULL;
    res = calloc(n + m, sizeof(long long));
    if (res == NULL)
        return NULL;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            res[i + j] += a[i] * b[j];
        }
    }
    return res;
}
