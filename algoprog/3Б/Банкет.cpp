#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;
bool check = true;
vector<int> mem;
void dfs(vector<vector<int> > &gr, vector<int> &paint, int i, int color){
    paint[i] = color;
    if (paint[i] == 0)
        mem.push_back(i);
    for (auto j : gr[i]){
        if (paint[j] == -1){
            dfs(gr, paint, j, (color + 1) % 2);
        }
        else if (paint[j] == paint[i]){
            check = false;
        }
    }
}


int main(){
   int n, m;
   cin >> n >> m;
   vector<vector<int> > gr(n);
   vector<int> paint(n, -1);
   for (int i = 0; i < m; i++){
       int a, b;
       cin >> a >> b;
       a--; b--;
       gr[a].push_back(b);
       gr[b].push_back(a);
   }
    for (int i = 0; i < n; i++){
        if (paint[i] == -1) {
            int color = 0;
            dfs(gr, paint, i, color);
        }
    }
    if (check){
        cout << "YES" << endl;
        for (auto i : mem){
            cout << i + 1 << " ";
        }
    }
    else
        cout << "NO";
}