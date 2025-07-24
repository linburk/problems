#include <queue>
#include <deque>
#include <iostream>
#include <set>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <list>
#include <iterator>
using namespace std;

int main() {
    long long n, m;
    cin >> n >> m;
    vector<pair<long long, long long> > moves{{2, 1}, {2, -1}, {1, 2}, {-1, 2}};
    vector<vector<long long> > table(n, vector<long long>(m, 0));
    queue<pair<long long, long long> > q;
    q.push({0, 0});
    while (!q.empty()){
        auto &[x, y] = q.front();
        q.pop();
        for (auto &[dx, dy] : moves){
            if (x + dx >= 0 and x + dx < m and y + dy >= 0 and y + dy < n){
                table[y + dy][x + dx]++;
                q.push({x + dx, y + dy});
            }
        }
    }
    cout << table[n - 1][m - 1];
}