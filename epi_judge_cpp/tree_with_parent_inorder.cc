#include <vector>

#include "binary_tree_with_parent_prototype.h"
#include "test_framework/generic_test.h"
using std::cout;
using std::vector;
/* My code */
/*
vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  vector<int> result;
  auto const* iter = tree.get();
  while (iter != nullptr) {
    while (iter->left != nullptr) {
      iter = iter->left.get();
    }
    result.emplace_back(iter->data);
    // while (iter->right == nullptr) iter = iter->parent;
    while (iter->right == nullptr) {
      auto right = iter;
      iter = iter->parent;
      while (iter != nullptr && iter->right.get() == right) {
        right = iter;
        iter = iter->parent;
      }
      if (iter == nullptr) return result;
      result.emplace_back(iter->data);
    }
    iter = iter->right.get();
  }
  return result;
}
*/

/**
 * Code in the book.
 */
vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  vector<int> result;
  BinaryTreeNode<int>*prev = nullptr, *curr = tree.get();
  while (curr != nullptr) {
    BinaryTreeNode<int>* next;
    if (curr->parent == prev) {
      if (curr->left != nullptr) {
        next = curr->left.get();
      } else {
        result.emplace_back(curr->data);
        next = (curr->right != nullptr) ? curr->right.get() : curr->parent;
      }
    } else if (curr->left.get() == prev) {
      result.emplace_back(curr->data);
      next = (curr->right != nullptr) ? curr->right.get() : curr->parent;
    } else {
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
  return GenericTestMain(args, "tree_with_parent_inorder.cc",
                         "tree_with_parent_inorder.tsv", &InorderTraversal,
                         DefaultComparator{}, param_names);
}
/*
           1
        2    3
      4  5  6  7
p = 1
c = 2
n =
*/