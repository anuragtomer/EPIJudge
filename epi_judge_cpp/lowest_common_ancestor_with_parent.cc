#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

int Height(const unique_ptr<BinaryTreeNode<int>>& node) {
  int height = 0;
  BinaryTreeNode<int>* temp = node.get();
  while (temp->parent) {
    temp = temp->parent;
    height++;
  }
  return height;
}
BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  int height0 = Height(node0);
  int height1 = Height(node1);
  BinaryTreeNode<int>* n0 = node0.get();
  BinaryTreeNode<int>* n1 = node1.get();
  while (n0 && height0 > height1) {
    n0 = n0->parent;
    height0--;
  }
  while (n1 && height0 < height1) {
    n1 = n1->parent;
    height1--;
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
