#include <stdio.h>
#include <string.h>

int main()
{
    int dp[2001] = { 0, 1, 1 };
    int was[2002] = { 0 };
    int n;
    scanf("%d", &n);
    for (int i = 3; i <= n; ++i) {
        memset(was, 0, (i + 1) * sizeof(int));
        for (int j = 3; j + 1 < i; ++j) {
            was[dp[j - 3] ^ dp[i - j - 2]] = 1;
        }
        was[dp[i - 3]] = 1;
        if (i > 3)
            was[dp[i - 4]] = 1;
        while (was[dp[i]])
            ++dp[i];
    }
    printf("%d", 1 + (dp[n] == 0));
    return 0;
}
