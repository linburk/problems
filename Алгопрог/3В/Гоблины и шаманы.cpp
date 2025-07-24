#include <queue>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

int main() {
    int n;
    cin >> n;
    deque<int> d;
    deque<int>::iterator middle;
    for (int i = 0; i < n; i++){
        middle = (d.begin() + (d.size() + 1) / 2 );
        int num;
        char c;
        cin >> c;
        if (c == '+'){
            cin >> num;
            d.push_back(num);
        }
        if (c == '*'){
            cin >> num;
            d.insert(middle, num);
        }
        if (c == '-'){
            cout << d.front() << endl;
            d.pop_front();
        }
    }
}