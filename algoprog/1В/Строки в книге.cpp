#include <iostream>

using namespace std;

int main(){
    
    int stronpage, str;

    cin >> stronpage >> str;

    int p, s;
    
    p = (str + stronpage - 1) / stronpage;
    s = str - stronpage * (p - 1);

    cout << p << " " << s;
    
}