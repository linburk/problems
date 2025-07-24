#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    int max = -1001;
    for (int i = 0; i < n; i++){
        if (a[i] > max)
            max = a[i];
    }
    cout << max;
}