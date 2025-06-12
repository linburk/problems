#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int main(){
    int n = 1;
    int prev = 0;
    int num = 0;
    int maxn = -1;
    while (n != 0){
        cin >> n;
        if (n == prev){
            num++;
        }
        else 
            num = 1;
        if (num > maxn)
            maxn = num;
        prev = n;
    }
    cout << max