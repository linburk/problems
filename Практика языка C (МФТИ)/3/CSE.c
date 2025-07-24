#include <stdint.h>

void memswap(void* pa, void* pb, int n)
{
    int i = 0;
    char* pca = (char*)pa;
    char* pcb = (char*)pb;
    uintmax_t* pma = (uintmax_t*)pa;
    uintmax_t* pmb = (uintmax_t*)pb;
    for (; i < n && (i & ((1 << sizeof(uintmax_t)) - 1)); ++i) { // align
        char tmp = pca[i];
        pca[i] = pcb[i];
        pcb[i] = tmp;
    }
    for (; i + sizeof(uintmax_t) < n; i += sizeof(uintmax_t)) {
        uintmax_t tmp = pma[i / sizeof(uintmax_t)];
        pma[i / sizeof(uintmax_t)] = pmb[i / sizeof(uintmax_t)];
        pmb[i / sizeof(uintmax_t)] = tmp;
    }
    for (; i < n; ++i) {
        char tmp = pca[i];
        pca[i] = pcb[i];
        pcb[i] = tmp;
    }
}

typedef int (*cmp_t)(void const* lhs, void const* rhs);

int selstep(void* parr, int eltsize, int numelts, int nsorted, cmp_t cmp)
{
    char* pcarr = (char*)parr;
    int pos = nsorted;
    for (int i = pos; i < numelts; ++i) {
        if (cmp(pcarr + eltsize * i, pcarr + eltsize * pos))
            pos = i;
    }
    memswap(pcarr + pos * eltsize, pcarr + nsorted * eltsize, eltsize);
    return 0;
}
