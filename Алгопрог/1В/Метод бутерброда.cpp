#include <iostream>
#include <string>

using namespace std;

int main(){
    string a;
    string b;
    string s;
    getline(cin, b);
    for (int i = 0; i < b.size() - 1; i++)
        s += b[i];

    int j = 1;
    for (int i = 0; i < s.size() ; i+=2){
        a += s[i];
    }
    for (int i = 1; i < s.size() ; i+=2){
        a += s[i];
    }
    for (int i = 0; i < s.size(); i++)
        cout << a[i];
}