#include <vector>

#include "binary_tree_with_parent_prototype.h"
#include "test_framework/generic_test.h"
using std::vector;

vector<int> PreorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  vector<int> result;
  BinaryTreeNode<int>* curr = tree.get();
  BinaryTreeNode<int>* prev = nullptr;
  while (curr != nullptr) {
    BinaryTreeNode<int>* next;
    if ((prev == nullptr) ||
        (prev != curr->left.get() && prev != curr->right.get())) {
      result.emplace_back(curr->data);
      if (curr->left != nullptr) {
        next = curr->left.get();
      } else if (curr->right != nullptr) {
        next = curr->right.get();
      } else {
        next = curr->parent;
      }
    } else {
      next = (prev != curr->right.get())
                 ? ((curr->right.get() != nullptr) ? curr->right.get()
                                                   : curr->parent)
                 : curr->parent;
    }
    prev = curr;
    curr = next;
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_with_parent_preorder.cc",
                         "tree_preorder.tsv", &PreorderTraversal,
                         DefaultComparator{}, param_names);
}
