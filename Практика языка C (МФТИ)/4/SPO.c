#include <stdio.h>
#include <stdlib.h>

#if 1
struct tree_t {
    struct tree_t* left;
    struct tree_t* right;
    int data;
};
#endif

struct stacktree_t {
    struct stacktree_t* prev;
    struct tree_t* data;
};

int push(struct stacktree_t** top, struct tree_t* data)
{
    struct stacktree_t* tmp = calloc(1, sizeof(struct stacktree_t));
    if (tmp == NULL)
        return -1;
    tmp->prev = *top;
    tmp->data = data;
    *top = tmp;
    return 0;
}

struct tree_t* pop(struct stacktree_t** top)
{
    struct stacktree_t* tmp;
    struct tree_t* ret;
    if (top == NULL || *top == NULL)
        return NULL;
    tmp = (*top)->prev;
    ret = (*top)->data;
    free(*top);
    *top = tmp;
    return ret;
}

void print_pre(struct tree_t* top)
{
    struct stacktree_t* stack = NULL;
    int err;
    if (top == NULL)
        return;
    err = push(&stack, top);
    if (err == -1)
        abort();
    while (stack != NULL) {
        top = pop(&stack);
        if (top == NULL)
            continue;
        printf("%d ", top->data);
        err = push(&stack, top->right);
        if (err == -1)
            abort();
        err = push(&stack, top->left);
        if (err == -1)
            abort();
    }
}
