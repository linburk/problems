#include <iostream>
#include <math.h>
using namespace std;
int main(){
    int an, an1, n;
    cin >> n >> an >> an1;
    int a1, a2;
    for (int i = 0, c; i < n - 1; i++){
        c = an;
        an = an1 - an;
        an1 = c;
    }
    cout << an << " " << an1;
}