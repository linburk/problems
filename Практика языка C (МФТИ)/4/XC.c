#include <limits.h>
#include <stdlib.h>
#if 1
#define HASH_MAX 1
#endif

typedef int (*get_hash_t)(const char* s);

int ncollisions(char** strs, int n, get_hash_t f)
{
    int ret = 0;
    char* was = calloc(HASH_MAX / CHAR_BIT + 1, sizeof(char));
    if (was == NULL)
        abort(); // ret -1
    for (int i = 0; i < n; ++i) {
        int hash = f(strs[i]);
        if (was[hash / CHAR_BIT] >> (hash % CHAR_BIT) & 1)
            ++ret;
        was[hash / CHAR_BIT] |= 1 << (hash % CHAR_BIT);
    }
    free(was);
    return ret;
}
