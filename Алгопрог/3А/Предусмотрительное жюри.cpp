#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
using namespace std;

bool comp(int a, int b){
    return a >= b;
}

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> acopy(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    acopy = a;
    sort(acopy.begin(), acopy.end(), comp);
    
    for (int i = 0; i < n; i++){
        int x = acopy[i];
        int xi = distance(a.begin(), find(a.begin(), a.end(), x));

        cout << xi + 1 << " ";
        a[xi] = -1;
    }
}