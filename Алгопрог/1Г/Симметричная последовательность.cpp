#include <iostream>
#include <cmath>
#include <queue>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> acopy;
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    acopy = a;
    reverse(acopy.begin(), acopy.end());
    int cnt = 0;
    while (1){
        bool flag = true;
        for (int i = 0; i < n - cnt; i++){
            if (a[i + cnt] != acopy[i]){
                flag = false;
                cnt++;
                break;
            }
        }
        if (flag){
            break;
        }
        
    }
    cout << cnt << endl;
    for (int i = n - cnt; i < n; i++){
        cout << acopy[i] << " ";
    }
}