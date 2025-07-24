#define _POSIX_C_SOURCE 200809L
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int err;
	char mail_pattern[] =
		"(([a-zA-Z0-9]+\\.)*[a-zA-Z0-9]+@[a-zA-Z]+\\.[a-zA-Z]+)";
	regex_t reg;
	char *str = NULL;
	size_t buf = 0;
	err = regcomp(&reg, mail_pattern, REG_EXTENDED);
	if (err != 0)
		abort();
	getline(&str, &buf, stdin);
	if (str == NULL) {
		regfree(&reg);
		abort();
	}
	err = regexec(&reg, str, 0, NULL, 0);
	printf("%d\n", !err);
	regfree(&reg);
	free(str);
	return 0;
}
