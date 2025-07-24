#include <iostream>

#include <algorithm>
#include <string>

using namespace std;

void enter(string &login){
    char c;
    while (cin.get(c)){
        if (c == '0' or c == 'O' or c == 'o')
            login.push_back('{');
        else if (c == 'I' or c == '1' or c == 'l' or c == 'i' or c == 'L')
            login.push_back(';');
        else if (islower(c)){
            login.push_back(c - ('a' - 'A'));
        }
        else if (c != '\n')
            login.push_back(c);
        else
            break;
    }
}

int main() {
    string login;
    enter(login);
    bool flag = 1;
    int n;
    cin >> n;
    cin.get();
    for (int i = 0; i < n; i++){
        string templogin;
        enter(templogin);
        if (templogin == login)
            flag = 0;
    }
    if (flag)
        cout << "Yes";
    else
        cout << "No";
}