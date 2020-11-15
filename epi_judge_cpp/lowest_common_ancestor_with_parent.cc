#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

int Height(const BinaryTreeNode<int>* node) {
  int height = 0;
  while (node->parent) {
    node = node->parent;
    ++height;
  }
  return height;
}

BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  auto *n0 = node0.get(), *n1 = node1.get();
  int height0 = Height(n0), height1 = Height(n1);
  if (height1 > height0) std::swap(n0, n1);
  int depth_diff = abs(height0 - height1);
  while (n0 && depth_diff--) {
    n0 = n0->parent;
  }
  while (n0 && n1 && (n0 != n1)) {
    n0 = n0->parent;
    n1 = n1->parent;
  }
  return n0;
}
int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return Lca(node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
