#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main(){
    const char alphabet[] {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    stack<char> ans;
    string n;
    getline(cin, n);
    int temp = 0, two = 1;
    for (int i = n.size(); i > 0; i--){
        temp += (two * (n[i - 1] - '0'));
        two *= 2;
    }
    while (temp > 0){
        ans.push(alphabet[temp % 16]);
        temp /= 16;
    }
    while (!ans.empty()){
        cout << ans.top();
        ans.pop();
    }
}