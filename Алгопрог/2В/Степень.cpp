#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
    long long a;
    cin >> a;
    if (a % 2 == 0){
        int x;
        x = round(sqrt(a));
        if (x % 2 == 1)
            x++;
        for (long long i = x; i <= a; i += 2){
            if ((i * i) % a == 0){
                cout << i;
                break;
            }
        }
    }
    else {
        int x;
        x = round(sqrt(a));
        if (x % 2 == 0)
            x++;
        for (long long i = x; i <= a; i += 2){
            if ((i * i) % a == 0){
                cout << i;
                break;
            }
        }
    }
}