#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define INT_MIN (-2147483647-1)
int main(){

    int n;
    cin >> n;

    vector<int> a(3 * n , INT_MIN);

    for (int i = n; i < n * 2; i++)
        cin >> a[i];

    int k;
    cin >> k;
    k %= n;

    if (k > 0)
    {
        for (int i = n - k; i < n; i++){
            swap(a[i], a[n + i]);
        }
    }
    else if (k < 0)
    {
        k = abs(k);
        for (int i = 0; i < k; i++){
            swap(a[n + i], a[n * 2 + i]);
        }

    }

    int ind;
    for (int i = 0; i <= 3 * n; i++){
        if (a[i] != INT_MIN){
            ind = i;
            break;
        }
    }

    for (int i = ind; i < ind + n; i++){
        cout << a[i] << " ";
    }

}