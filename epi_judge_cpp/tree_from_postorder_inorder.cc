#include <unordered_map>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"

using std::unordered_map;
using std::vector;

using std::make_unique;

int findIndex(const vector<int>& inorder, int data) {
  if (inorder.empty()) return -1;
  for (int i = 0; i < inorder.size(); ++i)
    if (inorder[i] == data) return i;
  return -1;
}

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPostorderInorder(
    const vector<int>& postorder, const vector<int>& inorder) {
  if (inorder.empty() || postorder.empty()) return nullptr;
  int data = postorder.back();
  int index = findIndex(inorder, data);
  vector<int> postorderLeft =
      vector<int>(postorder.begin(), postorder.begin() + index);
  vector<int> postorderRight =
      vector<int>(postorder.begin() + index, postorder.end() - 1);
  vector<int> inorderLeft =
      vector<int>(inorder.begin(), inorder.begin() + index);
  vector<int> inorderRight =
      vector<int>(inorder.begin() + 1 + index, inorder.end());
  return make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{
      data, BinaryTreeFromPostorderInorder(postorderLeft, inorderLeft),
      BinaryTreeFromPostorderInorder(postorderRight, inorderRight)});
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"postorder", "inorder"};
  return GenericTestMain(
      args, "tree_from_postorder_inorder.cc", "tree_from_postorder_inorder.tsv",
      &BinaryTreeFromPostorderInorder, DefaultComparator{}, param_names);
}
