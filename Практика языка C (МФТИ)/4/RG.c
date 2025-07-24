typedef int (*generator_t)(int);

unsigned get_start(generator_t gen)
{
    int i = gen(0);
    int j = gen(gen(0));
    while (i != j) {
        i = gen(i);
        j = gen(gen(j));
    }
    return i;
}

unsigned cycle_len(generator_t gen)
{
    int start, p, i;
    p = start = get_start(gen);
    i = 0;
    do {
        ++i;
        p = gen(p);
    } while (p != start);
    return i;
}
