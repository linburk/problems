#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){

    int n;
    cin >> n;
    vector<vector<int> > a;
    vector<int> b(n);
    for (int i = 0; i < n; i++)
        a.push_back(b);


    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> a[i][j];
        }
    }
    int x, ilast, jlast;
    x = -2147483648

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            x = max(x, a[i][j]);
            ilast = i;
            jlast = j;
        }
    }
    
    cout << x << endl;
    cout << ilast << " " < jlast;
}