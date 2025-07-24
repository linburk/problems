#include <iostream>
#include <cmath>
using namespace std;

int main()
{  

    int n;
    cin >> n;

    vector<int> a(n);
    vector<int> sum(n - 1);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
   
    sort(a.begin(), a.end());

    sum[0] = a[1] - a[0];
    sum[1] = a[2] - a[0];
    
    for (int i = 2; i < n - 1; i++)
    {
        sum[i] = min(sum[i - 1], sum[i - 2]) + (a[i + 1] - a[i]);
    }
    cout << sum[n - 2];
}