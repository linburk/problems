#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

bool f(double m, double a, double n){
    return (pow(m, n) < a);
}

int main(){
    double a, n;
    cin >> a >> n;
    double e = 10e-12;
    double l = 0, r = n;
    for (int i = 0; i < 1000; i++){
        double m = (r + l) / 2;
        if (f(m, a, n)){
            l = m;
        }
        else
            r = m;
    }
    cout << setprecision(12) << (l + r) / 2;
}