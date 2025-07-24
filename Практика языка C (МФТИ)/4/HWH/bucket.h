#pragma once

struct bk_bucket;

struct bk_bucket *bk_new_bucket(int *err);
void bk_delete_bucket(struct bk_bucket *);

void bk_constructor(struct bk_bucket *);
void bk_destructor(struct bk_bucket *);

void bk_add(struct bk_bucket *, void const *data, int data_size, int *err);
void bk_delete(struct bk_bucket *, void const *data, int data_size);
int bk_count(struct bk_bucket *, void const *data, int data_size);
void bk_to_data(struct bk_bucket *bucket, void **data, int **data_sizes,
				int *count, int *err);
