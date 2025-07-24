#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<bool> > lab(n, vector<bool>(m, 0));
    vector<vector<bool> > used(n, vector<bool>(m, 0));
    vector<pair<int, int> > moves { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
    int endx, endy;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            char c;
            cin >> c;
            if (c == '1'){
                lab[i][j] = 1;
                used[i][j] = 1;
            }
            if (c == '*'){
                endx = i;
                endy = j;
            }
        }
    }
    int nentries;
    cin >> nentries;
    vector<pair<int, int> > entries(nentries);
    for (int i = 0; i < nentries; i++){
        cin >> entries[i].first >> entries[i].second;
        entries[i].first--;
        entries[i].second--;
        used[entries[i].first][entries[i].second] = 1;
    }
    queue<pair<pair<int, int>, int> > q;
    for (int i = 0; i < nentries; i++){
        q.push({entries[i], i + 1});
    }
    while (!q.empty()){
        int x, y, num, dx, dy;
        x = q.front().first.first;
        y = q.front().first.second;
        num = q.front().second;
        q.pop();
        for (auto d : moves){
            dx = d.first;
            dy = d.second;
            if (x + dx >= 0 and x + dx < n and y + dy >= 0 and y + dy < m){
                if (!used[x + dx][y + dy] and !lab[x + dx][y + dy]){
                    if (x + dx == endx and y + dy == endy){
                        cout << num ;
                        return 0;
                    }
                    q.push({{x + dx, y + dy}, num});
                }
            }
        }
        used[x][y] = 1;
    }
    cout << -1;
}