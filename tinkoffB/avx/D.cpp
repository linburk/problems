#pragma GCC target("avx2")
#include <immintrin.h>
#include <stdint.h>

void getRealityStone(char* s, int n)
{
    int i = 0;
    for (; i < n && (uintptr_t)&(s[i]) & 31; ++i) {
        s[i] ^= 1 << 5;
        s[i] ^= (s[i] == 0b01111111) << 5;
    }
    __m256i r32 = _mm256_set1_epi8(0b00100000);
    __m256i req = _mm256_set1_epi8(0b01111111);
    for (; i + 32 < n; i += 32) {
        __m256i rc = _mm256_load_si256((__m256i*)&s[i]);
        rc = _mm256_xor_si256(rc, r32);
        __m256i rb = _mm256_cmpeq_epi8(rc, req);
        rb = _mm256_and_si256(rb, r32);
        rc = _mm256_xor_si256(rc, rb);
        _mm256_store_si256((__m256i*)&s[i], rc);
    }
    for (; i < n; ++i) {
        s[i] ^= 1 << 5;
        s[i] ^= (s[i] == 0b01111111) << 5;
    }
}

#if 0
#include <stdio.h>
#include <string.h>
char s[10000];
int main()
{
    scanf("%s", s);
    getRealityStone(s, strlen(s));
    printf("%s\n", s);
}
#endif
