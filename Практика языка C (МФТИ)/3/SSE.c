#include <stdio.h>
#include <stdlib.h>

void selection_sort(int*, int, int);

int main()
{
    int tmp;
    unsigned len, last;
    int* arr;
    tmp = scanf("%u", &len);
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
    tmp = scanf("%u", &last);
    if (tmp != 1)
        goto free_and_abort;
    selection_sort(arr, len, last);
    for (int i = 0; i < len; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
free_and_abort:
    free(arr);
    abort();
}

int find_minimum(int* arr, int i, int len)
{
    int min = arr[i];
    int pos = i;
    for (; i < len; ++i) {
        if (arr[i] < min) {
            min = arr[i];
            pos = i;
        }
    }
    return pos;
}

void selection_sort(int* arr, int len, int last)
{
    for (int i = last; i < len; ++i) {
        int tmp, pos;
        pos = find_minimum(arr, i, len);
        tmp = arr[i];
        arr[i] = arr[pos];
        arr[pos] = tmp;
        break;
    }
}
