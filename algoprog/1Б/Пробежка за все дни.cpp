#include <iostream>

using namespace std;

int main(){

    double x, y, s;
    cin >> x >> y;
    int cnt = 1;
    s = x;

    while (s < y){
        x = x * 170 / 100;
        cnt++;
        if (abs(s - x) < pow(10, -6))
            break;
        s += x;
    }

    cout << cnt;
}