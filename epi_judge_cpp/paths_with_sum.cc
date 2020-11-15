#include <memory>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

void PathSumHelper(const unique_ptr<BinaryTreeNode<int>>& tree,
                   int remaining_weight,
                   vector<vector<BinaryTreeNode<int>>>& sum_paths,
                   vector<BinaryTreeNode<int>> path) {
  if (!tree) return;

  path.emplace_back(tree);
  remaining_weight -= tree->data;
  if (!tree->left && !tree->right) {
    if (remaining_weight == 0) {
      sum_paths.emplace_back(path);
      return;
    }
  }

  PathSumHelper(tree->left, remaining_weight, sum_paths, path);
  PathSumHelper(tree->right, remaining_weight, sum_paths, path);
  return;
}

vector<vector<BinaryTreeNode<int>>> PathSum(
    const unique_ptr<BinaryTreeNode<int>>& tree, int remaining_weight) {
  vector<vector<BinaryTreeNode<int>>> sum_paths;
  vector<BinaryTreeNode<int>> path;
  PathSumHelper(tree, remaining_weight, sum_paths, path);
  return sum_paths;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "remaining_weight"};
  return GenericTestMain(args, "paths_with_sum.cc", "paths_with_sum.tsv",
                         &PathSum, DefaultComparator{}, param_names);
}
