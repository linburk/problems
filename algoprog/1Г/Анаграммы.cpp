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
    map<char, int> m1, m2;
    for (int i = 0; i < 256; i++){
        m1[char(i)] = 0;
        m2[char(i)] = 0;
    }
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    for (auto c : s1){
        m1[c]++;
    }
    for (auto c : s2){
        m2[c]++;
    }
    for (int i = 0; i < 256; i++){
        if (m1[char(i)] != m2[char(i)]){
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
}