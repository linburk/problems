#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "hash_set.h"

int scan_word(char **s, int *len)
{
	*len = 0;
	while (isspace((*s)[0]))
		++(*s);
	while (!isspace((*s)[*len]) && (*s)[*len] != '\0')
		++(*len);
	if ((*s)[*len] == '\0')
		return 1;
	return 0;
}

void add_words(struct ht_hash_set *table, char *txt, int *err)
{
	int len, tmp;
	*err = 0;
	for (;;) {
		tmp = scan_word(&txt, &len);
		if (len > 0)
			ht_add(table, txt, len, err);
		if (*err == -1)
			return;
		if (tmp == 1)
			break;
		txt += len;
	}
	return;
}

int *count_entries(struct ht_hash_set *table, char *words, int count, int *err)
{
	int len, i, tmp;
	int *ret;
	*err = 0;
	ret = calloc(count, sizeof(int));
	if (ret == NULL) {
		*err = -1;
		return NULL;
	}
	for (i = 0; i < count; ++i) {
		tmp = scan_word(&words, &len);
		ret[i] = ht_count(table, words, len);
		words += len;
	}
	return ret;
}

int main()
{
	int err;
	int i;
	struct ht_hash_set *table = NULL;
	char *txt = NULL, *srch = NULL;
	int *entries = NULL;
	int txt_len, srch_len;
	size_t txt_mem, srch_mem;
	int srch_cnt;
	table = ht_new_hash_set(&err);
	if (err == -1)
		goto free_and_fail;
	ht_constructor(table);
	err = scanf("%d", &srch_cnt);
	if (err != 1)
		goto free_and_fail;
	err = scanf("%d", &txt_len);
	if (err != 1)
		goto free_and_fail;
	getchar();
	err = getline(&txt, &txt_mem, stdin);
	if (err == -1)
		goto free_and_fail;
	err = scanf("%d", &srch_len);
	if (err != 1)
		goto free_and_fail;
	getchar();
	err = getline(&srch, &srch_mem, stdin);
	if (err == -1)
		goto free_and_fail;
	add_words(table, txt, &err);
	if (err == -1)
		goto free_and_fail;
	entries = count_entries(table, srch, srch_cnt, &err);
	if (err == -1)
		goto free_and_fail;
	for (i = 0; i < srch_cnt; ++i)
		printf("%d ", entries[i]);
	printf("\n");
	free(txt);
	free(srch);
	free(entries);
	ht_destructor(table);
	ht_delete_hash_set(table);
	return 0;
free_and_fail:
	free(txt);
	free(srch);
	free(entries);
	ht_destructor(table);
	ht_delete_hash_set(table);
	return 1;
}
