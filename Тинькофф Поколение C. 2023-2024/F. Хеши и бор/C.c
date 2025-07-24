#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const int64_t MAXLEN = 1E5 + 1;
const int64_t f1 = 31, f2 = 37;
const int64_t m2 = 1E9 + 7;
int64_t powers[MAXLEN][2];

void POWERS_INITIALIZE(int64_t powers[][2])
{
	powers[0][0] = powers[0][1] = 1;
	for (int64_t i = 1; i < MAXLEN; i++) {
		powers[i][0] = powers[i - 1][0] * f1;
		powers[i][1] = (powers[i - 1][1] % m2 * f2) % m2;
	}
}

void HASH_INITIALIZE(char *arr, long long **hash_memory, int64_t N)
{
	hash_memory[N][0] = 0;
	hash_memory[N][1] = 0;
	for (int64_t i = N - 1; i >= 0; i--) {
		hash_memory[i][0] = arr[i] - 'a' + 1 + hash_memory[i + 1][0] * f1;
		hash_memory[i][1] =
			(arr[i] % m2 - 'a' + 1 + (hash_memory[i + 1][1] * f2) % m2) % m2;
	}
}

void get_hash(int64_t l, int64_t r, long long **hash_memory,
			  int64_t powers[][2], int64_t result[2])
{
	result[0] = hash_memory[l][0] - hash_memory[r][0] * powers[r - l][0];
	result[1] =
		(hash_memory[l][1] - (hash_memory[r][1] * powers[r - l][1]) % m2 + m2) %
		m2;
}

int32_t main(int argc, char *argv[])
{
#ifdef __APPLE__
	freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
	freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
	POWERS_INITIALIZE(powers);
	char s[MAXLEN];
	char s_rev[MAXLEN];
	scanf("%s", s);
	ll N = strlen(s);
	long long **hash_mem = (long long **)calloc(N + 1, sizeof(long long *));
	for (int i = 0; i <= N; i++) {
		hash_mem[i] = (long long *)calloc(2, sizeof(long long));
	}
	long long **hash_mem_rev = (long long **)calloc(N + 1, sizeof(long long *));
	for (int i = 0; i <= N; i++) {
		hash_mem_rev[i] = (long long *)calloc(2, sizeof(long long));
	}
	for (int i = 0; i < N; i++)
		s_rev[i] = s[N - i - 1];
	HASH_INITIALIZE(s, hash_mem, N);
	HASH_INITIALIZE(s_rev, hash_mem_rev, N);
	int64_t get1[2], get2[2];
	int64_t count = 0;
	for (int i = 0; i < N; i++) {
		ll l = 0;
		ll r = (N - i - 1 > i ? i : N - i - 1) + 1;
		while (r - l > 1) {
			ll m = (r + l) >> 1;
			get_hash(i, i + m + 1, hash_mem, powers, get1);
			get_hash(N - i - 1, N - i + m, hash_mem_rev, powers, get2);
			if (get1[0] == get2[0] && get2[1] == get1[1]) {
				l = m;
			} else {
				r = m;
			}
		}
		count += l + 1;
	}
	for (int i = 0; i < N - 1; i++) {
		if (s[i] == s[i + 1]) {
			ll l = 0;
			ll r = (N - i - 2 > i ? i : N - i - 2) + 1;
			while (r - l > 1) {
				ll m = (r + l) >> 1;
				get_hash(i + 1, i + 1 + m + 1, hash_mem, powers, get1);
				get_hash(N - i - 1, N - i + m, hash_mem_rev, powers, get2);
				if (get1[0] == get2[0] && get2[1] == get1[1]) {
					l = m;
				} else {
					r = m;
				}
			}
			count += l + 1;
		}
	}
	printf("%lld", count);
	return 0;
}
