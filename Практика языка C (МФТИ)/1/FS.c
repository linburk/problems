#include <stdio.h>
#include <stdlib.h>

int main()
{
    char number[32];
    int size = 0;
    int x;
    int cnt = scanf("%d", &x);
    if (cnt != 1)
        abort();
    for (int fact = 1, i = 1; x > 0;) {
        int part = x / fact % (i + 1);
        number[size++] = part;
        x -= part * fact;
        ++i;
        fact *= i;
    }
    for (int i = size - 1; i >= 0; --i) {
        printf("%d.", number[i]);
    }
    return 0;
}
