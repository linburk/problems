#pragma GCC target("avx2")
#include <cassert>
#include <cmath>
#include <cstdint>
#include <immintrin.h>

typedef struct {
    double x, y;
} Point;

alignas(32) double t[4] = { 0 };
double getSpaceStone(Point p, const Point* a, int n)
{
    double res = 0;
    int i = 0;
    for (; i < n && (uintptr_t)(&a[i]) & 31; ++i) {
        res += std::sqrt((a[i].x - p.x) * (a[i].x - p.x) + (a[i].y - p.y) * (a[i].y - p.y));
    }
    for (int j = 0; j < 4; j += 2) {
        t[j] = -p.x;
        t[j + 1] = -p.y;
    }
    __m256d rd = _mm256_load_pd(&t[0]);
    __m256d rs = _mm256_setzero_pd();
    for (; i + 2 < n; i += 2) {
        __m256d rb, rc;
        rb = _mm256_load_pd((double*)&a[i]);
        rb = _mm256_add_pd(rb, rd);
        rb = _mm256_mul_pd(rb, rb);
        rb = _mm256_hadd_pd(rb, rb);
        rb = _mm256_sqrt_pd(rb);
        rs = _mm256_add_pd(rs, rb);
    }
    _mm256_store_pd(&t[0], rs);
    for (int i = 0; i < 4; i += 2) {
        res += t[i];
    }
    for (; i < n; ++i) {
        res += std::sqrt((a[i].x - p.x) * (a[i].x - p.x) + (a[i].y - p.y) * (a[i].y - p.y));
    }
    return res;
}

#if 0
#include <random>
#include <stdio.h>
std::mt19937 ru32(42);
std::uniform_real_distribution<float> rf(-100, 100);
Point arr[1000];
int main()
{
    int n;
    scanf("%d", &n);
    Point p;
    p.x = rf(ru32);
    p.y = rf(ru32);
    double res = 0;
    for (int i = 0; i < n; ++i) {
        arr[i].x = rf(ru32);
        arr[i].y = rf(ru32);
        res += std::sqrt((arr[i].x - p.x) * (arr[i].x - p.x) + (arr[i].y - p.y) * (arr[i].y - p.y));
    }
    printf("%lf\n%lf\n", res, getSpaceStone(p, arr, n));
}
#endif
