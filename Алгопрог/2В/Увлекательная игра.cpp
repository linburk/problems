#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
    int n, a, b;
    cin >> n >> a >> b;
    if (a == 0 or b == 0){
        cout << max(a, b);
    }
    else {
        int x = int(ceil(log2(n)));
        x *= max(a, b);
        cout << x;
    }
}