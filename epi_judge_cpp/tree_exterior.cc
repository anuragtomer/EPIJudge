#include <unordered_set>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unordered_set;
using std::vector;

void getLeftExterior(const unique_ptr<BinaryTreeNode<int>>& tree,
                     vector<const unique_ptr<BinaryTreeNode<int>>*>& result) {
  if (tree == nullptr) return;
  if (tree->left == nullptr && tree->right == nullptr)
    return;  // I've reached leave node. Return.
  result.push_back(&tree);
  if (tree->left)  // Priority give to left child. This is left exterior.
    getLeftExterior(tree->left, result);
  else if (tree->right)
    getLeftExterior(tree->right, result);
}

void getLeaves(const unique_ptr<BinaryTreeNode<int>>& tree,
               vector<const unique_ptr<BinaryTreeNode<int>>*>& result) {
  if (tree == nullptr) return;
  if (tree->left == nullptr && tree->right == nullptr) result.push_back(&tree);
  getLeaves(tree->left, result);
  getLeaves(tree->right, result);
}
void getRightExterior(const unique_ptr<BinaryTreeNode<int>>& tree,
                      vector<const unique_ptr<BinaryTreeNode<int>>*>& result) {
  if (tree == nullptr) return;
  if (tree->left == nullptr && tree->right == nullptr)
    return;  // I've reached leave node. Return.
  result.push_back(&tree);
  if (tree->right)  // Priority given to right child. This is right exterior.
    getRightExterior(tree->right, result);
  else if (tree->left)
    getRightExterior(tree->left, result);
}

vector<const unique_ptr<BinaryTreeNode<int>>*> ExteriorBinaryTree(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  vector<const unique_ptr<BinaryTreeNode<int>>*> result, temp_result,
      final_result;
  if (tree != nullptr) {
    result.push_back(&tree);
    getLeftExterior(tree->left, result);
    getLeaves(tree, result);
    getRightExterior(tree->right, temp_result);
    reverse(temp_result.begin(), temp_result.end());
    result.insert(result.end(), temp_result.begin(), temp_result.end());
    unordered_set<const unique_ptr<BinaryTreeNode<int>>*> set;

    for (auto elem : result) {
      if (set.count(elem) == 0) final_result.push_back(elem);
      set.insert(elem);
    }
  }
  return final_result;
}
vector<int> CreateOutputVector(
    const vector<const unique_ptr<BinaryTreeNode<int>>*>& L) {
  if (std::find(std::begin(L), std::end(L), nullptr) != std::end(L)) {
    throw TestFailure("Resulting list contains nullptr");
  }
  std::vector<int> output;
  for (const auto* l : L) {
    output.push_back((*l)->data);
  }
  return output;
}

vector<int> ExteriorBinaryTreeWrapper(
    TimedExecutor& executor, const unique_ptr<BinaryTreeNode<int>>& tree) {
  auto result = executor.Run([&] { return ExteriorBinaryTree(tree); });

  return CreateOutputVector(result);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree"};
  return GenericTestMain(args, "tree_exterior.cc", "tree_exterior.tsv",
                         &ExteriorBinaryTreeWrapper, DefaultComparator{},
                         param_names);
}
