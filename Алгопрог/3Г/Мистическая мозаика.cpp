#include "stdio.h"
#include "strings.h"

int main(int argc, const char * argv[]) {
    char t[52][52];
    bzero(t, 52 * 52);
    int n, m;
    scanf("%d %d\n", &n, &m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%c", &t[i][j]);
        } scanf("\n");
    }
    char res = 1;
    int stackj[52];
    int sj_size = 0;
    int stacki[52];
    int si_size = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (t[i][j] == '#') {
                for (int k = 0; k < n; ++k) {
                    if (t[k][j] == '#') stacki[si_size++] = k;
                }
                for (int k = 0; k < m; ++k) {
                    if (t[i][k] == '#') stackj[sj_size++] = k;
                }
                for (int k = 0; k < si_size; ++k) {
                    for (int l = 0; l < sj_size; ++l) {
                        if (t[stacki[k]][stackj[l]] != '#') res = 0;
                    }
                }
                si_size = 0, sj_size = 0;
            }
        }
    }
    printf("%s\n", res ? "Yes" : "No");
    int z = 0;
    return 0;
}