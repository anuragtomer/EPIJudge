#include <unordered_map>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"

using std::unordered_map;
using std::vector;

using std::make_unique;

// One way without using map. Takes more time and space because we are creating
// vectors again and again but complexity wise, both are same.
int findIndex(const vector<int>& preorder, int key) {
  int i = 0;
  for (auto num : preorder) {
    if (num == key) return i;
    i++;
  }
  return -1;
}

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorder(
    const vector<int>& preorder, const vector<int>& inorder) {
  if (inorder.empty() || preorder.empty()) return nullptr;
  int first = preorder[0];
  int idx = findIndex(inorder, first);
  if (idx < 0 || idx >= inorder.size()) return nullptr;
  vector<int> firstHalf(inorder.begin(), inorder.begin() + idx);
  vector<int> secondHalf(inorder.begin() + idx + 1, inorder.end());
  vector<int> newPreorderLeft(preorder.begin() + 1,
                              preorder.begin() + 1 + firstHalf.size());
  vector<int> newPreorderRight(preorder.begin() + 1 + firstHalf.size(),
                               preorder.end());
  return make_unique<BinaryTreeNode<int>>(
      first, BinaryTreeFromPreorderInorder(newPreorderLeft, firstHalf),
      BinaryTreeFromPreorderInorder(newPreorderRight, secondHalf));
}

/*
  Another way using map to keep track of indices in inorder_traversal
unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorderHelper(
    const vector<int>& preorder, size_t preorder_start, size_t preorder_end,
    size_t inorder_start, size_t inorder_end,
    const unordered_map<int, size_t>& node_to_inorder_idx) {
  if (preorder_end <= preorder_start || inorder_end <= inorder_start)
    return nullptr;
  size_t root_inorder_idx = node_to_inorder_idx.at(preorder[preorder_start]);
  size_t left_subtree_size = root_inorder_idx - inorder_start;
  return make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{
      preorder[preorder_start],
      BinaryTreeFromPreorderInorderHelper(
          preorder, preorder_start + 1, preorder_start + 1 + left_subtree_size,
          inorder_start, root_inorder_idx, node_to_inorder_idx),
      BinaryTreeFromPreorderInorderHelper(
          preorder, preorder_start + 1 + left_subtree_size, preorder_end,
          root_inorder_idx + 1, inorder_end, node_to_inorder_idx)});
}

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorder(
    const vector<int>& preorder, const vector<int>& inorder) {
  unordered_map<int, size_t> node_to_inorder_idx;
  for (size_t i = 0; i < inorder.size(); ++i)
    node_to_inorder_idx.emplace(inorder[i], i);

  return BinaryTreeFromPreorderInorderHelper(
      preorder, 0, preorder.size(), 0, inorder.size(), node_to_inorder_idx);
}
*/
int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder", "inorder"};
  return GenericTestMain(
      args, "tree_from_preorder_inorder.cc", "tree_from_preorder_inorder.tsv",
      &BinaryTreeFromPreorderInorder, DefaultComparator{}, param_names);
}
