#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int a, b, c;
    cin >> a >> b >> c;

    int pa, pb, pc;
    pa = (a + (a % 2)) / 2;
    pb = (b + (b % 2)) / 2;
    pc = (c + (c % 2)) / 2;

    cout << pa + pb + pc;
}