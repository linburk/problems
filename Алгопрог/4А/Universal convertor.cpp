#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <stack>
using namespace std;

string convertor(int n, string A, int k){

    unordered_map<char, int> alphabetresult;
    unordered_map<int, char> alphabetcharacters;

    stack<char> result_of_converting;
    string result_of_function;

    for (int i = 0; i <= 9; i++){
        alphabetresult[i + '0'] = i;
        alphabetcharacters[i] = i + '0';
    }

    for (int i = 10; i <= 36; i++){
        alphabetresult[i + 'A' - 10] = i;
        alphabetcharacters[i] = i + 'A' - 10;
    }

    int temppower = 1, tempvalue = 0;

    for (int i = A.size() - 1; i >= 0; i--){
        tempvalue += (alphabetresult[A[i]] * temppower);
        temppower *= n;
    }

    while (tempvalue > 0){
        result_of_converting.push(alphabetcharacters[tempvalue % k]);
        tempvalue /= k;
    }

    while (not result_of_converting.empty()){
        result_of_function += result_of_converting.top();
        result_of_converting.pop();
    }

    return result_of_function;
}


int main(){
    int n, k;
    string A;
    cin >> n;
    cin.get();
    getline(cin, A);
    cin >> k;
    cout << convertor(n, A, k);
}