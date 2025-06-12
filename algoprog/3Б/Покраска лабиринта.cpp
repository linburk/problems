#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<vector<bool> > lab(n + 2, vector<bool>(n + 2, false));
    vector<vector<bool> > used(n + 2, vector<bool>(n + 2, true));
    vector<pair<int, int> > moves{{0,1}, {1,0},{-1,0},{0,-1}};
    for (int i = 0; i < n + 1; i++){
        lab[i][0] = 1;
        lab[0][i] = 1;
        lab[i][n + 1] = 1;
        lab[n + 1][i] = 1;
    }

    lab[1][0] = 0;
    lab[0][1] = 0;
    lab[n + 1][n] = 0;
    lab[n][n + 1] = 0;
    used[1][0] = 0;
    used[0][1] = 0;
    used[n + 1][n] = 0;
    used[n][n + 1] = 0;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++){
            char t;
            cin >> t;
            if (t == '#'){
                lab[i][j] = true;
                used[i][j] = false;
            }
        }
    queue<pair<int, int> > q;
    q.push({1, 1});
    int sum = 0;
    while (!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (auto z : moves){
            if (lab[x + z.first][y + z.second] == 0 and used[x + z.first][y + z.second]){
                q.push({x + z.first, y + z.second});
                used[x + z.first][y + z.second] = 0;
            }
            if (lab[x + z.first][y + z.second] == 1){
                sum += 9;
            }

        }
    }
    cout << sum;
}