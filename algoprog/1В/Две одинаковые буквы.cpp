#include <iostream> 
#include <string>
#include <algorithm>
#include <vector>
using namespace std; 
int main(){ 
    string a;
    vector<char> b;
    getline(cin, a);
    char last;
    for (int i = 0; i < a.size(); i++){
        b.push_back(a[i]);
        if (find(b.begin(), b.end(), a[i]) != b.end())
            last = a[i];
    }
    cout << last;
}