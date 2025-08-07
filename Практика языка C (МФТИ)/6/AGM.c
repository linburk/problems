int foo(int* x, int y, int z)
{
    int i;
    if (z <= 0)
        return z;
    for (i = z - 1; i >= 0; --i) {
        if (x[i] <= y)
            return i + 1;
    }
    return i;
}
