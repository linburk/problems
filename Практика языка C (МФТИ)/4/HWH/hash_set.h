#pragma once

struct ht_hash_set;

struct ht_hash_set *ht_new_hash_set(int *err);
void ht_delete_hash_set(struct ht_hash_set *);

void ht_constructor(struct ht_hash_set *);
void ht_destructor(struct ht_hash_set *);

void ht_add(struct ht_hash_set *, void const *data, int data_size, int *err);
void ht_delete(struct ht_hash_set *, void const *data, int data_size);
int ht_count(struct ht_hash_set *, void const *data, int data_size);
