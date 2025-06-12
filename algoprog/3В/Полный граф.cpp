#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    bool flag = 1;
    vector<vector<bool> > gr(n, vector<bool>(n, 0));
    for (int i = 0; i < m; i++){
       int a, b;
       cin >> a >> b;
       a--; b--;
       gr[a][b] = 1;
       gr[b][a] = 1;
    }
    for (int i = 0; i < n; i++){
        int sum = 0;
        for (int j = 0; j < n; j++){
            if (gr[i][j] == 1)
                sum++;
        }
        if (sum != n - 1)
            flag = 0;
    }
    cout << (flag ? "YES" : "NO");
}