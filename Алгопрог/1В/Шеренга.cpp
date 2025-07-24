#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(int a, int b){
    return b < a;
}

int main(){
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    cin >> a[n];
    int p = a[n];
    sort(a.begin(), a.end(), comp);
    for (int i = 0; i <= n; i++)
        if (a[i] == p){
            cout << i + 1;
            break;
        }
}