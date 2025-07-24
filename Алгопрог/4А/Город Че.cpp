#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n, r;
    cin >> n >> r;
    vector<int> memories(n);
    for (int i = 0; i < n; i++)
        cin >> memories[i];
    int i = 0, j = 0;
    int cnt = 0;
    while (i < n and j < n){
        if (memories[j] - memories[i] > r){
            cnt += (n - j);
            i++;
        }
        else
            j++;
    }
    cout << cnt;
}