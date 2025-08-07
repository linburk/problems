#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int reverse_entries(char *hay, char *ndl);

int main()
{
	int err;
	char *ndl = NULL, *hay = NULL;
	int ndl_len, hay_len;
	err = scanf("%d", &ndl_len);
	if (err != 1 || ndl_len <= 0)
		abort();
	ndl = malloc(ndl_len + 1);
	if (ndl == NULL)
		abort();
	getchar();
	if (fgets(ndl, ndl_len + 1, stdin) == NULL)
		goto free_and_abort;
	err = scanf("%d", &hay_len);
	if (err != 1 || hay_len <= 0)
		abort();
	hay = malloc(hay_len + 1);
	if (hay == NULL)
		goto free_and_abort;
	getchar();
	if (fgets(hay, hay_len + 1, stdin) == NULL)
		goto free_and_abort;
	err = reverse_entries(hay, ndl);
	if (err == -1)
		goto free_and_abort;
	printf("%s\n", hay);
free_and_success:
	free(ndl);
	free(hay);
	return 0;
free_and_abort:
	free(ndl);
	free(hay);
	abort();
}

void reverse(char *s, int len)
{
	char tmp;
	for (int i = 0; i < len / 2; ++i) {
		tmp = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = tmp;
	}
}

char *next_match(char *hay, regex_t *reg, int *match_len)
{
	regmatch_t match;
	int res = regexec(reg, hay, 1, &match, 0);
	if (res == REG_NOMATCH)
		return NULL;
	*match_len = match.rm_eo - match.rm_so;
	return hay + match.rm_so;
}

int reverse_entries(char *hay, char *ndl)
{
	int err;
	regex_t reg;
	char *i = hay;
	int match_len;
	err = regcomp(&reg, ndl, REG_EXTENDED);
	if (err != 0)
		return -1;
	for (;;) {
		i = next_match(i, &reg, &match_len);
		if (i == NULL)
			break;
		reverse(i, match_len);
		i += match_len;
	}
	regfree(&reg);
	return 0;
}
