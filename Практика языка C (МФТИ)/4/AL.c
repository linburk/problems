#include <stdio.h>
#include <stdlib.h>
#if 1
struct node_t {
    struct node_t* next;
    int data;
};
#endif

int add_node(struct node_t** last, int x)
{
    struct node_t* tmp = calloc(1, sizeof(struct node_t));
    if (tmp == NULL)
        return -1;
    tmp->data = x;
    if (*last == NULL)
        *last = tmp;
    else
        (*last)->next = tmp;
    *last = tmp;
    return 0;
}

struct node_t* read_list(FILE* inp)
{
    int x;
    int err;
    struct node_t *even_first = NULL, *odd_first = NULL;
    struct node_t *even_last = NULL, *odd_last = NULL;
    for (;;) {
        err = fscanf(inp, "%d", &x);
        if (err == EOF)
            break;
        if (err != 1)
            abort();
        if (x % 2 == 0) {
            err = add_node(&even_last, x);
            if (err == -1)
                abort();
            if (even_first == NULL)
                even_first = even_last;
        } else {
            err = add_node(&odd_last, x);
            if (err == -1)
                abort();
            if (odd_first == NULL)
                odd_first = odd_last;
        }
    }
    if (even_last == NULL)
        return odd_first;
    even_last->next = odd_first;
    return even_first;
}
void delete_list(struct node_t* top)
{
    if (top == NULL)
        return;
    delete_list(top->next);
    free(top);
}
