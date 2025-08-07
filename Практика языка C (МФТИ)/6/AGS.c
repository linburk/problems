int callee(int, int, int);

int caller(int x, int pow, int mod)
{
    int ret = 1;
    if (pow == 0)
        return 1;
    x = x % mod;
    do {
        if (pow % 2 == 0) {
            x = callee(x, x, mod);
            pow >>= 1;
        } else {
            ret = callee(ret, x, mod);
            pow -= 1;
        }
    } while (pow > 0);
    return ret;
}
