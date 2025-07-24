#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct list_T {
    struct list_T* next;
    int data;
};

struct list_T** bucket_sort(int*, int);
void free_buckets(struct list_T***, int);
void free_list(struct list_T**);
void print_buckets(struct list_T**, int);
void print_list(struct list_T*);

int main()
{
    int err;
    int* arr;
    int len;
    err = scanf("%d", &len);
    if (err != 1 || len <= 0)
        abort();
    arr = calloc(len, sizeof(int));
    if (arr == NULL)
        abort();
    for (int i = 0; i < len; ++i) {
        err = scanf("%d", &arr[i]);
        if (err != 1)
            goto free_and_abort;
    }
    struct list_T** bkts = bucket_sort(arr, len);
    if (bkts == NULL)
        goto free_and_abort;
    print_buckets(bkts, len);
    free_buckets(&bkts, len);
    free(arr);
    return 0;
free_and_abort:
    free_buckets(&bkts, len);
    free(arr);
    abort();
}

void free_list(struct list_T** top)
{
    while (*top != NULL) {
        struct list_T* tmp = top[0]->next;
        free(*top);
        *top = tmp;
    }
}

void free_buckets(struct list_T*** bkts, int len)
{
    if (bkts == NULL)
        return;
    for (int i = 0; i < len; ++i)
        free_list(&bkts[0][i]);
    free(*bkts);
    *bkts = NULL;
}

void print_list(struct list_T* top)
{
    while (top != NULL) {
        printf("%d ", top->data);
        top = top->next;
    }
    printf("0 ");
}

void print_buckets(struct list_T** bkts, int len)
{
    for (int i = 0; i < len; ++i)
        print_list(bkts[i]);
}

int max_element(int* arr, int len)
{
    int res = INT_MIN;
    for (int i = 0; i < len; ++i) {
        res = res < arr[i] ? arr[i] : res;
    }
    return res;
}

int add_to_bucket(struct list_T** bkt, int x)
{
    struct list_T* i = *bkt;
    struct list_T* tmp = calloc(1, sizeof(struct list_T));
    if (tmp == NULL)
        return -1;
    tmp->data = x;
    if (i == NULL) {
        *bkt = tmp;
        return 0;
    }
    if (i->data > x) {
        *bkt = tmp;
        tmp->next = i;
    } else {
        while (i->next != NULL && i->next->data <= x)
            i = i->next;
        tmp->next = i->next;
        i->next = tmp;
    }
    return 0;
}

struct list_T** bucket_sort(int* arr, int len)
{
    struct list_T** bkts;
    int err, i, pos, max, step;
    max = max_element(arr, len);
    step = max / len;
    bkts = calloc(len, sizeof(struct list_T*));
    if (bkts == NULL)
        return NULL;
    for (i = 0; i < len; ++i) {
        pos = arr[i] / step;
        if (pos >= len)
            pos = len - 1;
        err = add_to_bucket(&bkts[pos], arr[i]);
        if (err == -1)
            goto free_and_fail;
    }
    return bkts;
free_and_fail:
    free_buckets(&bkts, len);
    return NULL;
}
