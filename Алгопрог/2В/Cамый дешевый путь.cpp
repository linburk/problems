#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > matrix(n + 1, vector<int>(m + 1, 101));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> matrix[i][j];
        }
    }

    matrix[0][1] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            matrix[i][j] = matrix[i][j] + min(matrix[i][j - 1], matrix[i - 1][j]);
        }
    }

    cout << matrix[n][m];

}