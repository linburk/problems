#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;


bool check(int a, int b, int n){
    return a >= 0 and a < n and b >= 0 and b < n;
}

int main()
{
    int n;
    cin >> n;

    vector<vector<int> > graph(n, vector<int>(n, -1));
    vector<vector<pair<int, int> > > put(n, vector<pair<int, int> >(n, make_pair(-1, -1)));

    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    x1--; y1--;
    x2--; y2--;

    vector<pair<int, int> > moves;
    moves.push_back(make_pair(2, 1));
    moves.push_back(make_pair(-2, 1));
    moves.push_back(make_pair(2, -1));
    moves.push_back(make_pair(-2, -1));
    moves.push_back(make_pair(1, 2));
    moves.push_back(make_pair(1, -2));
    moves.push_back(make_pair(-1, 2));
    moves.push_back(make_pair(-1, -2));

    queue<pair<int, int> > s;
    s.push(make_pair(x1, y1));
    graph[x1][y1] = 0;
    while (!s.empty()){
        pair<int, int> v = s.front();
        s.pop();
        int ax = v.first;
        int ay = v.second;
        for (auto x : moves){
            int bx = x.first;
            int by = x.second;
            if (check(ax + bx, ay + by, n)){
                if (graph[ax + bx][ay + by] == -1){
                    s.push(make_pair(ax + bx, ay + by));
                    graph[ax + bx][ay + by] = graph[ax][ay] + 1;
                    put[ax + bx][ay + by] = v;
                }
            }
        }
    }
    vector<pair<int, int> > ans;
    pair<int, int> coord;
    coord.first = x2;
    coord.second = y2;
    cout << graph[x2][y2] << endl;
    while (coord.first != x1 or coord.second != y1){
        ans.push_back(put[coord.first][coord.second]);
        coord = put[coord.first][coord.second];
    }
    for (int i = ans.size() - 1; i >= 0; i--){
        cout << ans[i].first + 1 << " " << ans[i].second + 1 << endl;
    }
}