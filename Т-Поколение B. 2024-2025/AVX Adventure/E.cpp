#pragma GCC target("avx2")
#include <cassert>
#include <cstdint>
#include <immintrin.h>

alignas(32) long long t[4] = { 0 };
alignas(32) int m[8] = { 0 };
long long getSoulStone(const int* a, int n)
{
    int i = 0;
    long long sum = 0;
    for (; i < n && (uintptr_t)(&a[i]) & 31; ++i) {
        sum += a[i] * (1 - 2 * (i & 1));
    }
    for (int j = 0; j < 8; ++j) {
        m[j] = -1 * ((i + j) & 1);
    }
    __m256i rs = _mm256_setzero_si256();
    __m256i rr = _mm256_setzero_si256();
    __m256i minus = _mm256_load_si256((__m256i*)&m[0]);
    __m256i plus = ~minus;
    __m256i r1 = _mm256_set1_epi32(1);
    for (; i + 8 < n; i += 8) {
        __m256i ra, radd, rsub;
        ra = _mm256_load_si256((__m256i*)&a[i]);
        radd = plus & ra;
        rsub = ~(minus & ra);
        rsub = _mm256_add_epi32(rsub, r1);
        rs += radd + rsub;
        __m128i hxmm, lxmm;
        lxmm = _mm256_castsi256_si128(rs);
        hxmm = _mm256_extracti128_si256(rs, 1);
        rr = _mm256_add_epi64(rr, _mm256_cvtepi32_epi64(lxmm));
        rr = _mm256_add_epi64(rr, _mm256_cvtepi32_epi64(hxmm));
        rs = _mm256_setzero_si256();
    }
    _mm256_store_si256((__m256i*)&t[0], rr);
    for (int j = 0; j < 4; ++j) {
        sum += t[j];
    }
    for (; i < n; ++i) {
        sum += a[i] * (1 - 2 * (i & 1));
    }
    return sum;
}

#if 0
#include <random>
#include <stdio.h>
std::mt19937 ru32(42);
int arr[1000000];
int main()
{
    int n;
    scanf("%d", &n);
    long long res = 0;
    for (int i = 0; i < n; ++i) {
        arr[i] = ru32();
        res += arr[i] * (1 - 2 * (i & 1));
    }
    printf("%lld\n", getSoulStone(arr, n));
    printf("%lld\n", res);
}
#endif
