#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int> > a(n + 1, vector<int>(m + 1, 0));
    a[0][1] = 1;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            a[i][j] = a[i - 1][j] + a[i][j - 1];
        }
    }
    cout << a[n][m];
}