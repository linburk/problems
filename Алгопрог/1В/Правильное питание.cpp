#include <iostream>
#include <math.h>

using namespace std;

int main(){
    double x, y, z, sx, sy, sz;
    sx = 0;
    sy = 0; 
    sz = 0;

    cin >> x >> y >> z;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++){
        int nq;
        double xx, yy, zz;
        cin >> xx >> yy >> zz >> nq;
        sx += xx * nq;
        sy += yy * nq;
        sz += zz * nq;
    }
    if ((sx > x || abs(x - sx) < pow(10, -6)) && (abs(z - sz) < pow(10, -6) || sz > z) && (abs(y - sy) < pow(10, -6) || sy > y))
        cout << "YES";
    else
        cout << "NO";
}