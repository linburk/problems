#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef unsigned long long hs_hash_T;

hs_hash_T hs_get_hash(void const *data, int data_size)
{
	hs_hash_T ret = 1;
	char const *pcdata = (char const *)data;
	int const a = 471;
	int const b = 597;
	for (int i = 0; i < data_size; ++i)
		ret = (a * ret + b) + pcdata[i];
	return ret;
}

struct node {
	struct node *next;
	void *data;
	int data_size;
};

struct bk_bucket {
	struct node *top;
};

struct bk_bucket *bk_new_bucket(int *err)
{
	struct bk_bucket *ret;
	ret = malloc(sizeof(struct bk_bucket));
	if (ret == NULL) {
		*err = -1;
		return NULL;
	}
	return ret;
}
void bk_delete_bucket(struct bk_bucket *bucket)
{
	free(bucket);
}

static void *data_copy(void const *data, int data_size, int *err)
{
	void *ret;
	*err = 0;
	ret = malloc(data_size);
	if (ret == NULL) {
		*err = -1;
		return NULL;
	}
	memcpy(ret, data, data_size);
	return ret;
}

static void nd_constructor(struct node *node, void const *data, int data_size,
						   int *err)
{
	*err = 0;
	node->data = data_copy(data, data_size, err);
	if (*err == -1)
		return;
	node->data_size = data_size;
	return;
}

static void nd_destructor(struct node *node)
{
	free(node->data);
	return;
}

void bk_constructor(struct bk_bucket *bucket)
{
	bucket->top = NULL;
	return;
}

void bk_destructor(struct bk_bucket *bucket)
{
	struct node *tmp;
	if (bucket == NULL)
		return;
	while (bucket->top != NULL) {
		tmp = bucket->top;
		bucket->top = tmp->next;
		nd_destructor(tmp);
		free(tmp);
	}
	return;
}

static int bk_summem(struct bk_bucket *bucket)
{
	int ret = 0;
	struct node *i = bucket->top;
	while (i != NULL) {
		ret += i->data_size;
		i = i->next;
	}
	return ret;
}

static int bk_size(struct bk_bucket *bucket)
{
	int ret = 0;
	struct node *i = bucket->top;
	while (i != NULL) {
		++ret;
		i = i->next;
	}
	return ret;
}

void bk_add(struct bk_bucket *bucket, void const *data, int data_size, int *err)
{
	struct node *add = malloc(sizeof(struct node));
	*err = 0;
	if (add == NULL) {
		*err = -1;
		return;
	}
	nd_constructor(add, data, data_size, err);
	if (*err == -1) {
		free(add);
		return;
	}
	add->next = bucket->top;
	bucket->top = add;
	return;
}

void bk_delete(struct bk_bucket *bucket, void const *data, int data_size)
{
	struct node *prev = NULL;
	struct node *i = bucket->top;
	while (i != NULL) {
		if (i->data_size != data_size) {
			i = i->next;
			continue;
		}
		if (memcmp(i->data, data, data_size) == 0) {
			if (prev == NULL)
				bucket->top = i->next;
			else
				prev->next = i->next;
			nd_destructor(i);
			free(i);
			break;
		}
		prev = i;
		i = i->next;
	}
	return;
}

int bk_count(struct bk_bucket *bucket, void const *data, int data_size)
{
	int ret = 0;
	struct node *i = bucket->top;
	while (i != NULL) {
		if (i->data_size != data_size) {
			i = i->next;
			continue;
		}
		ret += memcmp(i->data, data, data_size) == 0;
		i = i->next;
	}
	return ret;
}

void bk_to_data(struct bk_bucket *bucket, void **data, int **data_sizes,
				int *count, int *err)
{
	int nelts, summem, passed;
	char *pcdata;
	struct node *i;
	*err = 0;
	summem = bk_summem(bucket);
	nelts = bk_size(bucket);
	*data = malloc(summem);
	if (*data == NULL) {
		*err = -1;
		return;
	}
	*data_sizes = malloc(nelts * sizeof(int));
	if (*data_sizes == NULL) {
		*err = -1;
		free(*data);
		return;
	}
	i = bucket->top;
	pcdata = (char *)(*data);
	passed = 0;
	while (i != NULL) {
		memcpy(pcdata, i->data, i->data_size);
		*data_sizes[passed] = i->data_size;
		pcdata += i->data_size;
		i = i->next;
		++passed;
	}
	*count = nelts;
	return;
}

#define BUCKETS_START 31
#define REALLOC_RATIO 3
#define MAX_LOAD_FACTOR 1.0

struct ht_hash_set {
	struct bk_bucket **buckets;
	int bucket_count;
	int elem_count;
};

struct ht_hash_set *ht_new_hash_set(int *err)
{
	struct ht_hash_set *ret;
	ret = malloc(sizeof(struct ht_hash_set));
	if (ret == NULL) {
		*err = -1;
		return NULL;
	}
	return ret;
}
void ht_delete_hash_set(struct ht_hash_set *table)
{
	free(table);
	return;
}

static int ht_get_pos(void const *data, int data_size, int bucket_count)
{
	hs_hash_T hash = hs_get_hash(data, data_size);
	return (unsigned long long)hash % bucket_count;
}

static void ht_delete_buckets(struct bk_bucket **buckets, int bucket_count)
{
	int i;
	for (i = 0; i < bucket_count; ++i) {
		bk_destructor(buckets[i]);
		bk_delete_bucket(buckets[i]);
	}
	return;
}

static struct bk_bucket **ht_create_buckets(int bucket_count, int *err)
{
	struct bk_bucket **ret;
	int i;
	*err = 0;
	ret = calloc(bucket_count, sizeof(struct bk_bucket *));
	if (ret == NULL) {
		*err = -1;
		return NULL;
	}
	for (i = 0; i < bucket_count; ++i) {
		ret[i] = bk_new_bucket(err);
		if (*err == -1) {
			ht_delete_buckets(ret, bucket_count);
			free(ret);
			return NULL;
		}
		bk_constructor(ret[i]);
	}
	return ret;
}

static void ht_insert_to_buckets(struct bk_bucket **buckets, int bucket_count,
								 void const *data, int data_size, int *err)
{
	int pos;
	*err = 0;
	pos = ht_get_pos(data, data_size, bucket_count);
	bk_add(buckets[pos], data, data_size, err);
	return;
}

static void ht_insert_all_to_buckets(struct bk_bucket **buckets,
									 int bucket_count, void const **data,
									 int *data_sizes, int count, int *err)
{
	int i;
	*err = 0;
	for (i = 0; i < count; ++i) {
		ht_insert_to_buckets(buckets, bucket_count, data[i], data_sizes[i],
							 err);
		if (*err == -1)
			return;
	}
	return;
}

static void ht_realloc(struct ht_hash_set *table, int *err)
{
	struct bk_bucket **new_buckets;
	int new_bucket_count, count, i;
	void *data;
	int *data_sizes;
	*err = 0;
	new_bucket_count = table->buckets ? table->bucket_count * REALLOC_RATIO :
										BUCKETS_START;
	new_buckets = ht_create_buckets(new_bucket_count, err);
	if (*err == -1)
		return;
	for (i = 0; i < table->bucket_count; ++i) {
		bk_to_data(table->buckets[i], &data, &data_sizes, &count, err);
		if (*err == -1) {
			ht_delete_buckets(new_buckets, new_bucket_count);
			return;
		}
		ht_insert_all_to_buckets(new_buckets, new_bucket_count, data,
								 data_sizes, count, err);
		if (*err == -1) {
			ht_delete_buckets(new_buckets, new_bucket_count);
			free(data);
			free(data_sizes);
			return;
		}
		free(data);
		free(data_sizes);
	}
	ht_delete_buckets(table->buckets, table->bucket_count);
	table->buckets = new_buckets;
	table->bucket_count = new_bucket_count;
	return;
}

void ht_constructor(struct ht_hash_set *table)
{
	table->buckets = NULL;
	table->bucket_count = 0;
	table->elem_count = 0;
	return;
}
void ht_destructor(struct ht_hash_set *table)
{
	if (table == NULL)
		return;
	ht_delete_buckets(table->buckets, table->bucket_count);
	free(table->buckets);
	return;
}

void ht_add(struct ht_hash_set *table, void const *data, int data_size,
			int *err)
{
	if (!table->buckets ||
		MAX_LOAD_FACTOR < table->elem_count * 1.L / table->bucket_count) {
		ht_realloc(table, err);
		if (*err == -1)
			return;
	}
	ht_insert_to_buckets(table->buckets, table->bucket_count, data, data_size,
						 err);
	return;
}
void ht_delete(struct ht_hash_set *table, void const *data, int data_size)
{
	int pos;
	pos = ht_get_pos(data, data_size, table->bucket_count);
	bk_delete(table->buckets[pos], data, data_size);
	return;
}
int ht_count(struct ht_hash_set *table, void const *data, int data_size)
{
	int pos, ret;
	pos = ht_get_pos(data, data_size, table->bucket_count);
	ret = bk_count(table->buckets[pos], data, data_size);
	return ret;
}

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
