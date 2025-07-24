#include <iostream>
#include <vector>

using namespace std;

int main(){

    int n;
    cin >> n;
    vector<int> a(n + 2);

    for (int i = 0; i < n; i++)
        cin >> a[i];
    
    int x = a[n - 1];
    for (int i = n - 1; i >= 1; i--){
        a[i] = a[i - 1];

    }  
    a[0] = x;

    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
}