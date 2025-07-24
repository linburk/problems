#include <stdio.h>
#include <string.h>

#pragma GCC optimize("unrool-loops")

#define MAXLEN 100002
#define MOD 1000000007
#define TR 2
#define DC 10

int dp[MAXLEN][TR][DC][DC];

int n;
char number[MAXLEN];

int main(void)
{
    scanf("%s", number);
    n = strlen(number);
    for (int i = 0; i < n / 2; ++i)
    {
        char tc = number[i];
        number[i] = number[n - i - 1];
        number[n - i - 1] = tc;
    }
    for (int a = 0; a < DC; ++a)
    {
        for (int b = 0; b < DC; ++b)
        {
            if ((a + b) % DC == number[0] - '0')
            {
                dp[1][(a + b) / DC][a][b] += 1;
            }
        }
    }
    for (int i = 1; i < n; ++i)
    {
        static int prev_a[TR][DC];
        static int prev_b[TR][DC];
        static int prev_all[TR];
        memset(prev_a, 0, TR * DC * sizeof(int));
        memset(prev_b, 0, TR * DC * sizeof(int));
        memset(prev_all, 0, TR * sizeof(int));
        for (int c = 0; c < TR; ++c)
        {
            for (int a = 0; a < DC; ++a)
            {
                for (int b = 0; b < DC; ++b)
                {
                    prev_a[c][a] = (prev_a[c][a] + dp[i][c][a][b]) % MOD;
                    prev_b[c][b] = (prev_b[c][b] + dp[i][c][a][b]) % MOD;
                    prev_all[c]  = (prev_all[c]  + dp[i][c][a][b]) % MOD;
                }
            }
        }
        for (int c = 0; c < TR; ++c)
        {
            for (int a = 0; a < DC; ++a)
            {
                for (int b = 0; b < DC; ++b)
                {
                    if ((a + b + c) % DC == number[i] - '0')
                    {
                        int add_count =
                      (((prev_all[c] - prev_a[c][a] + MOD) % MOD - prev_b[c][b] + MOD) % MOD + dp[i][c][a][b]) %
                            MOD;
                        dp[i + 1][(a + b + c) / DC][a][b] = (dp[i + 1][(a + b + c) / DC][a][b] + add_count) % MOD;
                    }
                }
            }
        }
    }
#if 0
    for (int i = 0; i <= n; ++i)
    {
        for (int c = 0; c < TR; ++c)
        {
            for (int a = 0; a < DC; ++a)
            {
                for (int b = 0; b < DC; ++b)
                {
                    printf("dp[%d][%d][%d][%d]: %d\n", i, c, a, b, dp[i][c][a][b]);
                }
                printf("\n");
            }
            printf("\n");
        }
        printf("\n");
    }
#endif
    int res = 0;
    for (int a = 1; a < DC; ++a)
    {
        for (int b = 1; b < DC; ++b)
        {
            res = (res + dp[n][0][a][b]) % MOD;
        }
    }
    printf("%d\n", res);
}