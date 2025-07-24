#include <iostream>
#include <cmath>
using namespace std;
int main(){
    double ah, am;
    cin >> ah;
    double h = ah / (360 / 12);
    double m = h * 60 - floor(h) * 60;
    double s = h * 60 * 60 - floor(h) * 60 * 60 - floor(m)  * 60;
    cout << round(h) << " " << round(m) << " " << round(s);
}