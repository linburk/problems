#include <stdlib.h>
#include <string.h>

typedef int (*xcmp_t)(void* lhs, int lsz, void* rhs, int rsz);

void xmerge(void* lmem, int* lsizes, int lnelts, void* rmem, int* rsizes, int rnelts, void* dst, int* dst_sizes, xcmp_t cmp);
int sum(int* arr, int len);

void xmsort(void* mem, int* sizes, int nelts, xcmp_t cmp)
{
    char* pcmem = (char*)mem;
    void* dst;
    int* dst_sizes;
    int m, half_size, all_size;
    if (nelts == 1)
        return;
    m = nelts / 2;
    half_size = sum(sizes, m);
    all_size = sum(sizes, nelts);
    xmsort(pcmem, sizes, m, cmp);
    xmsort(pcmem + half_size, sizes + m, nelts - m, cmp);
    dst = malloc(all_size);
    if (dst == NULL)
        /* ret err */;
    dst_sizes = malloc(nelts * sizeof(int));
    if (dst_sizes == NULL)
        /* free dst & ret err */;
    xmerge(pcmem, sizes, m, pcmem + half_size, sizes + m, nelts - m, dst, dst_sizes, cmp);
    memcpy(pcmem, dst, all_size);
    memcpy(sizes, dst_sizes, sizeof(int) * nelts);
    free(dst);
    free(dst_sizes);
    return;
}

void xmerge(void* lmem, int* lsizes, int lnelts,
    void* rmem, int* rsizes, int rnelts,
    void* dst, int* dst_sizes, xcmp_t cmp)
{
    char* pcl = (char*)lmem;
    char* pcr = (char*)rmem;
    char* pcd = (char*)dst;
    int l = 0, r = 0, d = 0;
    int len = lnelts + rnelts;
    while (d < len) {
        while (l < lnelts && (r == rnelts || cmp(pcl, lsizes[l], pcr, rsizes[r]) <= 0)) {
            memcpy(pcd, pcl, lsizes[l]);
            dst_sizes[d] = lsizes[l];
            pcd += lsizes[l];
            pcl += lsizes[l];
            ++l;
            ++d;
        }
        while (r < rnelts && (l == lnelts || cmp(pcr, rsizes[r], pcl, lsizes[l]) <= 0)) {
            memcpy(pcd, pcr, rsizes[r]);
            dst_sizes[d] = rsizes[r];
            pcd += rsizes[r];
            pcr += rsizes[r];
            ++r;
            ++d;
        }
    }
}

int sum(int* arr, int len)
{
    int res = 0;
    for (int i = 0; i < len; ++i)
        res += arr[i];
    return res;
}
