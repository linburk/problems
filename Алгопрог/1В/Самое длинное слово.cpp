#include <iostream> 
#include <string>
#include <algorithm>
 
using namespace std; 
int main(){ 
    string a;
    string b, c;
    getline(cin, a);
    int maxx = -1, maxc = 0;
    for (int i = 0; i < a.size(); i++){
        if (a[i] != ' '){
            maxc++;
            b+=a[i];
        }
        else {
            if (maxc > maxx){
                maxx = maxc;
                c = b;
            }
            b = "";
            maxc = 0;
        }
    }
    cout << c << endl;
    cout << maxx;
}