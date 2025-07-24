#define _POSIX_C_SOURCE 200809L
#include "bucket.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>

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
