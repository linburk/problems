#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;


int main()
{
    int n;
    cin >> n;
    int x1, y1, x2, y2;
    vector<vector<bool > > wall(n + 2, vector<bool>(n + 2, 0));
    vector<vector<bool > > used(n + 2, vector<bool>(n + 2, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c;
            cin >> c;
            if (c == '@') {
                x1 = i;
                y1 = j;
            }
            if (c == 'X') {
                x2 = i;
                y2 = j;
            }
            if (c == '0') {
                wall[i][j] = 1;
            }
        }
    }
}