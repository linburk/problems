#pragma GCC target("avx2")
#include <algorithm>
#include <immintrin.h>
#include <stdint.h>

alignas(32) int t[8];
int getInfinityGauntlet(const int* a, int n)
{
    __m256i ra = _mm256_setzero_si256();
    int res = 0;
    int i = 0;
    for (; i < n && (uintptr_t)(&a[i]) & 31; ++i) {
        res = std::max(std::abs(a[i]), res);
    }
    for (; i + 8 < n; i += 8) {
        __m256i c = _mm256_load_si256((__m256i*)&a[i]);
        c = _mm256_abs_epi32(c);
        ra = _mm256_max_epi32(c, ra);
    }
    _mm256_store_si256((__m256i*)&t[0], ra);
    for (int j = 0; j < 8; ++j) {
        res = std::max(t[j], res);
    }
    for (; i < n; ++i) {
        res = std::max(std::abs(a[i]), res);
    }
    return res;
}

#if 0
#include <cassert>
#include <iostream>

int arr[100000];

int main()
{
    int n;
    std::cin >> n;
    int max_el = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
        max_el = std::max(max_el, std::abs(arr[i]));
    }
    std::cout << max_el << "\n"
              << getInfinityGauntlet(arr, n) << "\n";
}
#endif
