#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

long long gcd(long long a, long long b)
{
	while (a != 0) {
		int c = b % a;
		b = a;
		a = c;
	}
	assert(b);
	return b;
}

long long lcm(long long a, long long b)
{
	return a * b / gcd(a, b);
}

long long f(int n)
{
	long long res = 1;
	for (int i = 2; i <= n; ++i) {
		res = lcm(res, i);
	}
	return res;
}

int main()
{
	int n;
	long long res;
	int cnt = scanf("%d", &n);
	if (cnt != 1)
		abort();
	res = f(n);
	printf("%lld\n", res);
	return 0;
}
