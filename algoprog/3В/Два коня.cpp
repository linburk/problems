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
vector<vector<pair<int, int> > > memwhite(8, vector<pair<int, int> >(8, make_pair(-1, -1)));
vector<vector<pair<int, int> > > memblack(8, vector<pair<int, int> >(8, make_pair(-1, -1)));
vector<pair<int, int> > moves = {{2, 1},
                                 {2, -1},
                                 {-2, 1},
                                 {-2, -1},
                                 {1, 2},
                                 {-1, 2},
                                 {1, -2},
                                 {-1, -2}};
void bfs(int x, int y, int xno, int yno, vector<vector<pair<int, int> > > mem){
    queue<pair<int, int> > q;
    q.push({x, y});
    while (!q.empty()){
        pair<int, int> t = q.front();
        q.pop();
        int xt = t.first, yt = t.second;
        for (auto k : moves){
            int dx = k.first, dy = k.second;
            if (x + dx < 8 and x + dx >= 0 and y + dy >= 0 and y + dy < 8){
                if (mem[x + dx][y + dy] == make_pair(-1, -1) and not (x + dx == xno and y + dy == yno)){
                    q.push({x + dx, y + dy});
                    mem[x + dx][y + dy] = {x, y};
                }
            }
        }
    }
}
int main() {
    int xw1, yw1, xw2, yw2;
    int xb1, yb1, xb2, yb2;
    int num;
    char c;
    cin >> c >> num;
    yw1 = num - 1; xw1 = c - 'a';
    cin >> c >> num;
    yb1 = num - 1; xb1 = c - 'a';
    cin >> c >> num;
    yw2 = num - 1; xw2 = c - 'a';
    cin >> c >> num;
    yb2 = num - 1; xb2 = c - 'a';
    bfs(xw1, yw1, xb1, yb1, memwhite);
    bfs(xb1, yb1, xw2, yw2, memblack);
    vector<pair<int, int> > bans, wans;
    if (not(memwhite[xw2][yw2] == make_pair(-1, -1) or memblack[xb2][yb2] == make_pair(-1, -1))){
        pair<int, int> coord = memwhite[xw2][yw2];
        while(coord.first != xw1 or coord.second != yw1){
            wans.push_back(memwhite[coord.first][coord.second]);
            coord = memwhite[coord.first][coord.second];
        }
        coord = memblack[xb2][yb2];
        while(coord.first != xw1 or coord.second != yw1){
            bans.push_back(memblack[coord.first][coord.second]);
            coord = memblack[coord.first][coord.second];
        }
        cout << bans.size() + wans.size() << endl;
        for (int i = wans.size() - 1; i >= 0; i--){
            cout << 'W' << char(wans[i].first + 'a' - 1) << " " << wans[i].second + 1 << endl;
        }
        for (int i = bans.size() - 1; i >= 0; i--){
            cout << 'B' << char(bans[i].first + 'a' - 1) << " " << bans[i].second + 1 << endl;
        }
    }
    else
        cout << -1;
}