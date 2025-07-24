#include <stdio.h>
#include <stdlib.h>

struct tree_T {
    struct tree_T* left;
    struct tree_T* right;
    int data;
};

struct tree_T* add(struct tree_T*, int, int* err);
void print_preorder(struct tree_T*);
void free_tree(struct tree_T*);

int main()
{
    int err;
    struct tree_T* bst = NULL;
    FILE* in = NULL;
    int len;
    in = fopen("input.txt", "r");
    if (in == NULL)
        abort();
    err = fscanf(in, "%d", &len);
    if (err != 1)
        goto free_and_abort;
    for (int i = 0; i < len; ++i) {
        int x;
        err = fscanf(in, "%d", &x);
        if (err != 1)
            goto free_and_abort;
        bst = add(bst, x, &err);
        if (err == -1)
            goto free_and_abort;
    }
    print_preorder(bst);
    fclose(in);
    free_tree(bst);
    return 0;
free_and_abort:
    fclose(in);
    free_tree(bst);
    abort();
}

void print_preorder(struct tree_T* top)
{
    if (top == NULL)
        return;
    printf("%d ", top->data);
    print_preorder(top->left);
    print_preorder(top->right);
}

void free_tree(struct tree_T* top)
{
    if (top == NULL)
        return;
    free_tree(top->left);
    free_tree(top->right);
    free(top);
}

struct tree_T* add(struct tree_T* top, int x, int* err)
{
    if (top == NULL) {
        top = calloc(1, sizeof(struct tree_T));
        if (top == NULL) {
            *err = -1;
            return NULL;
        }
        top->data = x;
        return top;
    }
    if (x < top->data) {
        top->left = add(top->left, x, err);
    } else {
        top->right = add(top->right, x, err);
    }
    return top;
}
