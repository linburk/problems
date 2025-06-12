#include <iostream>
#include <cmath>
using namespace std;

int search(int k){
    if (k == 0) return 0;
    else return (search(k - pow(2,int(log2(k)))) + 1);
}

int main()
{  
    int k;
    cin >> k;
    cout << search(k - 1) % 3;
}