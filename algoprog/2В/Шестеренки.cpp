#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

unsigned long gcd(unsigned long a, unsigned long b) { 
    if (b == 0) 
        return a; 
    return gcd(b, a % b); 
} 

int main(){
    unsigned long a, b;
    cin >> a >> b;
    unsigned long shesterenkanok = a * b / gcd(a, b);
    cout << shesterenkanok;
}
//