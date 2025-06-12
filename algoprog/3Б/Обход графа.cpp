#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;
int sum = 1;
void find(vector<bool> &used, vector<vector<int> > &g, int i){
    if (used[i] == 0){
        return;
    }
    used[i] = 0;
    for (int j = 0; j < used.size(); j++){
        if (g[i][j] == 1 and used[j] == 1){
            find(used, g, j);
            sum++;
        }
    }
    return;
}


int main(){
   int n, s;
   cin >> n >> s;
   s--;
   vector<vector<int> > g(n, vector<int>(n, 0));
   vector<bool> used(n, 1);

   for (int i = 0; i < n; i++){
       for (int j = 0; j < n; j++){
           cin >> g[i][j];
       }
   }
   find(used, g, s);
    cout << sum;
}