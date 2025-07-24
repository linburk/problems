#include <queue>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> cost(n, 0);
    vector<int> ans(n, -1);
    vector<bool> used(n, 0);
    vector<vector<long long> > goroda(n);
    for (int i = 0; i < n; i++){
        cin >> cost[i];
        for (int j = 0; j < i; j++){
            if (!used[j]){
                if (cost[i] < cost[j]){
                    ans[j] = i;
                    used[j] = 1;
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
        cout << ans[i] << " ";


}