#include <iostream>

#include <cmath>
#include <set>

using namespace std;


int main() {
    set<long long> numbers23;
    for (int y = 0; y <= 20; y++){
        for (int x = 0; x <= 30; x++){
            numbers23.insert(pow(2, x) * pow(3, y));
        }
    }
    int l, r;
    int cnt = 0;
    cin >> l >> r;
    for (auto i : numbers23){
        if (i >= l and i <= r){
            cnt++;
        }
        if (i > r)
            break;
    }
    cout << cnt;
}