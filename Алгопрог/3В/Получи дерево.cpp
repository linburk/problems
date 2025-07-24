#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

vector<vector<int> > mem;
void dfs(vector<vector<int> > &gr, vector<bool> &used, int i) {
    used[i] = 1;
    for (auto j : gr[i]){
        if (!used[j]){
            dfs(gr, used, j);
            mem[i].push_back(j);
        }
    }
}

int main(){
    int n, m, l;
    cin >> n >> m;
    vector<vector<int> > gr(n);
    vector<bool> used(n, 0);
    mem.resize(n);
    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--; b--;
        gr[a].push_back(b);
        gr[b].push_back(a);
        l = a;
    }
    dfs(gr, used, l);
    for (int i = 0; i < mem.size(); i++) {
        if (mem[i].size() > 0){
            for (auto j : mem[i]){
                cout << i + 1 << " " << j + 1 << endl;
            }
        }
    }
}