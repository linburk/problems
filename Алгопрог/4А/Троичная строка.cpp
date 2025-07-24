#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main(){
   long long t;
   cin >> t;
   cin.get();
   for (long long t1 = 0; t1 < t; t1++){
       string s;
       getline(cin, s);
       long long p = 0, u1 = -1, u2 = -1, u3 = -1, minimal = 1e9;
       while (p < s.size()) {
           if (s[p] == '1') {
               u1 = p;
           }
           else if (s[p] == '2') {
               u2 = p;
           }
           else if (s[p] == '3')
               u3 = p;
           long long temps = (max(max(u1, u2), u3) - min(min(u1, u2), u3) + 1);
           if (temps < minimal and (u1 != -1) and (u2 != -1) and (u3 != -1))
               minimal = temps;
           p++;
       }
       if (minimal == 1e9)
           cout << 0 << endl;
       else
           cout << minimal << endl;
   }
}