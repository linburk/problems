typedef int (*cmp_t)(void const* lhs, void const* rhs);

void* cbsearch(void const* key, void const* base, int num, int size, cmp_t cmp)
{
    char const* pcbase = (char const*)base;
    int l, r, m;
    l = 0;
    r = num;
    while (r - l > 1) {
        m = (l + r) / 2;
        if (cmp(key, pcbase + m * size) >= 0) // ?: key >= base[m]
            l = m;
        else
            r = m;
    }
    if (cmp(key, pcbase + l * size) == 0) // ?: key == base[l]
        return (void*)(pcbase + l * size);
    return 0;
}
