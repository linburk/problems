#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void patpreproc(char const *needle, int *needle_lps)
{
	int i;
	int len = strlen(needle);
	needle_lps[0] = 0;
	for (i = 1; i < len; ++i) {
		needle_lps[i] = needle_lps[i - 1];
		while (needle_lps[i] > 0 &&
			   tolower(needle[needle_lps[i]]) != tolower(needle[i]))
			needle_lps[i] = needle_lps[needle_lps[i] - 1];
		needle_lps[i] += tolower(needle[i]) == tolower(needle[needle_lps[i]]);
	}
}

int strstrci(char const *needle, int const *needle_lps, char const *haystack)
{
	int i, match, k;
	int needle_len = strlen(needle);
	int len = strlen(haystack);
	int res = 0;
	for (i = 0, k = 0; i < len; ++i) {
		while (k > 0 && tolower(needle[k]) != tolower(haystack[i]))
			k = needle_lps[k - 1];
		k += tolower(haystack[i]) == tolower(needle[k]);
		if (k == needle_len) {
			++res;
			k = 0;
		}
	}
	return res;
}

int main()
{
	int err;
	char *ndl, *hay;
	int len_ndl, len_hay;
	int res;
	int *p;
	err = scanf("%d", &len_hay);
	if (err != 1)
		abort();
	hay = malloc(len_hay + 1);
	if (hay == NULL)
		abort();
	err = scanf("%s", hay);
	if (err != 1) {
		free(hay);
		abort();
	}
	err = scanf("%d", &len_ndl);
	if (err != 1) {
		free(hay);
		abort();
	}
	ndl = malloc(len_ndl + 1);
	if (ndl == NULL) {
		free(hay);
		abort();
	}
	err = scanf("%s", ndl);
	if (err != 1) {
		free(hay);
		free(ndl);
		abort();
	}
	p = malloc(sizeof(int) * (len_ndl));
	if (p == NULL) {
		free(ndl);
		free(hay);
		abort();
	}
	patpreproc(ndl, p);
	res = strstrci(ndl, p, hay);
	printf("%d\n", res);
	free(ndl);
	free(hay);
	free(p);
	return 0;
}
