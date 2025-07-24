#include <iostream>
using namespace std;

int main(){
    double n;
    unsigned int x;
    cin >> n >> x;
    double res = 1;
    while (x){
        if (x % 2 == 0){
            x /= 2;
            n *= n;
        }
        else {
            x--;
            res *= n;
        }
    }
    cout << res;
}