#include <stdlib.h>
#include <string.h>

#if 1
#define N 0
#endif

void multiply(unsigned (*A)[N], unsigned (*B)[N], unsigned (*res)[N], unsigned m)
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            res[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                res[i][j] = (res[i][j] + (A[i][k] * B[k][j] % m)) % m;
            }
        }
    }
}

void powNxN(unsigned (*A)[N], unsigned k, unsigned m)
{
    unsigned res[N][N];
    unsigned tmp[N][N];
    memset(res, 0, sizeof(int) * N * N);
    for (int i = 0; i < N; ++i)
        res[i][i] = 1;
    for (; k > 0; k >>= 1) {
        if (k & 1) {
            multiply(res, A, tmp, m);
            memcpy(res, tmp, sizeof(int) * N * N);
        }
        multiply(A, A, tmp, m);
        for (int i = 0; i < N; ++i) {
            memcpy(A[i], tmp[i], sizeof(int) * N);
        }
    }
    for (int i = 0; i < N; ++i) {
        memcpy(A[i], res[i], sizeof(int) * N);
    }
}
