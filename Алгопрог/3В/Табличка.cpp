#include <queue>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > rast(n + 2, vector<int>(m + 2, -1));
    vector<pair<int, int> > moves {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1}};
    queue<pair<int, int> > q;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            int a;
            cin >> a;
            if (a == 1){
                q.push({i, j});
                rast[i][j] = 0;
            }
            else
            {
                rast[i][j] = 100000;
            }
        }
    }
    while (!q.empty()){
        int i = q.front().first;
        int j = q.front().second;
        q.pop();
        for (auto t : moves){
            int di = i + t.first;
            int dj = j + t.second;
            if (rast[i][j] + 1 < rast[di][dj] and rast[di][dj] != -1){
                rast[di][dj] = rast[i][j] + 1;
                q.push({di, dj});
            }
        }
    }
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++)
            cout << rast[i][j] << " ";
        cout << endl;
    }
}