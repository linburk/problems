#include <iostream>
using namespace std;
int main(){
    int n, x; cin >> n;
    bool flag = true;
    for (int i = 0; i < n; i++){cin >> x; if (x==0)flag=0;}
    if (flag)cout<<"NO";else cout << "YES";}