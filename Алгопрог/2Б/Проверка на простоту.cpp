#include <iostream>

using namespace std;

int main(){
    long long n;
    cin >> n;
    bool flag = true;
    for (int i = 2; i < n / 2 + 2; i++){
        if (n % i == 0){
            flag = false;
            break;
        }
    }
    if (flag)
        cout << "prime";
    else
        cout << "composite";
}