#pragma GCC target("avx2")
#include <cstdint>
#include <immintrin.h>

alignas(32) int t[8] = { 0 };
int getMindStone(const int* a, int n, int k)
{
    --k;
    __m256i rk = _mm256_set1_epi32(k);
    __m256i rc = _mm256_setzero_si256();
    int res = 0;
    int i = 0;
    for (; i < n && (uintptr_t)(&a[i]) & 31; ++i) {
        res += a[i] > k;
    }
    for (; i + 8 < n; i += 8) {
        __m256i c = _mm256_load_si256((__m256i*)&a[i]);
        rc = _mm256_add_epi32(rc, _mm256_cmpgt_epi32(c, rk));
    }
    _mm256_store_si256((__m256i*)&t, rc);
    for (int j = 0; j < 8; ++j) {
        res -= t[j];
    }
    for (; i < n; ++i) {
        res += a[i] > k;
    }
    return res;
}

#if 0
#include <iostream>
int arr[1000];
int main()
{
    int n, k;
    std::cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    std::cout << getMindStone(arr, n, k) << "\n";
}
#endif
