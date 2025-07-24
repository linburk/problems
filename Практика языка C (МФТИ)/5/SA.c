#include <stdlib.h>
#include <string.h>

char *strcat_r(char *dest, const char *src, int *bufsz)
{
	int i;
	int dest_len, src_len;
	dest_len = strlen(dest);
	src_len = strlen(src);
	if (dest_len + src_len + 1 > *bufsz) {
		dest = realloc(dest, dest_len + src_len + 1);
		if (dest == NULL)
			return NULL;
		*bufsz = dest_len + src_len + 1;
	}
	for (i = 0; i < src_len; ++i)
		dest[dest_len + i] = src[i];
	dest[dest_len + src_len] = '\0';
	return dest;
}
