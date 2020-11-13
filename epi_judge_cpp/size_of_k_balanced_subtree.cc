#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

struct Status {
  bool iskBalanced;
  int size;
  int depth;
  BinaryTreeNode<int>* root;
};

Status largestkBalancedSubtreeHelper(
    const unique_ptr<BinaryTreeNode<int>>& tree, int k) {
  Status st;
  if (tree == nullptr) {
    st.iskBalanced = true;
    st.depth = 0;
    st.size = 0;
    st.root = tree.get();
    return st;
  }

  Status left, right;
  left = largestkBalancedSubtreeHelper(tree->left, k);
  right = largestkBalancedSubtreeHelper(tree->right, k);
  if (left.iskBalanced && right.iskBalanced &&
      abs(left.depth - right.depth) <= k) {
    st.iskBalanced = true;
    st.depth = std::max(left.depth, right.depth) + 1;
    st.size = left.size + right.size + 1;
    st.root = tree.get();
    return st;
  }
  st.iskBalanced = false;
  st.depth = std::max(left.depth, right.depth);
  st.size = left.depth >= right.depth ? left.size : right.size;
  st.root = left.depth >= right.depth ? left.root : right.root;
  return st;
}

int largestkBalancedSubtree(const unique_ptr<BinaryTreeNode<int>>& tree,
                            int k) {
  if (tree == nullptr) return 0;
  return largestkBalancedSubtreeHelper(tree, k).size;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(
      args, "size_of_k_balanced_subtree.cc", "size_of_k_balanced_subtree.tsv",
      &largestkBalancedSubtree, DefaultComparator{}, param_names);
}
