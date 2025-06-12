#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
int main(){
   int n;
   cin >> n;
   vector<vector<int> > lines;
   int m;
   (cin >> m).get();
   for (int i = 0; i < m; i++) {
       int nl;
       vector<int> linetemp(nl);
       cin >> nl;
       for (int j = 0; j < nl; j++){
            int a;
            cin >> a;
            linetemp[i] = a - 1;
       }
       lines.push_back((linetemp));
   }

}