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
    string a, b;
    getline(cin, a);
    getline(cin, b);
    vector<vector<int> > cost(a.length() + 1, vector<int>(b.length() + 1, 0));
    for (int i = 0; i <= a.length(); i++)
        cost[i][0] = i;
    for (int i = 0; i <= b.length(); i++)
        cost[0][i] = i;
    for (int i = 1; i <= a.length(); i++){
        for (int j = 1; j <= b.length(); j++) {
            int replace_ = cost[i - 1][j - 1] + int(a[i - 1] != b[j - 1]);
            int insert_ = cost[i][j - 1] + 1;
            int delete_ = cost[i - 1][j] + 1;
            cost[i][j] = min(min(insert_, delete_), replace_);
        }
    }
    cout << cost[a.size()][b.size()];
}