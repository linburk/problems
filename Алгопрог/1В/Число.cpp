#include <iostream> 
#include <string>
#include <algorithm>
#include <vector>
using namespace std; 
int main(){ 
    string a;
    getline(cin, a);
    vector<char> b;
    for (int i = a.size() - 1; i >= 0; i--){
        b.push_back(a[i]);
        if ((a.size() - i) % 3 == 0)
            b.push_back(',');
    }
    for (int i = b.size() - 1; i >= 0; i--)
        cout << b[i];
}