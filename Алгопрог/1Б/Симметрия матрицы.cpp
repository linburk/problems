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

    bool symmetry = false;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> a[i][j];
        }
    }
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (a[i][j] == a[j][i]) 
                symmetry = 1;
            else 
                symmetry = 0;
        }
    }
    if (symmetry)
        cout << "yes";
    else
        cout << "no";
}