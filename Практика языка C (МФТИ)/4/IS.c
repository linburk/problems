#include <limits.h>
#include <stdlib.h>

#if 1
struct tree_t {
    struct tree_t* left;
    struct tree_t* right;
    int data;
};
#endif

int check_is_bst_impl(struct tree_t* top, int l, int r)
{
    int check_l, check_r, check_m;
    if (top == NULL)
        return 1;
    check_m = l <= top->data && top->data <= r;
    check_l = check_is_bst_impl(top->left, l, top->data);
    check_r = check_is_bst_impl(top->right, top->data, r);
    return check_l && check_m && check_r;
}

int check_is_bst(struct tree_t* top)
{
    return check_is_bst_impl(top, INT_MIN, INT_MAX);
}
