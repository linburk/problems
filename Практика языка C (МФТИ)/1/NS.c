#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
    char number[32];
    int x, y, size = 0;
    int cnt = scanf("%d%d", &x, &y);
    if (cnt != 2 || x < 1 || y < 2 || y > 10)
        abort();
    while (x > 0) {
        number[size++] = x % y;
        x /= y;
    }
    for (int i = size - 1; i >= 0; --i) {
        printf("%d", number[i]);
    }
}
