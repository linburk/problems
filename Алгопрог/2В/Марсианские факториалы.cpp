#include <queue>
#include <deque>
#include <iostream>
#include <set>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <list>
#include <iterator>
using namespace std;

int main(){
    long long n, k, nulls = 0;
    cin >> n >> k;
    long long maxdelitel;
    int j = 2, t = k;
    for (int j = 2; j * j <= k; j++) {
        if (t % j == 0) {
            maxdelitel = j;
            while (t % j == 0)
                t /= j;
        }
    }
    if (t > maxdelitel)
        maxdelitel = t;

    int i = 1;
    while (n != 0){
        long long umn = pow(maxdelitel, i);
        nulls += n / umn;
        n /= umn;
    }
    cout << nulls;
}
//
// 1
// 2
// 6
// 24
// 120
// 12
//