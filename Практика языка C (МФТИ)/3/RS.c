#include <stdio.h>
#include <stdlib.h>

int radix_sort_step(int* arr, int len, int r);

int main()
{
    int* arr;
    int len, r;
    int err = scanf("%d", &len);
    if (err != 1 || len < 0)
        abort();
    arr = calloc(len, sizeof(int));
    if (arr == NULL)
        abort();
    for (int i = 0; i < len; ++i) {
        err = scanf("%d", &arr[i]);
        if (err != 1)
            goto free_and_abort;
    }
    err = scanf("%d", &r);
    if (err != 1)
        goto free_and_abort;
    err = radix_sort_step(arr, len, r);
    if (err == -1)
        goto free_and_abort;
    for (int i = 0; i < len; ++i)
        printf("%d ", arr[i]);
    printf("\n");
    free(arr);
    return 0;
free_and_abort:
    free(arr);
    abort();
}

int radix_sort_step(int* arr, int len, int r)
{
    int* res;
    int bucket[11] = { 0 };
    int pow = 1;
    for (int i = 0; i < r; ++i)
        pow *= 10;
    for (int i = 0; i < len; ++i) {
        int d = arr[i] / pow % 10;
        ++bucket[d + 1];
    }
    for (int i = 0; i < 10; ++i)
        bucket[i + 1] += bucket[i];
    res = calloc(len, sizeof(int));
    if (res == NULL)
        return -1;
    for (int i = 0; i < len; ++i) {
        int d = arr[i] / pow % 10;
        res[bucket[d]++] = arr[i];
    }
    for (int i = 0; i < len; ++i)
        arr[i] = res[i];
    free(res);
    return 0;
}
