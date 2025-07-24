#include <iostream>
using namespace std;
int main(){
    int n;
    cin >> n;
    cout << n%1440/60 << " " << n%60;
}