#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    
    int n;

    cin >> n;

    n = n + n % 2;

    cout << n;
    
}