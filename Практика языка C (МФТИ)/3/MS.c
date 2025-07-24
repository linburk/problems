#include <assert.h>
#include <stdlib.h>

void merge(int* arr, int l, int m, int r)
{
    int* tmp;
    int p1, p2;
    int len = r - l + 1;
    assert(len > 0);
    tmp = calloc(len, sizeof(int));
    if (tmp == NULL)
        abort();
    p1 = l;
    p2 = m + 1;
    for (int i = 0; i < len;) {
        while (p1 <= m && (p2 == r + 1 || arr[p1] <= arr[p2]))
            tmp[i++] = arr[p1++];
        while (p2 <= r && (p1 == m + 1 || arr[p2] <= arr[p1]))
            tmp[i++] = arr[p2++];
    }
    for (int i = 0; i < len; ++i)
        arr[i + l] = tmp[i];
    free(tmp);
}
