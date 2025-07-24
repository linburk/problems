#include <iostream>
#include <math.h>

using namespace std;

int main(){
    int n, f = 1;
    cin >> n;
    double s = 1;
    for (int i = 1; i <= n; i++){
        s += 1/double(f);
        f *= (i + 1);
    }
    cout << s;
}