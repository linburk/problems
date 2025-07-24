#include <stdlib.h>
#if 1
struct node_t {
    struct node_t* next;
    int data;
};
#endif

int list_is_a_loop(struct node_t* top)
{
    struct node_t *i = top, *j = top;
    while (i != NULL && j != NULL) {
        i = i->next;
        if (j->next == NULL)
            return 0;
        j = j->next->next;
        if (i == j)
            return 1;
    }
    return 0;
}
