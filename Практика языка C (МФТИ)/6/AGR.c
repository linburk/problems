// не я чот не пон чо оно делает ващ(

int* to_pointer(long long x)
{
    return (int*)(x);
}

long long foo(long long x, long long y, long long z)
{
    unsigned long long a0, a1, a2, a3, a4, a5, a6, a7;
    unsigned long long t0, t1, t2, t3, t4, t5, t6, t7;
    a0 = x;
    a1 = y;
    a2 = z;

    a5 = a1 << 32;
    t4 = a5 >> 30;
    t4 = a0 + t4;
    t3 = to_pointer(t4)[0];
    a6 = a0;
    a7 = (int)a2;
    if (a1 >= a2)
        goto L7;
    t1 = a7 << 2;
    a5 = a0 + t1;
    a4 = a7;
L6:
    a3 = to_pointer(a5)[0];
    a2 = a6 + t1;
    a4 = a4 - 1;
    if ((long long)a3 <= (long long)t3)
        goto L5;
    a0 = to_pointer(a2)[0];
    a7 = a7 - 1;
    to_pointer(a2)[0] = a3;
    to_pointer(a5)[0] = a0;
    t1 = a7 << 2;
L5:
    a5 = a5 - 4;
    if (a1 < a4)
        goto L6;
    t3 = to_pointer(t4)[0];
    a6 = a6 + t1;
    a5 = to_pointer(a6)[0];
    to_pointer(a6)[0] = t3;
    a0 = (int)a7;
    to_pointer(t4)[0] = a5;
    return a0;
L7:
    t1 = a7 << 2;
    a6 = a6 + t1;
    a5 = to_pointer(a6)[0];
    to_pointer(a6)[0] = t3;
    a0 = a2;
    to_pointer(t4)[0] = a5;
    return a0;
}
