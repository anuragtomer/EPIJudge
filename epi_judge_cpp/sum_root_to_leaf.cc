#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
int SumRootToLeafHelper(const unique_ptr<BinaryTreeNode<int>>& tree,
                        int running_sum) {
  if (!tree) {
    return 0;
  }
  running_sum = (running_sum << 1) + tree->data;
  if (!tree->left && !tree->right) {
    return running_sum;
  }
  return SumRootToLeafHelper(tree->left, running_sum) +
         SumRootToLeafHelper(tree->right, running_sum);
}
int SumRootToLeaf(const unique_ptr<BinaryTreeNode<int>>& tree) {
  int running_sum = 0;
  return SumRootToLeafHelper(tree, running_sum);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "sum_root_to_leaf.cc", "sum_root_to_leaf.tsv",
                         &SumRootToLeaf, DefaultComparator{}, param_names);
}
