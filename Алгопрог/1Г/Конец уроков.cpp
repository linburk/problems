#include <iostream>
#include <math.h>
using namespace std;
int main(){
    int n, time = 0;
    cin >> n;
    if (n % 2 == 0){
        time += n / 2 * 5 + (n - 2) / 2 * 15;
    }
    else 
        time += (n - 1) / 2 * 5 + (n - 1) / 2 * 15;
    time += n * 45;
    cout << 9 + time / 60 << " " << time % 60;
}