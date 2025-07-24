#include <iostream>

#include <algorithm>
#include <string>

using namespace std;


int main() {
    string s;
    getline(cin, s);
    string::iterator st = s.begin();
    while (st < s.end()){
        if (*st == '@')
            st = s.erase(st);
        st++;
    }
    for (auto c : s)
        cout << c;
}