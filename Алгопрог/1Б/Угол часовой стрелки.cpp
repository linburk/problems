#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int main(){

    double h, m, s;
    cin >> h >> m >> s;
    cout << (h * 3600 + m * 60 + s) / (12 * 3600) * 360;
}