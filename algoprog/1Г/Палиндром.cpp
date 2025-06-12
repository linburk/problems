#include <queue>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <list>
using namespace std;


int main() {
    deque<char> d;
    map<char, int> m;
    int n;
    cin >> n;
    cin.get();
    string s;
    getline(cin, s);
    for (auto c : s){
        m[c]++;
    }
    for (char c = 'Z'; c >= 'A'; c--){
        if (m[c] >= 2){
            int i = m[c] / 2;
            m[c] %= 2;
            for (i; i > 0; i--) {
                d.push_back(c);
                d.push_front(c);
            }
        }
    }
    for (char c = 'A'; c <= 'Z'; c++){
        if (m[c] == 1){
            d.insert(d.begin() + (d.size() + 1) / 2, c);
            break;
        }
    }
    for (auto i : d){
        cout << i;
    }
}