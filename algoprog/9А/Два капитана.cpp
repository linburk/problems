#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 5001
#define max(a, b) (a < b ? b : a)
#define min(a, b) (a < b ? a : b)

int n;
int a[MAX_SIZE];
int b[MAX_SIZE];
int ind[MAX_SIZE];
int dp[MAX_SIZE][MAX_SIZE / 2 + 1];
int prev[MAX_SIZE][MAX_SIZE / 2 + 1];
int ans[MAX_SIZE / 2 + 1][2];

int part(int l, int r) {
    assert(l >= 0 && r <= n);
    int mid = a[l + rand() % (r - l)];
    int j = l;
    for (int i = l; i < r; ++i) {
        if (a[i] <= mid) {
            int ta = a[j];
            int tb = b[j];
            int ti = ind[j];
            a[j] = a[i];
            b[j] = b[i];
            ind[j] = ind[i];
            a[i] = ta;
            b[i] = tb;
            ind[i] = ti;
            ++j;
        }
    }
    return j;
}

void quicksort(int l, int r) {
    if (l < r - 1) {
        int m = part(l, r);
        quicksort(l, m);
        quicksort(m, r);
    }
}

int main(void) {
    srand(time(NULL));
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        ind[i] = i;
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &b[i]);
    }
    quicksort(0, n);
#if 0
    for (int i = 0; i < n; ++i)
        printf("%d ", a[i]);
    printf("\n");
#endif
    for (int i = 1; i <= n; ++i) {
        for (int l = 0; l <= min(n / 2, i); ++l) {
            dp[i][l + 1] = dp[i - 1][l] + b[i - 1];
            prev[i][l + 1] = l;
            if (l - 1 >= 0 && dp[i - 1][l] > dp[i][l - 1]) {
                dp[i][l - 1] = dp[i - 1][l];
                prev[i][l - 1] = l;
            }
        }
    }
    for (int l = 1, r = 1, p = 0, i = n; i > 0; --i) {
        if (prev[i][p] < p) {
            --p;
            ans[l++][0] = ind[i - 1] + 1;
        } else {
            ++p;
            ans[r++][1] = ind[i - 1] + 1;
        }
    }
    for (int i = 1; i <= n / 2; ++i) {
        printf("%d %d\n", ans[i][0], ans[i][1]);
    }
}