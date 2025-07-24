#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct matrix_T {
    int** data;
    int n, k;
};

void init_mtrx(struct matrix_T*, int, int);
void free_mtrx(struct matrix_T*);
int input_mtrx(struct matrix_T*);
void print_mtrx(struct matrix_T*);
int sort(struct matrix_T*, int);

int main()
{
    struct matrix_T mtrx;
    int n, k, x;
    int err = scanf("%d%d%d", &n, &k, &x);
    if (err != 3 || n < 0 || k < 0 || x < 0)
        abort();
    init_mtrx(&mtrx, n, k);
    if (mtrx.data == NULL)
        abort();
    err = input_mtrx(&mtrx);
    if (err == -1)
        goto free_and_abort;
    err = sort(&mtrx, x);
    if (err == -1)
        goto free_and_abort;
    //    print_mtrx(&mtrx);
    for (int i = 0; i < n; ++i)
        printf("%d ", mtrx.data[i][i % k]);
    printf("\n");
    free_mtrx(&mtrx);
    return 0;
free_and_abort:
    free_mtrx(&mtrx);
    abort();
}

void init_mtrx(struct matrix_T* mtrx, int n, int k)
{
    mtrx->n = n;
    mtrx->k = k;
    mtrx->data = calloc(n, sizeof(int*));
    if (mtrx == NULL)
        return;
    for (int i = 0; i < n; ++i) {
        mtrx->data[i] = calloc(k, sizeof(int));
        if (mtrx->data[i] == NULL)
            goto free_and_fail;
    }
    return;
free_and_fail:
    free_mtrx(mtrx);
    return;
}

void free_mtrx(struct matrix_T* mtrx)
{
    for (int i = 0; i < mtrx->n; ++i)
        free(mtrx->data[i]);
    free(mtrx->data);
    mtrx->data = NULL;
    mtrx->n = 0;
    mtrx->k = 0;
}

int input_mtrx(struct matrix_T* mtrx)
{
    for (int i = 0; i < mtrx->n; ++i) {
        for (int j = 0; j < mtrx->k; ++j) {
            int err = scanf("%d", &mtrx->data[i][j]);
            if (err != 1)
                return -1;
        }
    }
    return 0;
}

void print_mtrx(struct matrix_T* mtrx)
{
    for (int i = 0; i < mtrx->n; ++i) {
        for (int j = 0; j < mtrx->k; ++j)
            printf("%d ", mtrx->data[i][j]);
        printf("\n");
    }
}

void reverse(int** arr, int len)
{
    for (int i = 0; i <= len / 2; ++i) {
        int* tmp = arr[i];
        arr[i] = arr[len - i - 1];
        arr[len - i - 1] = tmp;
    }
}

int shift_right(int** arr, int key, int last, int x)
{
    for (int i = last; i > 0; --i) {
        if (arr[i - 1][x] <= key)
            return i;
        arr[i] = arr[i - 1];
    }
    return 0;
}

void insertion_sort(int** arr, int len, int x)
{
    for (int i = 0; i < len; ++i) {
        int* tmp = arr[i];
        int j = shift_right(arr, arr[i][x], i, x);
        arr[j] = tmp;
    }
}

void sort_run(int** arr, int len, int x)
{
    if (len > 1 && arr[0][x] > arr[1][x]) {
        int j = 1;
        while (j < len && arr[j - 1][x] > arr[j][x])
            ++j;
        reverse(arr, j);
    }
    insertion_sort(arr, len, x);
}

void merge(int** lmem, int lnelts, int** rmem, int rnelts, int** dst, int x)
{
    int l = 0, r = 0, d = 0;
    int len = lnelts + rnelts;
    while (d < len) {
        while (l < lnelts && (r == rnelts || lmem[l][x] <= rmem[r][x])) {
            dst[d] = lmem[l];
            ++l;
            ++d;
        }
        while (r < rnelts && (l == lnelts || rmem[r][x] < lmem[l][x])) {
            dst[d] = rmem[r];
            ++r;
            ++d;
        }
    }
}

int sort_impl(int** arr, int len, int x)
{
    int err;
    int** dst;
    int m = len / 2;
    if (len <= 64) {
        sort_run(arr, len, x);
        return 0;
    }
    err = sort_impl(arr, m, x);
    if (err == -1)
        return err;
    err = sort_impl(arr + m, len - m, x);
    if (err == -1)
        return err;
    dst = calloc(len, sizeof(int*));
    if (dst == NULL)
        return -1;
    merge(arr, m, arr + m, len - m, dst, x);
    memcpy(arr, dst, len * sizeof(int*));
    free(dst);
    return 0;
}

int sort(struct matrix_T* mtrx, int x)
{
    return sort_impl(mtrx->data, mtrx->n, x);
}
