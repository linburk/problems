#include <iostream>

using namespace std;

int main(){
    
    int x, y, xk, yk;

    cin >> x >> y >> xk >> yk;

    if (xk - x == yk - y)
        cout << "YES";

    else
        cout << "NO";
    
}