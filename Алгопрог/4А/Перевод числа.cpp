#include <iostream>
#include <string>
using namespace std;

int main(){
    string n;
    getline(cin, n);
    int ans = 0, two = 1;
    for (int i = n.size(); i > 0; i--){
        ans += (two * (n[i - 1] - '0'));
        two *= 2;
    }
    cout << ans;
}