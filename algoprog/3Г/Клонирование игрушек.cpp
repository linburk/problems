#include <iostream>

using namespace std;

int main() {
    int x, y;
    cin >> y >> x;
    if (y >= x - 1 and (y - x - 1) % 2 == 0 and !(x == 1 and y > 0 or y == 1 and x == 0))
        cout << "Yes";
    else
        cout << "No";
}