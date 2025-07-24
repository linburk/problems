#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    long long last = 9;
    long long now = 9;
    for (int i = 1; i < n; i++){
        now = (last - 1) * 3 + 2;
        last = now;
    }
    cout << now;
}