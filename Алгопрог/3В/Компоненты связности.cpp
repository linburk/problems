#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

void bfs(vector<vector<int> > &gr, vector<bool> &used, int i, vector<int> &komp){
    queue<int> q;
    q.push(i);
    while (!q.empty()){
        i = q.front();
        used[i] = 0;
        komp.push_back(i);
        q.pop();
        for (auto j : gr[i]){
            if (used[j]){
                q.push(j);
                used[j] = 0;
            }
        }
    }
}


int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int> > gr(n);
    vector<bool> used(n, 1);
    vector<vector<int> > ans;
    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--; b--;
        gr[a].push_back(b);
        gr[b].push_back(a);
    }
    for (int i = 0; i < n; i++){
        vector<int> komp;
        if (used[i]){
            bfs(gr, used, i, komp);
        }
        if (komp.size() > 0)
            ans.push_back(komp);
    }
    for (int i = 0; i < ans.size(); i++){
        cout << ans[i].size() << endl;
        for (auto j : ans[i]){
            cout << j + 1 << " ";
        }
        if (i < ans.size() - 1)
            cout << endl;
    }
}