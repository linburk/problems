#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

int ans = 0;
void dfs(vector<vector<int> > &gr, vector<bool> &used, vector<int> &mind, vector<int> &d, int i, int last) {
    int flag = 0;
    used[i] = 1;
    int c = 0;
    if (last == -1)
        d[i] = 0;
    else
        d[i] = d[last] + 1;
    mind[i] = d[i];
    for (auto j : gr[i]){
        if (j != last){
            if (!used[j]){
                dfs(gr, used, mind, d, j, i);
                mind[i] = min(mind[i], mind[j]);
                if (d[i] <= mind[j] and last != -1){
                    flag = 1;
                }
                c++;
            }
            else {
                mind[i] = min(mind[i], d[j]);
            }
        }
    }
    ans += flag;
    if (last == -1 and c > 1)
        ans++;
}




int main(){
    int n, m;
    cin >> n;
    vector<vector<int> > gr(n);
    vector<bool> used(n, 0);
    vector<int> mind(n);
    vector<int> d(n);
    for (int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        a--; b--;
        gr[a].push_back(b);
        gr[b].push_back(a);
    }
    for (int i = 0; i < n; i++){
        if (!used[i]){
            dfs(gr, used, mind, d, i, -1);
        }
    }
    cout << ans;
}