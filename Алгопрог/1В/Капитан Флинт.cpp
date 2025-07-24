#include <fstream> 
#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
using namespace std; 
int main(){ 
    ifstream fin; 
    ofstream fout;
    fin.open("/Users/dmitrii/Downloads/VSCode/output/input.txt");
    fout.open("/Users/dmitrii/Downloads/VSCode/output/output.txt");
    cout << fin.is_open();
    cout << fout.is_open();
    vector<char> a;
    string b;
    while (fin.eof() != 1){
        scanf("%s", &b);
        for (int i = b.size() - 1; i >= 0; i--)
            a.push_back(b[i]);
        a.push_back(' ');
    }
    for (int i = 0; i < a.size(); i++)
        fout << a[i];
    fin.close();
    fout.close();
}