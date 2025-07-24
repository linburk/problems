#include <iostream>
using namespace std;
int main(){
    float ah, am, h, m;
    cin >> ah;
    h = ah / (360 / 12);
    m = (h - int(h)) * 60;
    am = m / 60 * 360;
    cout << am;
}