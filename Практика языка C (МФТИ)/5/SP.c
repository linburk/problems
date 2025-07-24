#include <string.h>
#include <stdlib.h>

int count_entries(char const *hay, int hay_len, char const *ndl, int ndl_len)
{
	int ret = 0;
	char const *i;
	for (i = hay; i < hay + hay_len;) {
		i = strstr(i, ndl);
		if (i == NULL)
			break;
		++ret;
		i += ndl_len;
	}
	return ret;
}

char *replace(char *str, char const *from, char const *to)
{
	char *ret;
	int i, j;
	int cnt_entries;
	int ret_len, str_len, from_len, to_len;
	str_len = strlen(str);
	from_len = strlen(from);
	to_len = strlen(to);
	cnt_entries = count_entries(str, str_len, from, from_len);
	ret_len = str_len + (to_len - from_len) * cnt_entries;
	ret = malloc(ret_len + 1);
	if (ret == NULL)
		return NULL;
	for (i = 0, j = 0; i < str_len;) {
		if (i + from_len <= str_len && memcmp(str + i, from, from_len) == 0) {
			memcpy(ret + j, to, to_len);
			i += from_len;
			j += to_len;
			continue;
		}
		ret[j++] = str[i++];
	}
	ret[ret_len] = '\0';
	return ret;
}
