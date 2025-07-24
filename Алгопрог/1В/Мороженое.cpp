#include <iostream>

using namespace std;

int main(){
    int k;
    if (k % 3 == 0 || k % 5 == 0)
        cout << "YES";
    else if ((k - 3) % 5 == 0 || (k - 5) % 3 == 0)
        cout << "YES";
    else if ((k - 6) % 5 == 0 || (k - 10) % 3 == 0)
        cout << "YES";
    else if ((k - 9) % 5 == 0 || (k - 15) % 3 == 0)
        cout << "YES";
    else if ((k - 12) % 5 == 0 || (k - 20) % 3 == 0)
        cout << "YES";
    else if ((k - 25) % 3 == 0)
        cout << "YES";
    else 
        cout << "NO";
}