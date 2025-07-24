#include <iostream>
using namespace std;
int main(){
    int ss;
    cin >> ss;
    cout << ss / 3600 % 24 << ":" << ss / 60 / 10 % 6 << ss / 60 % 10 << ":" << ss / 10 % 6 << ss % 10;
}