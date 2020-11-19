#include <vector>

#include "binary_tree_with_parent_prototype.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

vector<int> PostorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  vector<int> result;
  BinaryTreeNode<int>*curr = tree.get(), *prev = nullptr;
  while (curr != nullptr) {
    BinaryTreeNode<int>* next = nullptr;
    if ((prev == nullptr) ||
        ((curr->left.get() != prev) && (curr->right.get() != prev))) {
      if (curr->left != nullptr)
        next = curr->left.get();
      else if (curr->right != nullptr)
        next = curr->right.get();
      else {
        result.emplace_back(curr->data);
        next = curr->parent;
      }
    } else if (prev == curr->left.get()) {
      if (curr->right == nullptr) result.emplace_back(curr->data);
      next = (curr->right != nullptr) ? (curr->right.get()) : (curr->parent);
    } else {
      result.emplace_back(curr->data);
      next = curr->parent;
    }
    prev = curr;
    curr = next;
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_with_parent_postorder.cc",
                         "tree_postorder.tsv", &PostorderTraversal,
                         DefaultComparator{}, param_names);
}
