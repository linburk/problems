#include <iostream>
using namespace std;
int main(){
    int a, b, n;
    cin >> a >> b >> n;
    int k;
    k = a * 100 + b;
    k *= n;
    cout << k/100 << " " << k%100;
}