#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

int sum = 1;
vector<pair<int, int> > moves {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

void find(vector<vector<bool> > &used, vector<vector<int> > &g, pair<int, int> i){
    if (used[i.first][i.second] == 0){
        return;
    }
    used[i.first][i.second] = 0;
    for (auto j : moves){
        if (g[i.first + j.first][i.second + j.second] == 1 and used[i.first + j.first][i.second + j.second] == 1){
            find(used, g, {i.first + j.first, i.second + j.second});
            sum++;
        }
    }
    return;
}


int main(){
   int n;
   cin >> n;
   vector<vector<int> > g(n, vector<int>(n, 0));
   vector<vector<bool> > used(n, vector<bool>(n, 1));

   for (int i = 0; i < n; i++){
       for (int j = 0; j < n; j++){
           char c;
           cin >> c;
           if (c == '.')
               g[i][j] = 1;
       }
   }
   int x, y;
   cin >> x >> y;
   x--; y--;
   find(used, g, {x, y});
    cout << sum;
}