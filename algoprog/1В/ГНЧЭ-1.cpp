#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for (int j = 0, i = 1; i <= n; i++){
        for (int jlast = j; j < jlast + i; j++){
            a[j] = i;
        }
    }
    for (int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
}