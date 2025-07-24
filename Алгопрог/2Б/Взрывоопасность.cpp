#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int cur, last1, last2;
    last1 = 2;
    last2 = 1;
    for (int i = 2; i <= n; i++){
        cur = last2 + last1;
        last2 = last1;
        last1 = cur;
    }
    cout << cur;
}