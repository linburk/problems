#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int> > svetofori(n, vector<int>(n, 0));
    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        svetofori[a][b]++;
        svetofori[b][a]++;
    }
    for (int i = 0; i < n; i++){
        int sum = 0;
        for (int j = 0; j < n; j++){
            sum += svetofori[i][j];
        }
        cout << sum << " ";
    }
}