#include <stdlib.h>
#if 1
struct node_t {
    struct node_t* next;
    int data;
};
#endif

struct node_t* reverse(struct node_t* top)
{
    struct node_t* prev = NULL;
    struct node_t* tmp;
    while (top != NULL) {
        tmp = top->next;
        top->next = prev;
        prev = top;
        top = tmp;
    }
    return prev;
}
