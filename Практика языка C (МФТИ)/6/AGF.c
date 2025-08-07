int foo(int x, int y)
{
    y = 0; // <- bad tests
    int z, t;
    z = x * x * x;
    if (z < 0) {
        y *= y;
        x += x;
        t = 17;
        t -= x;
        t -= y;
        z += t;
    }
    return z;
}
