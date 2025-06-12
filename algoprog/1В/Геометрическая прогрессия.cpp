#include <iostream>
#include <iomanip>
using namespace std;
int main(){
    double n, x;
    cin >> n >> x;
    double xn = 1, sum = 0;
    for (int i = 0; i < n; i++){
        sum += xn;
        xn *= x;
    }
    cout << fixed << setprecision(6) << sum;
}