unsigned partition(int* arr, unsigned low, unsigned high)
{
    int key, tmp;
    int i, j;
    key = arr[low];
    i = low + 1;
    j = high;
    while (i < j) {
        while (i <= j && arr[i] <= key)
            ++i;
        while (j > i && arr[j] > key)
            --j;
        if (i >= j)
            break;
        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
    --i;
    tmp = arr[i];
    arr[i] = key;
    arr[low] = tmp;
    return i;
}

#if 0
#include <stdio.h>
int main()
{
    int arr_l[] = { 5, 6, 6, 6, 6 };
    int arr_h[] = { 5, 1, 1, 1, 1 };
    int arr_m[] = { 5, 3, 4, 6, 7 };
    partition(arr_l, 0, 4);
    partition(arr_h, 0, 4);
    partition(arr_m, 0, 4);
    for (int i = 0; i < 5; ++i)
        printf("%d ", arr_l[i]);
    printf("\n");
    for (int i = 0; i < 5; ++i)
        printf("%d ", arr_h[i]);
    printf("\n");
    for (int i = 0; i < 5; ++i)
        printf("%d ", arr_m[i]);
    printf("\n");
}
#endif
