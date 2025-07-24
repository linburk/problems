#include <queue>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <list>
using namespace std;

int main(){
    long long x;
    cin >> x;
    long long index_C = 1, index_A = 1, index_B = 1;
    while (true){
        if (pow(index_A, 2) == pow(index_B, 3)){
            if (index_C == x){
                cout << (long long)pow(index_A, 2);
                break;
            }
            else {
                index_A++;
                index_B++;
                index_C++;
            }
        }
        else if (pow(index_A, 2) < pow(index_B, 3)){
            if (index_C == x){
                cout << (long long)pow(index_A, 2);
                break;
            }
            else {
                index_A++;
                index_C++;
            }
        }
        else {
            if (index_C == x) {
                cout << (long long)pow(index_B, 3);
                break;
            }
            else {
                index_C++;
                index_B++;
            }
        }
    }
}