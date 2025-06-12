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
    bool check = 0;
    vector<vector<bool> > gr(n, vector<bool>(n, 0));
    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--; b--;
        if (gr[a][b])
            check = 1;
        gr[a][b] = 1;
        gr[b][a] = 1;
    }
    if (check)
        cout << "YES";
    else
        cout << "NO";
}