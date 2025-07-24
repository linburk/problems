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
const int64_t m2 = 1E9 + 9;
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
	char p[MAXLEN];
	char s[MAXLEN];

	scanf("%s", p);
	scanf("%s", s);
	ll N = strlen(s);
	ll M = strlen(p);

	long long **hash_mem = (long long **)calloc(N + 1, sizeof(long long *));
	for (int i = 0; i <= N; i++) {
		hash_mem[i] = (long long *)calloc(2, sizeof(long long));
	}
	HASH_INITIALIZE(s, hash_mem, N);

	long long **hash_mem_p = (long long **)calloc(M + 1, sizeof(long long *));
	for (int i = 0; i <= M; i++) {
		hash_mem_p[i] = (long long *)calloc(2, sizeof(long long));
	}
	HASH_INITIALIZE(p, hash_mem_p, M);
	bool enter[MAXLEN];
	memset(enter, 0, MAXLEN);
	ll cnt = 0;
	int64_t get1[2], get2[2], get1r[2], get1l[2], get2l[2], get2r[2];

	for (ll right = M, left = 0; left <= N - M; left++, right = left + M) {
		get_hash(left, right, hash_mem, powers, get1);
		get_hash(0, M, hash_mem_p, powers, get2);
		if (get1[0] == get2[0] && get1[1] == get2[1] || M == 1) {
			enter[left] = 1;
			cnt++;
		} else {
			ll low = left, high = right;
			while (high - low > 1) {
				ll mid = (high + low) >> 1;
				get_hash(left, mid, hash_mem, powers, get1);
				get_hash(0, mid - left, hash_mem_p, powers, get2);
				if (get1[0] != get2[0] || get1[1] != get2[1]) {
					high = mid;
				} else {
					low = mid;
				}
			}
			ll incorrect_index = high - 1;
			if (incorrect_index > left) {
				get_hash(left, incorrect_index, hash_mem, powers, get1l);
				get_hash(0, incorrect_index - left, hash_mem_p, powers, get2l);
			}
			if (incorrect_index + 1 < right) {
				get_hash(incorrect_index + 1, right, hash_mem, powers, get1r);
				get_hash(incorrect_index - left + 1, M, hash_mem_p, powers,
						 get2r);
			}
			if (incorrect_index > left && incorrect_index + 1 < right) {
				if (get1l[0] == get2l[0] && get1l[1] == get2l[1] &&
					get1r[1] == get2r[1] && get1r[0] == get2r[0]) {
					enter[left] = 1;
					cnt++;
				}
			} else {
				if (incorrect_index > left &&
					(get1l[0] == get2l[0] && get1l[1] == get2l[1])) {
					enter[left] = 1;
					cnt++;
				}
				if (incorrect_index + 1 < right &&
					(get1r[1] == get2r[1] && get1r[0] == get2r[0])) {
					enter[left] = 1;
					cnt++;
				}
			}
		}
	}
	printf("%lld\n", cnt);
	for (int i = 0; i < N; i++) {
		if (enter[i]) {
			printf("%d ", i + 1);
		}
	}
	return 0;
}
