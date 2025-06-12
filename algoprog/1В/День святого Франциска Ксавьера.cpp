#include <iostream>

using namespace std;

int main(){
    int b, d;
    cin >> b >> d;
    if (d < 1605)
        cout << 0;
    else if (b < 1605)
        cout << (d - 1605) / 10 + 1;
    else
        cout << (d - b) / 10;
}