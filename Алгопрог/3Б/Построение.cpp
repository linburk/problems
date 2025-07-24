#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

void dfs(vector<vector<int> > &gr, vector<bool> &used, int last, int i){
    if (used[i]){
        cout << "No";
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
   int n, m;
   cin >> n >> m;
   vector<vector<int> > gr(n);
   vector<bool> used(n, 0);
   int a, b;
   for (int i = 0; i < m; i++){
       cin >> a >> b;
       a--; b--;
       gr[a].push_back(b);
       gr[b].push_back(a);
   }
   dfs(gr, used, b, a);
   cout << "Yes";
}