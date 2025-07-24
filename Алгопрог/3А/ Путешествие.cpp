#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int N, k, s;
    cin >> N >> k >> s;
    vector<int> a(s);
    for (int i = 0; i < s; i++)
        cin >> a[i];
    int start = 0;
    int cnt = 0;
    int i = 0;
    while (start != N)
    {
        if (start + k >= N) {
            break;
            
        }
        else if (start + k >= a[i]){
            start = a[i];
            cnt++;
            i++;
        }
        else {
            cout << -1;
            return 0;
        }
    }
    cout << cnt;
}