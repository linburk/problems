#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_entries(char *hay, char *ndl);

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
	reverse_entries(hay, ndl);
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

void reverse_entries(char *hay, char *ndl)
{
	char *i = hay;
	int ndl_len = strlen(ndl);
	for (;;) {
		i = strstr(i, ndl);
		if (i == NULL)
			break;
		reverse(i, ndl_len);
		i += ndl_len;
	}
}
