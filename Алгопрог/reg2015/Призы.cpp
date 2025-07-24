#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int max = 0;
    for (int i = 0; i < k; i++)
        max += a[i];
    int cur = max;
    int max2 = cur;
    int l1 = 0, r1 = k - 1, l2, r2;
    for (int i = k; i < n - 1; i++){
        cur -= a[i - k];
        cur += a[i + 1];
        if (cur > max){
            l2 = l1;
            r2 = r2;
            l1 = i - k + 1;
            r2 = i + 1;
            max2 = max;
            max = cur;
            
        }
    }
    if (l1 > l2 or r2 < r1){
        cout << max;
    }
    else
        cout << max2;
}