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

int main() {
    int n;
    cin >> n;
    vector<long long> arr(n + 2);
    arr[0] = 1;
    arr[1] = 1;
    for (int i = 2; i <= n + 1; i++){
        for (int j = 1; j < i; j++){
            arr[i] += (arr[i - j] * arr[j]) % (long long)(1e9 + 7);
        }
        arr[i] %= (long long)(1e9 + 7);
    }
    cout << arr[n + 1];
}