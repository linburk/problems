#include <math.h>

int foo(int x)
{
    double a, b, c;
    a = log(log(x));
    b = log(x);
    c = (a + b) * x;
    return round(c);
}
