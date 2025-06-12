#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    vector<vector<pair<int, int> > > a(k, vector<pair<int, int> >(1, make_pair(1, n)));
    int cnt = 0;
    for (int i = ; i <= k; i++){
        for (int j = 0; j < n; j++){
            while (a[i][0].second > 0){
                a[i][0].second -= i;
                cnt++;
            }
            a[i][0].second = n;
        }
    }
    cout << cnt;
}
// 5
// 1 1 1 1 1
// 2 2 1     2 1 1 1    
// 3 2    3 1 1
// 4 1
//