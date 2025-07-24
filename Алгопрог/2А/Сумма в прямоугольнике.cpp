#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int> > a(n, vector<int>(m));
    vector<vector<int> > pref(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            pref[i][j] = a[i - 1][j - 1] + pref[i][j - 1] + pref[i - 1][j] - pref[i - 1][j - 1];
        }
    }
    int x1, y1, x2, y2;
    for (int i = 0; i < k; i++){
        cin >> x1 >> y1 >> x2 >> y2;
        x1--; y1--; x2--; y2--;
        cout << pref[x2 + 1][y2 + 1] - pref[x1][y2 + 1] - pref[x2 + 1][y1] + pref[x1][y1] << endl;
    }
}