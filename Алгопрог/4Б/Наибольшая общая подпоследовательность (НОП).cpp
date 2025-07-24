#include <queue>
#include <deque>
#include <iostream>
#include <vector>
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

int main(){
    vector<int> a, b;
    int n, m;
    cin >> n;
    for (int temp, i = 0; i < n; ++i) {
        cin >> temp;
        a.push_back(temp);
    }
    cin >> m;
    for (int temp, i = 0; i < m; ++i) {
        cin >> temp;
        b.push_back(temp);
    }
    vector<vector<int> > ab(n + 1, vector<int>(m + 1));
    ab[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) {
                ab[i][j] = ab[i - 1][j - 1] + 1;
            } else {
                ab[i][j] = max(ab[i - 1][j], ab[i][j - 1]);
            }
        }
    cout << ab[n][m];
}