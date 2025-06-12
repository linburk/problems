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
#include <iterator>
using namespace std;

int main(){
    string file_name;
    string mask;
    getline(cin, file_name);
    getline(cin, mask);
    bool flag = true;
    int i = 0, j = 0;
    while (j < mask.size() and flag){
        if (mask[j] == '?'){
            i++;
            j++;
            if (i > file_name.size())
                flag = false;
        } else if (mask[j] == '*'){
            j++;
        } else {
            if (mask[j - 1] == '*'){
                bool check = false;
                for (i; i < file_name.size(); i++){
                    if (file_name[i] == mask[j]){
                        check = true;
                        break;
                    }
                }
                if (check){
                    i++;
                    j++;
                } else {
                    flag = false;
                }
            } else {
                if (file_name[i] != mask[j])
                    flag = false;
                i++;
                j++;
            }
        }
    }
    if (flag)
        cout << "YES";
    else
        cout << "NO";
}