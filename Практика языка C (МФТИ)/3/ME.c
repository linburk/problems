int majority_element(int const* parr, int len)
{
    int cur, cnt = 0;
    if (len == 0)
        return -1;
    for (int i = 0; i < len; ++i) {
        if (cnt == 0)
            cur = parr[i], ++cnt;
        else if (parr[i] == cur)
            ++cnt;
        else
            --cnt;
    }
    if (cnt == 0)
        return -1;
    cnt = 0;
    for (int i = 0; i < len; ++i)
        cnt += parr[i] == cur;
    return cnt > len / 2 ? cur : -1;
}
