#pragma GCC target("avx2")
#pragma GCC optimize("unroll-loops")
#include <assert.h>
#include <immintrin.h>
#include <stdint.h>
#include <stdio.h>

alignas(32) int t[8] = { 0 };

void print_register(__m256i r)
{
    _mm256_store_si256((__m256i*)&t[0], r);
    printf("reg: ");
    for (int i = 0; i < 8; ++i) {
        printf("%d ", t[i]);
    }
    printf("\n");
};

int getPowerStone(const int* a, const int* b, int n)
{
    int res = 0;
    int i = 0, j = 0;
    __m256i rr = _mm256_setzero_si256();
    __m256i rshift = _mm256_set_epi32(0, 7, 6, 5, 4, 3, 2, 1);
    for (; i + 8 <= n && j + 8 <= n;) {
        __m256i ra = _mm256_lddqu_si256((__m256i*)&a[i]);
        __m256i rb = _mm256_lddqu_si256((__m256i*)&b[j]);
        int fgr = a[i + 7] > b[j + 7];
        int fls = a[i + 7] < b[j + 7];
        int feq = a[i + 7] == b[j + 7];
        for (int k = 0; k < 8; ++k) {
            rr = _mm256_add_epi32(rr, _mm256_cmpeq_epi32(ra, rb));
            rb = _mm256_permutevar8x32_epi32(rb, rshift);
        }
        i += 8 * (feq || fls);
        j += 8 * (feq || fgr);
    }
    _mm256_store_si256((__m256i*)&t[0], rr);
    for (int k = 0; k < 8; ++k) {
        res -= t[k];
    }
    for (; i < n && j < n;) {
        int fgr = a[i] > b[j];
        int fls = a[i] < b[j];
        int feq = a[i] == b[j];
        i += feq || fls;
        j += feq || fgr;
        res += feq;
    }
    return res;
}

#if 0
int a[1000], b[1000];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &b[i]);
    }
    printf("%d\n", getPowerStone(a, b, n));
}
#endif
