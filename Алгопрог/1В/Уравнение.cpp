#include <iostream>

using namespace std;

int main(){
    int a, b, c;
    if (c < 0)
        cout << "NO SOLUTIONS";
    else if (a == 0 && b < 0)
        cout << "NO SOLUTIONS";
    else if (a == 0 && b == c * c)
        cout << "MANY SOLUTIONS";
    else if ((c * c - b) % a != 0)
        cout << "NO SOLUTIONS";
    else
        cout << (c * c - b) / a;
}