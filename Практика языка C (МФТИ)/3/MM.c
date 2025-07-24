#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int min_element(int*, int);
int max_element(int*, int);

int main()
{
    int tmp;
    int len;
    int* arr;
    int min, max;
    tmp = scanf("%d", &len);
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
    min = min_element(arr, len);
    max = max_element(arr, len);
    printf("%d %d\n", min, max);
    free(arr);
    return 0;
free_and_abort:
    free(arr);
    abort();
}

int min_element(int* arr, int len)
{
    if (len == 0)
        return 0;
    int res = INT_MAX;
    for (int i = 0; i < len; ++i)
        res = arr[i] < res ? arr[i] : res;
    return res;
}

int max_element(int* arr, int len)
{
    if (len == 0)
        return 0;
    int res = INT_MIN;
    for (int i = 0; i < len; ++i)
        res = arr[i] > res ? arr[i] : res;
    return res;
}
