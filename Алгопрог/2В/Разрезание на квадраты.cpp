#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
    long long a, b;
    cin >> a >> b;
    if (b > a) 
        swap(a, b);
    int cnt = 0;
    while (a and b){
        a -= b;
        cnt++;
        if (b > a){
            swap(a, b);
        }
    }
    cout << cnt;
}