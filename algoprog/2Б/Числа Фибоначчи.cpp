#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main(){
    int n;
    cin >> n;
    int f1, f2;
    f1 = 1;
    f2 = 1;
    int f3 = f1 + f2;
    for (int i = 2; i <= n; i++){
        f1 = f2;
        f2 = f3;
        f3 = f1 + f2;
    }
    
    cout << f1;
}