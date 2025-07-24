#include <stdio.h>
#include <stdlib.h>

int max_element(int*, int);
int* to_buckets(int*, int, int);

int main()
{
    int *arr, *res;
    int len, max;
    int tmp = scanf("%d", &len);
    if (tmp != 1)
        abort();
    arr = calloc(len, sizeof(int));
    if (arr == NULL)
        abort();
    for (int i = 0; i < len; ++i) {
        tmp = scanf("%d", &arr[i]);
        if (tmp != 1)
            goto free_and_abort;
    }
    max = max_element(arr, len);
    res = to_buckets(arr, len, max);
    if (res == NULL)
        goto free_and_abort;
    for (int i = 0; i <= max; ++i) {
        printf("%d ", res[i]);
    }
    printf("\n");
    free(res);
    free(arr);
    return 0;
free_and_abort:
    free(arr);
    abort();
}

int* to_buckets(int* arr, int len, int max)
{
    int* buckets = calloc(max + 1, sizeof(int));
    if (buckets == NULL)
        return NULL;
    for (int i = 0; i < len; ++i)
        ++buckets[arr[i]];
    return buckets;
}

int max_element(int* arr, int len)
{
    int res = 0;
    for (int i = 0; i < len; ++i)
        res = (res < arr[i] ? arr[i] : res);
    return res;
}
