#include <stdio.h>
#include <stdlib.h>

int myrand()
{
    static unsigned long int seed = 1;
    seed = seed * 1103515245 + 12345;
    return (unsigned int)(seed / 65536) % 32768;
}

void shuffle(int*, unsigned);

int main()
{
    int tmp;
    unsigned len;
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
    shuffle(arr, len);
    if (len == 0)
        printf("0 ");
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

void shuffle(int* arr, unsigned len)
{
    for (; len > 0; --len) {
        int tmp, i;
        i = myrand() % len;
        tmp = arr[len - 1];
        arr[len - 1] = arr[i];
        arr[i] = tmp;
    }
}
