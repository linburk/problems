#include <iostream> 
#include <string>
#include <algorithm>
 
using namespace std; 
int main(){ 
    string a;
    string b = " ";
    getline(cin, a);
    while(a.find(b) != a.npos) {
        a.erase(a.find(b), 1);    
    }
    int x = 0;
    for (int i = 0; i < a.size(); i++){
        if (a[i] != a[a.size() - i - 1])
            x++;
    }
    if (x > 0)
        cout << "no";
    else
        cout << "yes";
}