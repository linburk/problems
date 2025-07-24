#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
    long long a, b, c;
    cin >> a >> b >> c;
    long long a1 = a, b1 = b;
    while (b1){
        a1 = a1 % b1;
        swap(a1, b1);
    }
    long long line = a + b - a1;
    long long square = a * b;
    long long plitki = (square - line) / 2;
    
    cout << c - (plitki % (c + 1));
}