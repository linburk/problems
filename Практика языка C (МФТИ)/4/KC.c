#include <string.h>
#if 1
int get_hash(const char* start, const char* fin);
int update_hash(int current, int n, char cprev, char cnext);
unsigned long long pow_mod(unsigned n, unsigned k, unsigned m);
#define R 1
#define Q 1
#else
#include "func.h"
#endif

int rabin_karp(const char* needle, const char* haystack)
{
    unsigned n, target, cur, count = 0, left = 0, right = strlen(needle);

    target = get_hash(needle, needle + right);
    cur = get_hash(haystack, haystack + right);
    n = pow_mod(R, right - 1, Q);

    for (;;) {
        int match = 1;
        while (target != cur && haystack[right] != 0) {
            cur = update_hash(cur, n, haystack[left], haystack[right]);
            left += 1;
            right += 1;
        }
        for (int i = 0; match && i < right - left; ++i)
            match &= needle[i] == haystack[left + i];
        if (match)
            return left;
        if (haystack[right] == 0)
            break;
        cur = update_hash(cur, n, haystack[left], haystack[right]);
        left += 1;
        right += 1;
    }
    return -1;
}
