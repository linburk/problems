#include <queue>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <list>

using namespace std;

vector<pair<int, int> > moves {{0, 1},{1, 0},{-1, 0},{0, -1}};
pair<int, int> bfs(vector<vector<int> > &walls, map<pair<int, int>, pair<int, int> > &tunnels, vector<vector<pair<int, int> > > &mem, int i, int j)
{
    pair<int, int> escape = {-1, -1};
    queue<pair<int, int> > q;
    q.push({i, j});
    while (!q.empty()){
        i = q.front().first;
        j = q.front().second;
        q.pop();
        for (auto d : moves){
            if (mem[i + d.first][j + d.second] == make_pair(-1, -1) and walls[i + d.first][j + d.second] != 1 and walls[i + d.first][j + d.second] != -2){
                if (walls[i + d.first][j + d.second] == -1){
                    escape = {i + d.first, j + d.second};
                    mem[i + d.first][j + d.second] = {i, j};
                    return escape;
                }
                else {
                    mem[i + d.first][j + d.second] = {i, j};
                    q.push({i + d.first, j + d.second});
                }
            }
        }
        if (tunnels.count({i, j})){
            int dx = tunnels[{i, j}].first;
            int dy = tunnels[{i, j}].second;
            if (mem[dx][dy] == make_pair(-1, -1)){
                mem[dx][dy] = {i, j};
                q.push({dx, dy});
            }
        }
    }
    return escape;
}

int main() {
    int n, m;
    cin >> n >> m;
    int x, y;
    cin >> x >> y;
    vector<vector<int> > walls(n + 2, vector<int>(m + 2, -2));
    walls[x][y] = -2;
    map<pair<int, int>, pair<int, int> > tunnels;
    vector<vector<pair<int, int> > > mem(n + 2, vector<pair<int, int> >(m + 2, make_pair(-1, -1)));
    mem[x][y] = {-2, -2};
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            cin >> walls[i][j];
        }
    }
    int h;
    cin >> h;
    for (int i = 0; i < h; i++){
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        tunnels[{a, b}] = {c, d};
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; i++){
        int a, b;
        cin >> a >> b;
        walls[a][b] = -1;
    }
    pair<int, int> escape = bfs(walls, tunnels, mem, x, y);
    vector<pair<int, int> > ans;
    while (escape != make_pair(-2, -2)){
        ans.push_back(escape);
        x = escape.first;
        y = escape.second;
        escape = mem[x][y];
    }
    cout << ans.size() << endl;
    for (int i = ans.size() - 1; i >= 0; i--){
        cout << ans[i].first << " " << ans[i].second << endl;
    }
}