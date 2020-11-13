#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
struct BalancedStatusWithHeight {
  int height;
  bool balanced;
};

BalancedStatusWithHeight IsBalancedHeight(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  if (tree == nullptr) return {0, true};
  BalancedStatusWithHeight left, right;
  left = IsBalancedHeight(tree->left);
  right = IsBalancedHeight(tree->right);
  if (left.balanced == false || right.balanced == false)
    return {0, false};
  else {
    BalancedStatusWithHeight status;
    status.balanced = abs(left.height - right.height) <= 1;
    status.height = std::max(left.height, right.height) + 1;
    return status;
  }
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  BalancedStatusWithHeight left, right;
  if (tree == nullptr) return true;
  left = IsBalancedHeight(tree->left);
  right = IsBalancedHeight(tree->right);
  if (left.balanced == false || right.balanced == false) return false;
  return abs(left.height - right.height) <= 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
