#include <string.h>
#include <ctype.h>

char *strstrci(char const *needle, char const *haystack)
{
	int ndl_len, hay_len;
	int i, j, iscmp;
	ndl_len = strlen(needle);
	hay_len = strlen(haystack);
	for (i = 0; i <= hay_len - ndl_len; ++i) {
		iscmp = 1;
		for (j = 0; iscmp && j < ndl_len; ++j)
			iscmp &= toupper(needle[j]) == toupper(haystack[i + j]);
		if (iscmp)
			return (char *)haystack + i;
	}
	return NULL;
}
