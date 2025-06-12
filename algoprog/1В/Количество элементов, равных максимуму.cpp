#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int main(){
    int n = 1;
    int max = -2147483648;
    int num = 0;
    while (n != 0){
        cin >> n;
        if (n > max){
            max = n; 
            num = 1;  
        }
        else if (n == max){
            num+= 1;
        }
    }
    cout << num;
}