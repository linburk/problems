#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n;
	int cnt = scanf("%d", &n);
	if (cnt != 1)
		abort();
	if (n == 0) {
		printf("NO\n");
	} else {
		int hi, lo;
		for (int i = sizeof(int) * CHAR_BIT - 1; i >= 0; --i) {
			if (n & (1 << i)) {
				hi = i;
				break;
			}
		}
		for (int i = 0; i < sizeof(int) * CHAR_BIT; ++i) {
			if (n & (1 << i)) {
				lo = i;
				break;
			}
		}
		printf("%d %d\n", hi, lo);
	}
	return 0;
}
