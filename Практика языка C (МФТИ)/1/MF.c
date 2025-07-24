#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long matrix_T;
typedef matrix_T** matrix;

matrix alloc_matrix(unsigned n, unsigned m);
void free_matrix(matrix a, unsigned n);

matrix alloc_matrix(unsigned n, unsigned m)
{
    matrix a = (matrix)calloc(n, sizeof(matrix_T*));
    if (a == NULL)
        return NULL;
    for (int i = 0; i < n; ++i) {
        a[i] = (matrix_T*)calloc(n, sizeof(matrix_T));
        if (a[i] == NULL) {
            free_matrix(a, n);
            return NULL;
        }
    }
    return a;
}
void free_matrix(matrix a, unsigned n)
{
    if (a == NULL)
        return;
    for (int i = 0; i < n; ++i) {
        free(a[i]);
    }
    free(a);
}

// a = [l * m], b = [m * n]
void multiply(matrix a, matrix b, matrix restrict res, unsigned l, unsigned m, unsigned n, unsigned long long mod)
{
    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < n; ++j) {
            res[i][j] = 0;
        }
    }
    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < m; ++k) {
                res[i][j] = (res[i][j] + a[i][k] * b[k][j] % mod) % mod;
            }
        }
    }
}

matrix bpow(matrix a, unsigned n, unsigned long long p, unsigned long long mod)
{
    matrix res = alloc_matrix(n, n);
    matrix f = alloc_matrix(n, n);
    matrix tmp = alloc_matrix(n, n);
    if (res == NULL || f == NULL || tmp == NULL)
        goto free_and_fail;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            f[i][j] = a[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        res[i][i] = 1;
    }
    for (; p > 0; p >>= 1) {
        if (p & 1) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    tmp[i][j] = res[i][j];
                }
            }
            multiply(tmp, f, res, n, n, n, mod);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                tmp[i][j] = f[i][j];
            }
        }
        multiply(tmp, tmp, f, n, n, n, mod);
    }
    free_matrix(f, n);
    free_matrix(tmp, n);
    return res;
free_and_fail:
    free_matrix(res, n);
    free_matrix(f, n);
    free_matrix(tmp, n);
    return NULL;
}

int main()
{
    matrix a, res;
    unsigned long long p, mod;
    a = alloc_matrix(2, 2);
    if (a == NULL)
        abort();
    int cnt = scanf("%llu%llu%llu%llu%llu%llu", &a[0][0], &a[0][1], &a[1][0], &a[1][1], &p, &mod);
    if (cnt != 6 || mod == 0)
        goto free_and_abort;
    res = bpow(a, 2, p, mod);
    if (res == NULL)
        goto free_and_abort;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            printf("%llu ", res[i][j]);
        }
    }
    free_matrix(a, 2);
    free_matrix(res, 2);
    return 0;
free_and_abort:
    free_matrix(a, 2);
    free_matrix(res, 2);
    abort();
}
