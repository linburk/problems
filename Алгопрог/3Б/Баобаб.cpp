#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

void dfs(vector<vector<int> > &gr, vector<bool> &used, int last, int i){
    if (used[i]){
        cout << "NO";
        exit(0);
    }
    used[i] = 1;
    for (auto j : gr[i]){
        if (j != last){
            dfs(gr, used, i, j);
        }
    }
}

int main(){
    int n, l;
    cin >> n;
    vector<vector<int> > gr(n);
    vector<bool> used(n, 0);
    for (int i = 0; i < n; i++){
        for (int a, j = 0; j < n; j++) {
            cin >> a;
            if (a == 1){
                gr[i].push_back(j);
            }
        }
    }
    for (int i = 0; i < n; i++){
        if (!used[i]){
            dfs(gr, used, -1, i);
        }
    }
    cout << "YES";
}