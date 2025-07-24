#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct treenode_T {
    struct treenode_T* left;
    struct treenode_T* right;
    int data;
    int size;
    int height;
};
struct tree_T { // <- AVL parody
    struct treenode_T* top;
};
void init_tree(struct tree_T*);
void add(struct tree_T*, int val, int* err);
int get(struct tree_T*, int l, int r);
void free_tree(struct tree_T*);

int main()
{
    int err;
    struct tree_T tree;
    int n, q;
    err = scanf("%d", &n);
    if (err != 1 || n < 0)
        abort();
    init_tree(&tree);
    for (int i = 0; i < n; ++i) {
        int x;
        err = scanf("%d", &x);
        if (err != 1)
            goto free_and_abort;
        add(&tree, x, &err);
        if (err == -1)
            goto free_and_abort;
    }
    err = scanf("%d", &q);
    if (err != 1)
        goto free_and_abort;
    for (int i = 0; i < q; ++i) {
        int l, r, res;
        err = scanf("%d%d", &l, &r);
        if (err != 2)
            goto free_and_abort;
        res = get(&tree, l, r);
        printf("%d ", res);
    }
    free_tree(&tree);
    return 0;
free_and_abort:
    free_tree(&tree);
    abort();
}

int maxi(int a, int b)
{
    return a < b ? b : a;
}

void init_tree(struct tree_T* tree)
{
    if (tree == NULL)
        return;
    tree->top = NULL;
}

void free_nodes(struct treenode_T* top)
{
    if (top == NULL)
        return;
    free_nodes(top->left);
    free_nodes(top->right);
    free(top);
}

void free_tree(struct tree_T* tree)
{
    if (tree == NULL)
        return;
    free_nodes(tree->top);
    tree->top = NULL;
}

int size_node(struct treenode_T* node)
{
    if (node == NULL)
        return 0;
    return node->size;
}

int height_node(struct treenode_T* node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

void update_size(struct treenode_T* node)
{
    if (node == NULL)
        return;
    node->size = size_node(node->left) + size_node(node->right) + 1;
}

void update_height(struct treenode_T* node)
{
    if (node == NULL)
        return;
    node->height = maxi(height_node(node->left), height_node(node->right)) + 1;
}

struct treenode_T* balance_nodes(struct treenode_T* top)
{
    struct treenode_T* tmp;
    int l_height, r_height;
    if (top == NULL)
        return NULL;
    l_height = height_node(top->left);
    r_height = height_node(top->right);
    if (l_height > r_height + 2) {
        tmp = top;
        top = top->left;
        tmp->left = top->right;
        top->right = tmp;
        update_size(tmp);
        update_height(tmp);
        update_size(top);
        update_height(top);
    }
    if (r_height > l_height + 2) {
        tmp = top;
        top = top->right;
        tmp->right = top->left;
        top->left = tmp;
        update_size(tmp);
        update_height(tmp);
        update_size(top);
        update_height(top);
    }
    return top;
}

struct treenode_T* add_nodes(struct treenode_T* top, int val, int* err)
{
    if (top == NULL) {
        top = calloc(1, sizeof(struct treenode_T));
        if (top == NULL) {
            *err = -1;
            return NULL;
        }
        top->data = val;
        top->size = 1;
        top->height = 1;
        return top;
    }
    if (val < top->data) {
        top->left = add_nodes(top->left, val, err);
    } else {
        top->right = add_nodes(top->right, val, err);
    }
    update_size(top);
    update_height(top);
    top = balance_nodes(top);
    return top;
}

void add(struct tree_T* tree, int val, int* err)
{
    if (tree == NULL)
        return;
    tree->top = add_nodes(tree->top, val, err);
}

int get_nodes(struct treenode_T* top, int ql, int qr, int l, int r)
{
    int ret = 0;
    if (top == NULL || l > qr || r < ql)
        return 0;
    if (ql <= l && r <= qr)
        return size_node(top);
    ret += get_nodes(top->left, ql, qr, l, top->data);
    ret += get_nodes(top->right, ql, qr, top->data, r);
    ret += ql <= top->data && top->data <= qr;
    return ret;
}

int get(struct tree_T* tree, int l, int r)
{
    if (tree == NULL)
        return 0;
    return get_nodes(tree->top, l, r, INT_MIN, INT_MAX);
}
