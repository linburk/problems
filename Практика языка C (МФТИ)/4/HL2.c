#include <stdlib.h>
#if 1
struct node_t {
    struct node_t* next;
    int data;
};
#endif

struct node_t* get_start(struct node_t*);

int loop_len(struct node_t* top)
{
    int res;
    struct node_t *start, *p;
    p = start = get_start(top);
    if (start == NULL)
        return 0;
    res = 0;
    do {
        ++res;
        p = p->next;
    } while (p != start);
    return res;
}

struct node_t* get_start(struct node_t* top)
{
    struct node_t *i = top, *j = top;
    while (i != NULL && j != NULL) {
        i = i->next;
        if (j->next == NULL)
            break;
        j = j->next->next;
        if (i == j)
            return i;
    }
    return NULL;
}
