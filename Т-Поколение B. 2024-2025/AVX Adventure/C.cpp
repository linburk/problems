#pragma GCC target("avx2")
#include <cstdint>
#include <immintrin.h>

alignas(32) int t[8] = { 0 };
void getTimeStone(int* a, int n)
{

    int i = 0;
    for (; i < n && (uintptr_t)(&a[i]) & 31; ++i) {
        a[i] = n - i;
    }
    for (int j = 0; j < 8; ++j) {
        t[j] = -(i + j);
    }
    __m256i ra = _mm256_load_si256((__m256i*)&t);
    __m256i rb = _mm256_set1_epi32(n);
    __m256i rm = _mm256_set1_epi32(-8);
    for (; i + 8 < n; i += 8) {
        _mm256_store_si256((__m256i*)&a[i], _mm256_add_epi32(rb, ra));
        ra = _mm256_add_epi32(ra, rm);
    }
    for (; i < n; ++i) {
        a[i] = n - i;
    }
}

#if 0
#include <iostream>
int arr[1000];
int main()
{
    int n;
    std::cin >> n;
    getTimeStone(arr, n);
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}
#endif
