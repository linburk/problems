#include <stdio.h>
#include <stdlib.h>

struct tree_T {
    struct tree_T* left;
    struct tree_T* right;
    int data;
};

int input_array(int*, int);
struct tree_T* build_from_orders(int* pre, int* in, int len, int* err);
void print_postorder(struct tree_T*);
void free_tree(struct tree_T*);

int main()
{
    int err;
    int len;
    int *pre, *in;
    struct tree_T* tree;
    err = scanf("%d", &len);
    if (err != 1)
        abort();
    pre = calloc(len, sizeof(int));
    if (pre == NULL)
        abort();
    in = calloc(len, sizeof(int));
    if (in == NULL)
        goto free_and_abort;
    err = input_array(pre, len);
    if (err != len)
        goto free_and_abort;
    err = input_array(in, len);
    if (err != len)
        goto free_and_abort;
    tree = build_from_orders(pre, in, len, &err);
    if (err == -1)
        goto free_and_abort;
    print_postorder(tree);
    free(pre);
    free(in);
    free_tree(tree);
    return 0;
free_and_abort:
    free(pre);
    free(in);
    free_tree(tree);
    abort();
}

int input_array(int* arr, int len)
{
    int err;
    for (int i = 0; i < len; ++i) {
        err = scanf("%d", arr + i);
        if (err != 1)
            return i;
    }
    return len;
}

void print_postorder(struct tree_T* top)
{
    if (top == NULL)
        return;
    print_postorder(top->left);
    print_postorder(top->right);
    printf("%d ", top->data);
}

void free_tree(struct tree_T* top)
{
    if (top == NULL)
        return;
    free_tree(top->left);
    free_tree(top->right);
    free(top);
}

int find(int* arr, int len, int x)
{
    for (int i = 0; i < len; ++i) {
        if (arr[i] == x)
            return i;
    }
    return len;
}

struct tree_T* build_fo_impl(int* pre, int* in, int l, int r, int* i, int* err)
{
    struct tree_T *left, *right, *top;
    int elem, pos;
    if (r - l <= 0)
        return NULL;
    elem = pre[*i];
    ++(*i);
    pos = l + find(in + l, r - l, elem);
    top = calloc(1, sizeof(struct tree_T));
    if (top == NULL) {
        *err = -1;
        return NULL;
    }
    top->data = elem;
    left = build_fo_impl(pre, in, l, pos, i, err);
    if (*err == -1) {
        free_tree(top);
        return NULL;
    }
    top->left = left;
    right = build_fo_impl(pre, in, pos + 1, r, i, err);
    if (*err == -1) {
        free_tree(top);
        return NULL;
    }
    top->right = right;
    return top;
}

struct tree_T* build_from_orders(int* pre, int* in, int len, int* err)
{
    int i = 0;
    return build_fo_impl(pre, in, 0, len, &i, err);
}
