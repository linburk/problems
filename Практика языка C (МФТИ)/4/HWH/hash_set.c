#include "hash_set.h"
#include "bucket.h"
#include "hash.h"
#include <stdlib.h>

#define BUCKETS_START 31
#define REALLOC_RATIO 3
#define MAX_LOAD_FACTOR 0.7

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

static void ht_bks_to_bks(struct bk_bucket **src, int src_count,
						  struct bk_bucket **dst, int dst_count, int *err)
{
	void *data;
	int *data_sizes;
	int count;
	int i;
	for (i = 0; i < src_count; ++i) {
		bk_to_data(src[i], &data, &data_sizes, &count, err);
		if (*err == -1)
			return;
		ht_insert_all_to_buckets(dst, dst_count, data, data_sizes, count, err);
		free(data);
		free(data_sizes);
		if (*err == -1)
			return;
	}
}

static void ht_realloc(struct ht_hash_set *table, int *err)
{
	struct bk_bucket **new_buckets;
	int new_bucket_count, i;
	*err = 0;
	new_bucket_count = table->buckets ? table->bucket_count * REALLOC_RATIO :
										BUCKETS_START;
	new_buckets = ht_create_buckets(new_bucket_count, err);
	if (*err == -1)
		return;
	ht_bks_to_bks(table->buckets, table->bucket_count, new_buckets,
				  new_bucket_count, err);
	if (*err == -1) {
		ht_delete_buckets(new_buckets, new_bucket_count);
		free(new_buckets);
		return;
	}
	ht_delete_buckets(table->buckets, table->bucket_count);
	free(table->buckets);
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
