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

int main()
{
	uint64_t x;
	int res;
	int cnt = scanf("%llu", &x);
	srand(42);
	if (cnt != 1)
		abort();
	res = is_primec(x);
	printf("%d\n", res);
	return 0;
}
