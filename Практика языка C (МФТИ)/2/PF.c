#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

uint64_t mul(uint64_t a, uint64_t b, uint64_t mod)
{
	uint64_t res = 0;
	b %= mod;
	for (int i = 0; i < 64; ++i) {
		res = (res + (b * ((a >> i) & 1))) % mod;
		b = (b << 1) % mod;
	}
	return res;
}

uint64_t b_pow(uint64_t a, uint64_t p, uint64_t mod)
{
	uint64_t res = 1;
	for (; p; p >>= 1) {
		if (p & 1)
			res = mul(res, a, mod);
		a = mul(a, a, mod);
	}
	return res;
}

int f_test(uint64_t x)
{
	if (x < 2)
		return 0;
	if (x == 2)
		return 1;
	uint32_t r = (uint32_t)(rand()) % (x - 2) + 2;
	return b_pow(r, x - 1, x) == 1;
}

int is_primec(uint64_t x)
{
	int res = 1;
	for (int i = 0; i < 100; ++i) {
		res *= f_test(x);
	}
	return res;
}

uint64_t find_mp(int n, int k)
{
	uint64_t a = 0;
	uint64_t b = 1;
	uint64_t res = 0;
	while (b < (1ULL << 60)) {
		uint64_t c = a * n + b * k;
		if (is_primec(c))
			res = c;
		a = b;
		b = c;
	}
	return res;
}

int main()
{
	int k, n;
	uint64_t res;
	int cnt = scanf("%u%u", &k, &n);
	srand(42);
	if (cnt != 2)
		abort();
	res = find_mp(n, k);
	printf("%llu\n", res);
	return 0;
}
