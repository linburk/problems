#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){

    int n, x;
    cin >> n;
    vector<int> a(n);

    for (int i = 0; i < n; i++)
        cin >> a[i];
    
    x = INT_MIN;
    for (int i = 0; i < n; i++){
        x = max(x, a[i]);
    }
    cout << x;
}