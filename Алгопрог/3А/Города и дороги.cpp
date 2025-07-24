#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int cnt;
    for (int i = 0; i < n * n; i++){
            int x;
            cin >> x;
            if (x == 1)
                cnt++;
    }
    cout << cnt / 2;
    // :)
}