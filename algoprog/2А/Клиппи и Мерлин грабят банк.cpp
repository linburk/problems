#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
    int n, k;
    cin >> n >> k;
    vector<int> a(n + n);
    vector<int> pref(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 0; i < n; i++){
        pref[i] = a[i] + a[i + k + 1];
    }

    int max = -1, maxi;
    for (int i = 0; i < n; i++){
        if (pref[i] > max){
            max = pref[i];
            maxi = i;
        }
    }
    cout << maxi + 1 << " " << maxi + k + 2;
    
}