#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int main() {
    int n, k;
    cin >> n >> k;
    vector<vector<int> > m(n + 2, vector<int>(n + 2, 0));
    vector<vector<int> > a(n + 2, vector<int>(n + 2, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> m[i][j];
        }
    }
    a[1][1] = m[1][1];
    int cnt = k;
    int i = 1, j = 1, jlast = 1, ilast = 1;
    while (cnt != 0) {
        while (cnt != 0) {
            if (m[i][j] >= max(m[i][j - 1], max(m[i + 1][j], m[i - 1][j]))) {
                a[i][j + 1] = m[i][j + 1] + a[ilast][jlast];

                j++;
                jlast = j; 
                cnt--;
            }
            else if (m[i][j - 1] >= max(m[i + 1][j], m[i - 1][j])) {
                a[i][j - 1] = m[i][j - 1] + a[ilast][jlast];
                
                j--;
                jlast = j;
                cnt--;
            }
            else if (m[i + 1][j] >= m[i - 1][j]) {
                a[i + 1][j] = m[i + 1][j] + a[ilast][jlast];
                
                i++;
                ilast = i;
                cnt--;
            }
            else {
                a[i - 1][j] = m[i - 1][j] + a[ilast][jlast];
                
                i--;
                ilast = i;
                cnt--;
            }
        }
    }
    for (auto x : a) {
        for (auto y : x) {
            cout << y << " ";
        }
        cout << endl;
    }

}