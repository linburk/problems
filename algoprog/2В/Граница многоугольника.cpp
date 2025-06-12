#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int gcd(int a, int b)
{
    while (b) {
		a = a % b;
		swap(a, b);
	}
    return a;
}

int main()
{  
    int n;
    cin >> n;
    vector<pair<int,int> > a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
    }
    int sum = 0;
    for (int i = 0; i < n; i++){
        int x1 = a[i].first;
        int y1 = a[i].second;
        int x2 = a[(i + 1) % n].first;
        int y2 = a[(i + 1) % n].second;
        x1 = abs(x1 - x2);
        y1 = abs(y1 - y2);
        int x = gcd(x1, y1);
        sum += x;
    }
    cout << sum;
}