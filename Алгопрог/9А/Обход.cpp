#include <iostream>

class BST {
  struct Node {
    int key;
    Node *left = nullptr;
    Node *right = nullptr;
    Node(int key) : key{key} {}
  } root{0};
  void insert(int key, Node *node) {
    if (key < node->key) {
      if (node->left == nullptr) {
        node->left = new Node(key);
      } else
        return insert(key, node->left);
    } else if (key > node->key) {
      if (node->right == nullptr) {
        node->right = new Node(key);
      } else
        return insert(key, node->right);
    }
  }
  int height(Node *node) {
    if (!node->left && !node->right)
      return 1;
    int h = 0;
    if (node->left)
      h = std::max(h, height(node->left) + 1);
    if (node->right)
      h = std::max(h, height(node->right) + 1);
    return h;
  }
  void print_tree(Node *node) {
    if (!node->left && !node->right)
      return static_cast<void>(std::cout << node->key << "\n");
    if (node->left)
      print_tree(node->left);
    std::cout << node->key << "\n";
    if (node->right)
      print_tree(node->right);
  }

public:
  void insert(int key) {
    if (root.key == 0) {
      root.key = key;
    } else
      return insert(key, &root);
  }
  int height() { return height(&root); }
  void print_tree() { return print_tree(&root); }
};

int main(int argc, char **argv) {
  BST tree;
  for (int x; std::cin >> x;) {
    if (x == 0)
      break;
    tree.insert(x);
  }
  tree.print_tree();
  return 0;
}