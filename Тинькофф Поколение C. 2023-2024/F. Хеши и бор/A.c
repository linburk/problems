#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
		hash_memory[i][0] = arr[i] + 1 + hash_memory[i + 1][0] * f1;
		hash_memory[i][1] =
			(arr[i] % m2 + 1 + (hash_memory[i + 1][1] * f2) % m2) % m2;
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
	scanf("%s", s);
	int64_t N = strlen(s);
	long long **hash_mem = (long long **)malloc(sizeof(long long *) * (N + 1));
	for (int i = 0; i <= N; i++) {
		hash_mem[i] = (long long *)malloc(sizeof(long long) * 2);
	}
	HASH_INITIALIZE(s, hash_mem, N);
	int m;
	scanf("%d", &m);
	int64_t res1[2], res2[2];
	while (m--) {
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		get_hash(a - 1, b, hash_mem, powers, res1);
		get_hash(c - 1, d, hash_mem, powers, res2);
		if (res1[0] == res2[0] && res1[1] == res2[1]) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}
	}
	return 0;
}
