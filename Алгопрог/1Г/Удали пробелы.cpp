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
    string s;
    getline(cin, s);
    string::iterator st1 = s.begin(), st2 = s.begin();
    while (st2 < s.end()){
        bool flag = 0;
        if (*st1 == ' '){
            flag = 1;
            while (*st2 == ' ')
                st2++;
        }
        if (flag) {
            s.erase(st1, st2);
            st1 = s.insert(st1, ' ');
        }
        st1++;
        st2 = st1;
    }
    for (auto c : s)
        cout << c;
}