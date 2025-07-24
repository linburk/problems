#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

void inverse_bit(unsigned char *arr, int len, int n)
{
	if (n >= len * CHAR_BIT)
		return;
	char mask = 1 << (n % CHAR_BIT);
	arr[n / CHAR_BIT] ^= mask;
}

int main()
{
	int n, bit;
	unsigned char *arr;
	int cnt = scanf("%d", &n);
	if (cnt != 1)
		abort();
	arr = calloc(n, sizeof(char));
	if (arr == NULL)
		abort();
	for (int i = 0; i < n; ++i) {
		int tmp;
		cnt = scanf("%d", &tmp);
		if (cnt != 1)
			goto free_and_abort;
		arr[i] = tmp;
	}
	cnt = scanf("%d", &bit);
	if (cnt != 1)
		goto free_and_abort;
	inverse_bit(arr, n, bit);
	for (int i = 0; i < n; ++i)
		printf("%d ", arr[i]);
	printf("\n");
	free(arr);
	return 0;
free_and_abort:
	free(arr);
	abort();
}
